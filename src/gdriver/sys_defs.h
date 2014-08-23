/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

/**
 * @file    src/gdriver/sys_defs.h
 *
 * @addtogroup GINPUT
 *
 * @brief		Module to support registering and unregistering of drivers
 *
 * @details		GDRIVER provides a generalized way of defining and registering drivers.
 *
 * @note		There are many different types of drivers and GDRIVER can handle any
 * 				type of driver defined by the uGFX system.
 *
 * @note		GDRIVER supports multiple drivers for one type of device. eg a SSD1289 LCD
 * 				driver simultaneously with a framebuffer driver.
 * @note		GDRIVER supports multiple instances of a single driver. eg 2 SSD1289 LCD's.
 * @note		If there is only a single device of a particular type it will automatically
 *				register that device (it only needs to be included in the build, no special
 *				configuration is required)
 * @note		This module sys_defs.h file is NOT included in the general gfx.h file.
 * 				Instead it is included in each driver type's driver API.
 *
 * @pre			GFX_USE_GDRIVER must be set to TRUE in your gfxconf.h
 *
 * @{
 */

#ifndef _GDRIVER_H
#define _GDRIVER_H

#if GFX_USE_GDRIVER || defined(__DOXYGEN__)

/*===========================================================================*/
/* Type definitions                                                          */
/*===========================================================================*/

#define GDRIVER_TYPE_DISPLAY		'g'		// @< A graphics display
#define GDRIVER_TYPE_MOUSE			'm'		// @< A mouse
#define GDRIVER_TYPE_TOUCH			'm'		// @< A touch display (equivalent to a mouse)
#define GDRIVER_TYPE_TOGGLE			't'		// @< A toggle device eg GPIO pins, switches etc
#define GDRIVER_TYPE_DIAL			'd'		// @< A analog or digit dial (ranges in value from a minimum to a maximum)
#define GDRIVER_TYPE_KEYBOARD		'k'		// @< A keyboard
#define GDRIVER_TYPE_BLOCK			'b'		// @< A block device
#define GDRIVER_TYPE_STRING			's'		// @< A device that returns strings of data

/**
 * @brief	All runtime driver structures start with this structure
 *
 * @note	This structure (and any additional structure memory) is allocated
 * 			dynamically by the system for each driver instance.
 */
typedef struct GDriver {
	struct GDriver *			driverchain;
	const struct GDriverVMT *	vmt;
} GDriver;

/**
 * @brief	All driver VMT's start with this structure.
 */
typedef struct GDriverVMT {
	uint16_t	type;																// @< What type of driver this is
	uint16_t	flags;																// @< Flags for the driver. Meaning is specific to each driver type.
	uint32_t	objsize;															// @< How big the runtime driver structure is
	bool_t		(*init)(GDriver *driver, int driverinstance, int systeminstance);	// @< Initialise the driver.
																					//		driverinstance is the instance 0..n of this driver.
																					//		systeminstance is the instance 0..n of this type of device.
	void		(*deinit)(GDriver *driver);											// @< De-initialise the driver
} GDriverVMT;

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

	/**
	 * @brief	Register a new driver instance.
	 * @return	The runtime driver structure or NULL if it fails.
	 *
	 * @param[in]	vmt		The driver's vmt
	 */
	GDriver *gdriverRegister(const GDriverVMT *vmt);

	/**
	 * @brief	UnRegister a driver instance.
	 *
	 * @param[in]	driver	The driver instance's runtime structure
	 */
	void gdriverUnRegister(GDriver *driver);

	/**
	 * @brief	Get the driver for a particular instance of a type of device
	 * @return	The runtime driver structure or NULL if it fails.
	 *
	 * @param[in]	type		The type of driver to find
	 * @param[in]	instance	The instance (0..n) to find
	 */
	GDriver *gdriverGetInstance(uint16_t type, int instance);

	/**
	 * @brief	Get the count of instances of a type of device
	 * @return	The instance count.
	 *
	 * @note	Valid instance numbers are then 0 .. count-1
	 *
	 * @param[in]	type		The type of driver to find
	 */
	int gdriverInstanceCount(uint16_t type);

	/**
	 * @brief	Get the next driver for a type of device
	 * @return	The runtime driver structure or NULL if there are no more.
	 *
	 * @param[in]	type		The type of driver to find
	 * @param[in]	driver		The last driver returned or NULL to start again
	 */
	GDriver *gdriverGetNext(uint16_t type, GDriver *driver);

#ifdef __cplusplus
}
#endif

#endif /* GFX_USE_GDRIVER */

#endif /* _GDRIVER_H */
/** @} */
