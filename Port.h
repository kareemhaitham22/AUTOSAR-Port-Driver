/*******************************************************************************
 * Module: Port
 * File Name: Port.h
 * Description: TM4C123GH6PM microcontroller header file of port driver
 * Author: Kareem Haitham
*******************************************************************************/

#ifndef PORT_H
#define PORT_H

/*id for the company in the AUTOSAR*/
#define PORT_VENDOR_ID                                  (1000U)

/* port module id */
#define PORT_MODULE_ID                                  (124U)

/* port instance id */
#define PORT_INSTANCE_ID                                (0U)

/*Module Version 1.0.0*/
#define PORT_SW_MAJOR_VERSION                           (1U)
#define PORT_SW_MINOR_VERSION                           (0U)
#define PORT_SW_PATCH_VERSION                           (0U)

/*AUTOSAR Version 4.0.3*/
#define PORT_AR_RELEASE_MAJOR_VERSION                   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION                   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION                   (3U)

/*macros for port status*/
#define PORT_INITIALIZED                                (1U)
#define PORT_NOT_INITIALIZED                            (0U)

/* number of pins in the single port*/
#define SINGLE_PORT_PINS_NUM                            (8U)

#define PORT_PIN_MODE_DIO                               (0U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_01             (1U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_02             (2U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_03             (3U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_04             (4U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_05             (5U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_06             (6U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_07             (7U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_08             (8U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_09             (9U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_10             (10U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_11             (11U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_12             (12U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_13             (13U)
#define PORT_PIN_MODE_ALTERNATE_FUNCTION_14             (14U)
#define PORT_PIN_MODE_ANALOG                            (15U)


#include "Std_Types.h"


/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif


#include "Port_Cfg.h"


/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif


#include "Common_Macros.h"


/*service ids written in sws for each method*/
#define PORT_INIT_SID                                    (uint8)0x00
#define PORT_SET_PIN_DIRECTION_SID                       (uint8)0x01
#define PORT_REFRESH_PORT_DIRECTION_SID                  (uint8)0x02
#define PORT_GET_VERSION_INFO_SID                        (uint8)0x03
#define PORT_SET_PIN_MODE_SID                            (uint8)0x04


/*Development error values in sws*/
#define PORT_E_PARAM_PIN                                 (uint8)0x0A
#define PORT_E_DIRECTION_UNCHANGEABLE                    (uint8)0x0B
#define PORT_E_PARAM_CONFIG                              (uint8)0x0C
#define PORT_E_PARAM_INVALID_MODE                        (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE                         (uint8)0x0E
#define PORT_E_UNINIT                                    (uint8)0x0F
#define PORT_E_PARAM_POINTER                             (uint8)0x10


/*range: 0 to number of port pins (here 0 t0 48)*/
typedef uint8 Port_PinType;

/*enumeration type having range as PORT_PIN_IN and PORT_PIN_OUT*/
typedef enum {
      PORT_PIN_IN,          
      PORT_PIN_OUT,         
  }Port_PinDirectionType;

/* not in sws */
typedef enum {
      OFF,PULL_UP,PULL_DOWN
  }Port_InternalResistor;

typedef uint8 Port_InitialValue;

/*number of port pin modes*/
typedef uint8 Port_PinModeType;

typedef uint8 Port_DirectionChange;

typedef uint8 Port_ModeChange;

/*arranged according to sws suggestion, added internal resistance of port*/
typedef struct {
        Port_PinModeType            mode;
        Port_PinDirectionType       direction;                                
        uint8                       initial_value;                                
        uint8                       direction_change;       
        uint8                       mode_change;
        Port_InternalResistor       resistor;
  }Port_PinStruct;        /*Port_PinStruct*/

typedef struct {
        const Port_PinStruct* Pins[PORT_ALL_PINS_NUMBER];
  }Port_ConfigType;      


/*methods required in sws all description copied from sws*/

/*******************************************************************************
* service_name:Port_Init
* service_id:0x00
* sync/async:Synchronous
* reentrancy:non_reentrant
* in:const Port_ConfigType* ConfigPtr
* inout:none
* out:none
* return_value:none
* description:initializes the Port Driver module
*******************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr );


#if (STD_ON == PORT_SET_PIN_DIRECTION_API)
    /***************************************************************************
    * service_name:Port_SetPinDirection
    * service_id:0x01
    * sync/async:Synchronous
    * reentrancy:reentrant
    * in:Port_PinType Pin, Port_PinDirectionType Direction
    * inout:none
    * out:none
    * return_value:none
    * description:sets the port pin direction
    ***************************************************************************/
    void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif


/*******************************************************************************
* service_name:Port_RefreshPortDirection
* service_id:0x02
* sync/async:synchronous
* reentrancy:non_reentrant
* in:none
* inout:none
* out:none
* return_value:none
* description:refreshes port direction
*******************************************************************************/
void Port_RefreshPortDirection( void );


#if (STD_ON == Port_SetPinMode_API)
  /*****************************************************************************
  * service_name:Port_SetPinMode
  * service_id:0x04
  * sync/async:synchronous
  * reentrancy:reentrant
  * in: Port_PinType Pin, Port_PinModeType Mode
  * inout:none
  * out:none
  * return_value:none
  * description:sets the port pin mode
  *****************************************************************************/
  void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif
  

#if (STD_ON == PORT_VERSION_INFO_API)
    /***************************************************************************
    * service_name:Port_GetVersionInfo
    * service_id:0x03
    * sync/async:synchronous
    * reentrancy:non_reentrant
    * in:none
    * inout:none
    * out:versioninfo (Pointer contains version information)
    * return_value:none
    * description:returns the version information of this module.
    ***************************************************************************/
    void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif


/*extern variable mentioned in sws*/
extern const Port_ConfigType Port_Configuration;

#endif 