/******************************************************************************
 * Module: Port
 * File Name: Port.c
 * Description: TM4C123GH6PM microcontroller Source file of port driver
 * Author: Kareem Haitham
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"
#include "tm4c123gh6pm_registers.h"

#if (STD_ON == PORT_DEV_ERROR_DETECT)
#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif
#endif

static uint8 Port_Status = PORT_NOT_INITIALIZED;


void Port_Init( const Port_ConfigType* ConfigPtr ) {
  #if (STD_ON == DIO_DEV_ERROR_DETECT)
    /* check NULL_PTR for the input configuration */
    if (NULL_PTR == ConfigPtr) {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);  }
    else { }
  #endif
  Port_Status = PORT_INITIALIZED;
  Port_PinType Pin = 0;  
  while(Pin < PORT_ALL_PINS_NUMBER) {
    /* if configuration ptr is assigned as NULL_PTR, do nothing and skip to the next iteration */
    if(NULL_PTR == Port_Configuration.Pins[Pin]) { }
    else {
      /* pin number: PinId */  
      uint8 PinId = Pin % SINGLE_PORT_PINS_NUM;
      /* port number: PortId */
      uint8 PortId = Pin / SINGLE_PORT_PINS_NUM;
      volatile uint32 delay = 0;
      /* Port-Pin configuration structure */
      Port_PinStruct PinConfig = *Port_Configuration.Pins[Pin];
      volatile uint32 * Port_Ptr = NULL_PTR;  
      /* from portid assign the portptr to the equivalent port base address */
      switch(PortId) {
        case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /*PORTA*/       break;
	case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /*PORTB*/       break;
	case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /*PORTC*/       break;
	case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /*PORTD*/       break;
        case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /*PORTE*/       break;
        case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /*PORTF*/       break;
      }      
      if(NULL_PTR == Port_Ptr) { }
      else {
        /* enable PORT clock */
        SYSCTL_REGCGC2_REG |= (1<<PortId);
        delay = SYSCTL_REGCGC2_REG;
        /* unlock if PD7 or PF0  */
        if( ((3 == PortId) && (7 == PinId)) || ((5 == PortId) && (0 == PinId)) ) {
            /* unlock the GPIOCR register (assigning 0x4C4F434B to PORT_LOCK_REG) */
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B; 
            /* allow changes on pin (set bit in GPIOCR register) */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_COMMIT_REG_OFFSET) , PinId);  
        }
        else { }       
        if(PORT_PIN_MODE_DIO == PinConfig.mode) {
            /* disable analog function (clear GPIOAMSEL register bit) */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);
            /* disable alternative function (clear GPIOAFSEL register bit) */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
            /* clear PMCx bits */
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));            
            if(PORT_PIN_OUT == PinConfig.direction) {
                /* configure as output pin (set GPIODIR register bit)  */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);                  
                if(PinConfig.initial_value == STD_HIGH) {
                    /* set initial value to high (set GPIODATA register bit) */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PinId);   }
                else {
                  /* set initial value to low (clear GPIODATA register bit) */
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PinId);    }
            }
            else if(PORT_PIN_IN == PinConfig.direction) {
                /* configure as input pin (clear GPIODIR register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId); 
                if(PULL_UP == PinConfig.resistor) {
                    /* enable internal pull up (set GPIOPUR register bit) */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId); }
                else if(PULL_DOWN == PinConfig.resistor ) {
                    /* enable internal pull down (set GPIOPDR register bit) */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId); }
                else {
                    /* disable internal pull up (clear GPIOPUR register bit) */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);
                    /* disable internal pull down (clear GPIOPDR register bit) */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);
                }
            }
            else { }
            /* enable digital function (set GPIODEN register bit) */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);
        }
        else if(PORT_PIN_MODE_ANALOG == PinConfig.mode) {
            /* disable digital function (clear GPIODEN register bit) */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);
            /* Disable Alternative function (clear GPIOAFSEL register bit) */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
            /* Clear PMCx bits */
            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));            
            if(PORT_PIN_OUT == PinConfig.direction) {
                /* configure as output pin (set GPIODIR register bit) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId); }
            else if(PORT_PIN_IN == PinConfig.direction) {
                /* configure as input pin (clear GPIODIR register bit) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId); }
            /* enable analog function (set GPIOAMSEL register bit) */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);            
        }                               
        else if(    (PORT_PIN_MODE_ALTERNATE_FUNCTION_01 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_02 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_03 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_04 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_05 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_06 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_07 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_08 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_09 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_10 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_11 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_12 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_13 == PinConfig.mode) \
                 || (PORT_PIN_MODE_ALTERNATE_FUNCTION_14 == PinConfig.mode) )  {
                        
                        /* disable analog function (clear GPIOAMSEL register bit) */
                        CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);
                        /* enable alternative function (set GPIOAFSEL register bit) */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
                        /* clear the PMCx bits */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));
                        /* (set the PMCx bits): to selected Alternate function */
                        *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (PinId * 4));
                        /* enable digital function (set GPIODEN register bit) */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);
                        
                        if(PORT_PIN_OUT == PinConfig.direction) {
                          /* configure as output pin (set GPIODIR register bit)  */
                          SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);                  
                          if(PinConfig.initial_value == STD_HIGH) {
                            /* set initial value to high (set GPIODATA register bit) */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PinId);   }
                          else {
                            /* set initial value to low (clear GPIODATA register bit) */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DATA_REG_OFFSET) , PinId);    }
                            }
                        else if(PORT_PIN_IN == PinConfig.direction) {
                          /* configure as input pin (clear GPIODIR register bit) */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId); 
                          if(PULL_UP == PinConfig.resistor) {
                            /* enable internal pull up (set GPIOPUR register bit) */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId); }
                          else if(PULL_DOWN == PinConfig.resistor ) {
                            /* enable internal pull down (set GPIOPDR register bit) */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId); }
                        else {
                          /* disable internal pull up (clear GPIOPUR register bit) */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);
                          /* disable internal pull down (clear GPIOPDR register bit) */
                          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);
                          }
                       }              
          }                                
      }
    }
    Pin++;
  }
}


