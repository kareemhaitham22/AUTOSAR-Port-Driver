/*******************************************************************************
 * Module: Port
 * File Name: Port_PBcfg.c
 * Description: port driver post build configuration
 * Author: Kareem Haitham
*******************************************************************************/

#include "Port.h"

/*Module Version 1.0.0*/
#define PORT_PBCFG_SW_MAJOR_VERSION                             (1U)
#define PORT_PBCFG_SW_MINOR_VERSION                             (0U)
#define PORT_PBCFG_SW_PATCH_VERSION                             (0U)

/*AUTOSAR Version 4.0.3*/
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION                     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION                     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION                     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


#define DEFAULT                                                  (0U)
#define DIO_INPUT_PULLUP                                         (0U)
#define DIO_INPUT_PULLDOWN                                       (1U)
#define DIO_INPUT                                                (2U)
#define DIO_CONST_INPUT_PULLUP                                   (3U)
#define DIO_CONST_INPUT_PULLDOWN                                 (4U)
#define DIO_CONST_INPUT                                          (5U)   
#define CONST_DIO_CONST_INPUT_PULLUP                             (6U)
#define CONST_DIO_CONST_INPUT_PULLDOWN                           (7U)
#define CONST_DIO_CONST_INPUT                                    (8U)  
#define DIO_OUTPUT_PULLUP                                        (9U)
#define DIO_OUTPUT_PULLDOWN                                      (10U)
#define DIO_OUTPUT                                               (11U)
#define DIO_CONST_OUTPUT_PULLUP                                  (12U)
#define DIO_CONST_OUTPUT_PULLDOWN                                (13U)
#define DIO_CONST_OUTPUT                                         (14U)   
#define CONST_DIO_CONST_OUTPUT_PULLUP                            (15U)
#define CONST_DIO_CONST_OUTPUT_PULLDOWN                          (16U)
#define CONST_DIO_CONST_OUTPUT                                   (17U)
#define ANALOG_INPUT_PULLUP                                      (18U)
#define ANALOG_INPUT_PULLDOWN                                    (19U)
#define ANALOG_INPUT                                             (20U)
#define ANALOG_CONST_INPUT_PULLUP                                (21U)
#define ANALOG_CONST_INPUT_PULLDOWN                              (22U)
#define ANALOG_CONST_INPUT                                       (23U)   
#define CONST_ANALOG_CONST_INPUT_PULLUP                          (24U)
#define CONST_ANALOG_CONST_INPUT_PULLDOWN                        (25U)
#define CONST_ANALOG_CONST_INPUT                                 (26U)  
#define ANALOG_OUTPUT_PULLUP                                     (27U)
#define ANALOG_OUTPUT_PULLDOWN                                   (28U)
#define ANALOG_OUTPUT                                            (29U)
#define ANALOG_CONST_OUTPUT_PULLUP                               (30U)
#define ANALOG_CONST_OUTPUT_PULLDOWN                             (31U)
#define ANALOG_CONST_OUTPUT                                      (32U)   
#define CONST_ANALOG_CONST_OUTPUT_PULLUP                         (33U)
#define CONST_ANALOG_CONST_OUTPUT_PULLDOWN                       (34U)
#define CONST_ANALOG_CONST_OUTPUT                                (35U)   
#define CONST_DIO_INPUT_PULLUP                                   (36U)
#define CONST_DIO_INPUT_PULLDOWN                                 (37U)
#define CONST_DIO_INPUT                                          (38U)
#define CONST_DIO_OUTPUT_PULLUP                                  (39U)
#define CONST_DIO_OUTPUT_PULLDOWN                                (40U)
#define CONST_DIO_OUTPUT                                         (41U)
#define CONST_ANALOG_INPUT_PULLUP                                (42U)
#define CONST_ANALOG_INPUT_PULLDOWN                              (43U)
#define CONST_ANALOG_INPUT                                       (44U)
#define CONST_ANALOG_OUTPUT_PULLUP                               (45U)
#define CONST_ANALOG_OUTPUT_PULLDOWN                             (46U)
#define CONST_ANALOG_OUTPUT                                      (47U)
      
