/*******************************************************************************
 * Module: Port
 * File Name: Port_Cfg.h
 * Description: TM4C123GH6PM Microcontroller header file contains port driver configuration 
 * Author: Kareem Haitham
*******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*module version 1.0.0*/
#define PORT_CFG_SW_MAJOR_VERSION                     (1U)
#define PORT_CFG_SW_MINOR_VERSION                     (0U)
#define PORT_CFG_SW_PATCH_VERSION                     (0U)

/*AUTOSAR version 4.0.3*/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION             (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION             (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION             (3U)

/*development error detect*/
#define PORT_DEV_ERROR_DETECT                         (STD_ON)

/*version info API*/
#define Port_SetPinMode_API                         (STD_ON)

/*version info API*/
#define PORT_VERSION_INFO_API                         (STD_ON)

/*48 pins can be configured in TM4C123GH6PM microcontroller*/
/*will be used in the port initialization to loop and initialize all pins */
/*pins that is not needed in my application will be initilized by default configuration*/
#define PORT_ALL_PINS_NUMBER                          (48U)

#endif 