#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction ) {
      boolean error = FALSE;
      /* pin number: PinId */
      uint8 PinId = Pin % SINGLE_PORT_PINS_NUM;
      /* port number: PortId */
      uint8 PortId = Pin / SINGLE_PORT_PINS_NUM;
      /* Port-Pin configuration structure */
      Port_PinStruct PinConfig = *Port_Configuration.Pins[Pin];  
      volatile uint32 * Port_Ptr = NULL_PTR;
      /* from portid assign the portptr to the equivalent port base address */
      switch(PortId) {
        case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /*PORTA*/       break;
	case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /*PORTB*/       break;
	case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /*PORTC*/       break;
	case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /*PORTD*/       break;
        case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /*PORTE*/       break;
        case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /*PORTF*/       break;
      }  
      #if (STD_ON == PORT_DEV_ERROR_DETECT)
          /* check Port driver status */
          if(PORT_INITIALIZED != Port_Status) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
                error = TRUE;   }
          else { }
          /* check that pin direction is changeable */
          if(STD_OFF == PinConfig.direction_change) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
                error = TRUE;   }
          else { }
          if(NULL_PTR == Port_Configuration.Pins[Pin]) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
                error = TRUE;   }
          else { }  
      #endif   
      if(FALSE == error) {
          if(PORT_PIN_IN == Direction) {
                /* configure as input pin (Clear GPIODIR register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);    }
          else if(PORT_PIN_OUT == Direction) {
                /* configure as output pin (set GPIODIR register bit) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);      }
      }
  }
#endif


void Port_RefreshPortDirection( void ) {  
      #if (STD_ON == PORT_DEV_ERROR_DETECT)
          /* check Port driver status */
          if(PORT_INITIALIZED != Port_Status) {
              Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);  }
          else 
      #endif 
             {
              for(Port_PinType Pin = 0; Pin < PORT_ALL_PINS_NUMBER; Pin++) {
                  /* if configuration ptr is assigned as NULL_PTR, do nothing and skip to the next iteration */
                  if(NULL_PTR == Port_Configuration.Pins[Pin]) { }
                  else {
                      /* pin number: PinId */
                      uint8 PinId = Pin % SINGLE_PORT_PINS_NUM;
                      /* port number: PortId */
                      uint8 PortId = Pin / SINGLE_PORT_PINS_NUM;
                      /* Port-Pin configuration structure */
                      Port_PinStruct PinConfig = *Port_Configuration.Pins[Pin];       
                      volatile uint32 * Port_Ptr = NULL_PTR;
                      /* from portid assign the portptr to the equivalent port base address */
                      switch(PortId) {
                          case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /*PORTA*/     break;
                          case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /*PORTB*/     break;
                          case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /*PORTC*/     break;
                          case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /*PORTD*/     break;
                          case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /*PORTE*/     break;
                          case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /*PORTF*/     break;
                        }            
                      if(STD_ON == PinConfig.direction_change) {
                          if(PORT_PIN_IN == PinConfig.direction) {
                              /* configure as input pin (clear GPIODIR register bit) */
                              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);  }
                          else if(PORT_PIN_OUT == PinConfig.direction) {
                              /* configure as output pin (set GPIODIR register bit) */
                              SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIR_REG_OFFSET) , PinId);    }    
                          }
                      else { }
                    }
                }
          }             
    }