/*we have 48 different combinations (2*2*2*3) */
#define PORT_ALL_DIFFERENT_CONFIGURATIONS_ARRAY_SIZE                            (48U)   
const Port_PinStruct Port_AllDifferentConfigurations[PORT_ALL_DIFFERENT_CONFIGURATIONS_ARRAY_SIZE]={  
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, PULL_UP},          /* DEFAULT (DIO_INPUT_PULLUP)  0 */    
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, PULL_DOWN},        /*DIO_INPUT_PULLDOWN  1*/    
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, OFF},              /*DIO_INPUT  2*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, PULL_UP},         /*DIO_CONST_INPUT_PULLUP 3*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, PULL_DOWN},       /*DIO_CONST_INPUT_PULLDOWN 4*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, OFF},             /*DIO_CONST_INPUT 5*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, PULL_UP},        /*CONST_DIO_CONST_INPUT_PULLUP 6*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, PULL_DOWN},      /*CONST_DIO_CONST_INPUT_PULLDOWN 7*/
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, OFF},            /*CONST_DIO_CONST_INPUT 8*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, PULL_UP},         /*DIO_OUTPUT_PULLUP 9*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, PULL_DOWN},       /*DIO_OUTPUT_PULLDOWN 10*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, OFF},             /*DIO_OUTPUT 11*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, PULL_UP},        /*DIO_CONST_OUTPUT_PULLUP 12*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, PULL_DOWN},      /*DIO_CONST_OUTPUT_PULLDOWN 13*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, OFF},            /*DIO_CONST_OUTPUT 14*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, PULL_UP},       /*CONST_DIO_CONST_OUTPUT_PULLUP 15*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, PULL_DOWN},     /*CONST_DIO_CONST_OUTPUT_PULLDOWN 16*/ 
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, OFF},           /*CONST_DIO_CONST_OUTPUT 17*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, PULL_UP},       /*ANALOG_INPUT_PULLUP 18*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, PULL_DOWN},     /*ANALOG_INPUT_PULLDOWN 19*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_ON, OFF},           /*ANALOG_INPUT 20*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, PULL_UP},      /*ANALOG_CONST_INPUT_PULLUP 21*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, PULL_DOWN},    /*ANALOG_CONST_INPUT_PULLDOWN 22*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_ON, OFF},          /*ANALOG_CONST_INPUT 23*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, PULL_UP},     /*CONST_ANALOG_CONST_INPUT_PULLUP 24*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, PULL_DOWN},   /*CONST_ANALOG_CONST_INPUT_PULLDOWN 25*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_OFF, STD_OFF, OFF},         /*CONST_ANALOG_CONST_INPUT 26*/ 
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, PULL_UP},      /*ANALOG_OUTPUT_PULLUP 27*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, PULL_DOWN},    /*ANALOG_OUTPUT_PULLDOWN 28*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_ON, OFF},          /*ANALOG_OUTPUT 29*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, PULL_UP},     /*ANALOG_CONST_OUTPUT_PULLUP 30*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, PULL_DOWN},   /*ANALOG_CONST_OUTPUT_PULLDOWN 31*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_ON, OFF},         /*ANALOG_CONST_OUTPUT 32*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, PULL_UP},    /*CONST_ANALOG_CONST_OUTPUT_PULLUP 33*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, PULL_DOWN},  /*CONST_ANALOG_CONST_OUTPUT_PULLDOWN 34*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_OFF, STD_OFF, OFF},        /*CONST_ANALOG_CONST_OUTPUT 35*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, PULL_UP},         /*CONST_DIO_INPUT_PULLUP 36*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, PULL_DOWN},       /*CONST_DIO_INPUT_PULLDOWN 37*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, OFF},             /*CONST_DIO_INPUT 38*/
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, PULL_UP},        /*CONST_DIO_OUTPUT_PULLUP 39*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, PULL_DOWN},      /*CONST_DIO_OUTPUT_PULLDOWN 40*/  
      {PORT_PIN_MODE_DIO, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, OFF},            /*CONST_DIO_OUTPUT 41*/
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, PULL_UP},      /*CONST_ANALOG_INPUT_PULLUP 42*/ 
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, PULL_DOWN},    /*CONST_ANALOG_INPUT_PULLDOWN 43*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_IN, STD_HIGH, STD_ON, STD_OFF, OFF},          /*CONST_ANALOG_INPUT 44*/ 
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, PULL_UP},     /*CONST_ANALOG_OUTPUT_PULLUP 45*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, PULL_DOWN},   /*CONST_ANALOG_OUTPUT_PULLDOWN 46*/  
      {PORT_PIN_MODE_ANALOG, PORT_PIN_OUT, STD_HIGH, STD_ON, STD_OFF, OFF},         /*CONST_ANALOG_OUTPUT 47*/   
  };   

/*JTAG must be assigned by null pointer to avoid changing thier dubugging configuration*/
/*configurations of this application task*/   
const Port_ConfigType Port_Configuration = {
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA0*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA1*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA2*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA3*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA6*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PA7*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB0*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB1*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB2*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB3*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB6*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PB7*/
      NULL_PTR,                                                             /*PC0 JTAG*/
      NULL_PTR,                                                             /*PC1 JTAG*/
      NULL_PTR,                                                             /*PC2 JTAG*/
      NULL_PTR,                                                             /*PC3 JTAG*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PC4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PC5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PC6*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PC7*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD0*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD1*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD2*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD3*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD6*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PD7 Unlock the GPIOCR register*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE0*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE1*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE2*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE3*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE6*/  
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PE7*/  
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF0 Unlock the GPIOCR register*/
      &Port_AllDifferentConfigurations[CONST_DIO_CONST_OUTPUT],             /*PF1*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF2*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF3*/
      &Port_AllDifferentConfigurations[CONST_DIO_CONST_INPUT_PULLUP],       /*PF4*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF5*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF6*/
      &Port_AllDifferentConfigurations[DEFAULT],                            /*PF7*/  
  };