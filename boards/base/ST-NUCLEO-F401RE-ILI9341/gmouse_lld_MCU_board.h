/*
 * Copyright (c) 2015 dora38
 *
 * MIT License: http://opensource.org/licenses/MIT
 *
 */

#ifndef _LLD_GMOUSE_MCU_BOARD_H
#define _LLD_GMOUSE_MCU_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_MCU_PEN_CALIBRATE_ERROR		8
#define GMOUSE_MCU_PEN_CLICK_ERROR			6
#define GMOUSE_MCU_PEN_MOVE_ERROR			4
#define GMOUSE_MCU_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_MCU_FINGER_CLICK_ERROR		18
#define GMOUSE_MCU_FINGER_MOVE_ERROR		14
#define GMOUSE_MCU_Z_MIN					0
#define GMOUSE_MCU_Z_MAX					1
#define GMOUSE_MCU_Z_TOUCHON				1
#define GMOUSE_MCU_Z_TOUCHOFF				0

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_MCU_BOARD_DATA_SIZE			0

extern gfxMutex bus_mutex;

static const ADCConversionGroup adcgrpcfgX = {
  FALSE,
  1,
  0,
  0,
  /* HW dependent part.*/
  0,
  ADC_CR2_SWSTART,
  0,
  0,
  ADC_SQR1_NUM_CH(1),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN4)
};

static const ADCConversionGroup adcgrpcfgY = {
  FALSE,
  1,
  0,
  0,
  /* HW dependent part.*/
  0,
  ADC_CR2_SWSTART,
  0,
  0,
  ADC_SQR1_NUM_CH(1),
  0,
  ADC_SQR3_SQ1_N(ADC_CHANNEL_IN1)
};

static inline void set_touch_mode_X(void) {
	// assume the LCD is not used
	// YP, YM = output push/pull
	// XIN, XP = input analog
	palSetPad(GPIOA, GPIOA_TOUCH_YP);
	palClearPad(GPIOA, GPIOA_TOUCH_YM);
	palSetGroupMode(GPIOA, PAL_PORT_BIT(GPIOA_TOUCH_YP) | PAL_PORT_BIT(GPIOA_TOUCH_YM), 0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOA, GPIOA_TOUCH_XIN, PAL_MODE_INPUT_ANALOG | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOB, GPIOB_TOUCH_XP, PAL_MODE_INPUT_ANALOG | PAL_STM32_OSPEED_HIGHEST);
}

static inline void set_touch_mode_Y(void) {
	// assume the LCD is not used
	// XP, XM = output push/pull
	// YIN, YM = input analog
	palSetPad(GPIOB, GPIOB_TOUCH_XP);
	palClearPad(GPIOA, GPIOA_TOUCH_XM);
	palSetPadMode(GPIOB, GPIOB_TOUCH_XP, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOA, GPIOA_TOUCH_XM, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOA, GPIOA_TOUCH_YIN, PAL_MODE_INPUT_ANALOG | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOA, GPIOA_TOUCH_YM, PAL_MODE_INPUT_ANALOG | PAL_STM32_OSPEED_HIGHEST);
}

static inline void set_touch_mode_Z(void) {
	// assume the LCD is not used
	// XP = output push/pull
	// YIN = input pull down
	// XM, YM = input
	palSetPad(GPIOB, GPIOB_TOUCH_XP);
	palSetPadMode(GPIOB, GPIOB_TOUCH_XP, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetPadMode(GPIOA, GPIOA_TOUCH_YIN, PAL_MODE_INPUT_PULLDOWN | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOA, PAL_PORT_BIT(GPIOA_TOUCH_XM) | PAL_PORT_BIT(GPIOA_TOUCH_YM), 0, PAL_MODE_INPUT | PAL_STM32_OSPEED_HIGHEST);
}

static inline void set_lcd_mode(void) {
	// XP, XM, YP, YM = output push/pull
	palSetPadMode(GPIOB, GPIOB_TOUCH_XP, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
	palSetGroupMode(GPIOA, PAL_PORT_BIT(GPIOA_TOUCH_XM) | PAL_PORT_BIT(GPIOA_TOUCH_YP) | PAL_PORT_BIT(GPIOA_TOUCH_YM),
		0, PAL_MODE_OUTPUT_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
}


static bool_t init_board(GMouse *m, unsigned driverinstance) {
	(void)m;
	(void)driverinstance;

	if (driverinstance != 0) {
		return FALSE;
	}

	adcStart(&ADCD1, 0);
	return TRUE;
}

static bool_t read_xyz(GMouse *m, GMouseReading *prd) {
	adcsample_t sample;
	msg_t ret = 0;

	(void)m;
	(void)prd;

	gfxMutexEnter(&bus_mutex);

	prd->buttons = 0;
	prd->z = 0;

	set_touch_mode_Z();
	chThdSleepMilliseconds(1);
	if (palReadPad(GPIOA, GPIOA_TOUCH_YIN)) {
		// touching
		prd->z = 1;
		set_touch_mode_X();
		gfxSleepMilliseconds(1);
		ret = adcConvert(&ADCD1, &adcgrpcfgX, &sample, 1) || ret;
		prd->x = sample;

		set_touch_mode_Y();
		gfxSleepMilliseconds(1);
		ret = adcConvert(&ADCD1, &adcgrpcfgY, &sample, 1) || ret;
		prd->y = sample;
	}

	set_lcd_mode();
	gfxMutexExit(&bus_mutex);

	if (ret != 0) {
		// error
		prd->x = prd->y = prd->z = 0;
	}
	return TRUE;
}

#endif /* _LLD_GMOUSE_MCU_BOARD_H */
