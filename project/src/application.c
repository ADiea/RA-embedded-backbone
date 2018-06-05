/*
 * hello.c              Copyright NXP 2016
 * Description:  Simple program to exercise GPIO
 * 2015 Mar 31 S Mihalik/ O Romero - initial version
 *
 */

/*Modified 09.05.2018 by ADiea for simplification of code base*/

#include "system.h"
#include "gpio.h"
#include "timer.h"
#include "interrupt.h"

#include "button.h"
#include "delay.h"
#include "rgbLED.h"
#include "potentiometer.h"

uint8_t g_whichLED = LED_RED;
uint8_t g_factorR = 50, g_factorG = 50, g_factorB = 50;
uint8_t *g_whichColor = &g_factorR;

// if left button pressed, change led color
void onLeftBtnPressed(void)
{
	switch(g_whichLED)
	{
		case LED_RED:
			g_whichLED = LED_BLUE;
			g_whichColor = &g_factorB;
			break;
		case LED_BLUE:
			g_whichLED = LED_GREEN;
			g_whichColor = &g_factorG;
			break;
		default:
			g_whichLED = LED_RED;
			g_whichColor = &g_factorR;
	}
}

// if right button pressed, increment factorX corresponding to color X given by whichLED
void onRightBtnPressedIncrement(void)
{
	*g_whichColor += 30;
}

// if right button pressed, reset OTHER colors values to 0 (so we can see only current color)
void onRightBtnPressedResetValue(void)
{
	if(&g_factorR != g_whichColor)
		g_factorR = 0;

	if(&g_factorG != g_whichColor)
		g_factorG = 0;

	if(&g_factorB != g_whichColor)
		g_factorB = 0;
}

//this is the application entry point it is called from sysInit()
void applicationEntryPoint(void)
{
  uint32_t potValue;
  //perform initialization of needed modules. In the background various peripherals get inited
  initLED(eLEDCtrl_PWM);
  initSystemButtons();
  initPotentiometer();

  //rgister callback functions for left and right buttons
  registerBtnPressFn(eButtonLeft, onLeftBtnPressed);
  //registerBtnPressFn(eButtonRight, onRightBtnPressedIncrement);
  registerBtnPressFn(eButtonRight, onRightBtnPressedResetValue);

  //main application loop, our application has to set the color of the LED
  while(1)
  {
	//read the potentiometer ...
	potValue = (readPotentiometer() * MAX_LED_BRIGHTNESS) / MAX_POT_VALUE; //here we perform a int division we don't do (pot / max_pot) * max_led
	// ... and adjust the current color value between 0 and 255 (PWM factor)
	*g_whichColor = (uint8_t) potValue;

	//set current color
	setRgbLEDColor(g_factorR, g_factorG, g_factorB);
  }
}
