/*
 * button.h
 *
 *  Created on: June 04, 2018
 *      Author: Andrei Diea
 */
#ifndef BUTTON_H
#define BUTTON_H

#define BTN_0	12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1	13
#define NUMBER_BUTTONS 2

typedef enum{
	eButtonLeft = BTN_1,
	eButtonRight = BTN_0,
}eButton;

typedef enum {
	eBtn_NotPressed,
	eBtn_Pressed,
	eBtn_Released,
	eBtn_LongPress,
}eButtonPress;

#endif /*BUTTON_H*/