#if (STD_ON == Port_SetPinMode_API)
  void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode ) {
      boolean error = FALSE;
      /* pin number: PinId */
      uint8 PinId = Pin % SINGLE_PORT_PINS_NUM;
      /* port number: PortId */
      uint8 PortId = Pin / SINGLE_PORT_PINS_NUM;
      /* Port-Pin configuration structure */
      Port_PinStruct PinConfig = *Port_Configuration.Pins[Pin];
      volatile uint32 * Port_Ptr = NULL_PTR;
      /* from portid assign the portptr to the equivalent port base address */
      switch(PortId) {
          case  0: Port_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /*PORTA*/       break;
          case  1: Port_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /*PORTB*/       break;
          case  2: Port_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /*PORTC*/       break;
          case  3: Port_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /*PORTD*/       break;
          case  4: Port_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /*PORTE*/       break;
          case  5: Port_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /*PORTF*/       break;
        }  
        #if (STD_ON == PORT_DEV_ERROR_DETECT)
            /* check Port driver status */
            if(PORT_INITIALIZED != Port_Status) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
                error = TRUE;  }
            else { }
            /* check that pin direction is changeable */
            if(STD_OFF == PinConfig.mode_change) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
                error = TRUE;  }
            else { }
            if(NULL_PTR == Port_Configuration.Pins[Pin]) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
                error = TRUE;  }
            else { }
            if(PORT_PIN_MODE_ANALOG < PinConfig.mode) {
                Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
                error = TRUE;  }
            else { } 
        #endif  
        if(FALSE == error) {
            if(PORT_PIN_MODE_DIO == Mode) {
                /* disable analog function (clear GPIOAMSEL register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);
                /* Disable Alternative function (clear GPIOAFSEL register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
                /* Clear PMCx bits */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));
                /* enable digital function (set GPIODEN register bit) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);       }
            else if(PORT_PIN_MODE_ANALOG == Mode) {
                /* disable digital function (clear GPIODEN register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);
                /* Disable Alternative function (clear GPIOAFSEL register bit) */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
                /* Clear PMCx bits */
                *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));                
                /* enable analog function (set GPIOAMSEL register bit) */
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);      }
          
            else if(    (PORT_PIN_MODE_ALTERNATE_FUNCTION_01 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_02 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_03 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_04 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_05 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_06 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_07 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_08 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_09 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_10 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_11 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_12 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_13 == PinConfig.mode) \
                    || (PORT_PIN_MODE_ALTERNATE_FUNCTION_14 == PinConfig.mode) )  {
                       
                            /* disable analog function (clear GPIOAMSEL register bit) */
                            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);
                            /* enable alternative function (set GPIOAFSEL register bit) */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);
                            /* clear the PMCx bits */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));
                            /* (set the PMCx bits): to selected Alternate function */
                            *(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (PinId * 4));
                            /* enable digital function (set GPIODEN register bit) */
                            SET_BIT(*(volatile uint32 *)((volatile uint8 *)Port_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);           
              }                    
            else { }
          }
      }
#endif


#if (STD_ON == PORT_VERSION_INFO_API)
    void Port_GetVersionInfo( Std_VersionInfoType* versioninfo ) {
          boolean error = FALSE;
          #if (STD_ON == PORT_DEV_ERROR_DETECT)
              /* check NULL_PTR for versioninfo */
              if(NULL_PTR == versioninfo) {
                  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
                  error = TRUE;  }
              else { }
              /* check Port driver status */
              if(PORT_INITIALIZED != Port_Status) {
                  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
                  error = TRUE;  }
              else { }  
          #endif 
          if(FALSE == error) {
              /* copy vendor id of port */
              versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
              /* copy module id of port */
              versioninfo->moduleID = (uint16)PORT_MODULE_ID;
              /* copy software major version of port */
              versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
              /* copy software minor version of port */
              versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
              /* copy software patch version of port */
              versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
            }
        }
#endif