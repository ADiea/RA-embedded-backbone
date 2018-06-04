#ifndef BUTTON_H_
#define BUTTON_H_

#include "S32K144_small.h"
#include "gpio.h"

#define BTN_0		GPIO_Pin_12        /* Port PTC12, bit 12: FRDM EVB input from BTN0 [SW2] */
#define BTN_1		GPIO_Pin_13
#define NUMBER_BUTTONS 2

typedef enum {
	eBtn_NotPressed,
	eBtn_Pressed,
	eBtn_Released,
	eBtn_LongPress,
}eButtonPress;

typedef enum{
	eButtonLeft = BTN_1,
	eButtonRight = BTN_0,
}eButton;

void initLeftButton();
void initRightButton();
void initButtons();

#endif /* BUTTON_H_ */
