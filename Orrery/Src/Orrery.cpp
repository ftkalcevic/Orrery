#include "Orrery.h"
#include "SH1106.h"
#include "Planets.h"
#include "AnalogKeys.h"
#include <string>
#include "TMC2130.h"

#define RSENSE	1.2

SH1106 display;
AnalogKeys keys(&hadc1);
TMC2130 stepperDriver(&hspi2, RSENSE);

volatile bool TimeUpdate = true;

void HAL_RTCEx_RTCEventCallback(RTC_HandleTypeDef *hrtc)
{
	TimeUpdate = true;
}

void Orrery::main()
{
	#ifdef DEBUG
		printf("Starting orrery\n");
	#endif
	
	keys.Start();
	display.init();

	display.Text(0, 0, "Starting Orrery...");
	display.Refresh();
	
	//HAL_GPIO_WritePin(GPIO_ENABLE_GPIO_Port, GPIO_ENABLE_Pin, GPIO_PIN_SET);
	
	stepperDriver.toff(5);					// Enables driver in software
	//stepperDriver.I_scale_analog(false);
	stepperDriver.rms_current(50);			// Set motor RMS current
	stepperDriver.microsteps(STEP16);		// Set microsteps to 1/16th
	stepperDriver.en_pwm_mode(true);		// Toggle stealthChop on TMC2130/2160/5130/5160
	stepperDriver.pwm_autoscale(true);		// Needed for stealthChop
	
	CalculatePlanets();

	HAL_GPIO_WritePin(GPIO_DIR0_GPIO_Port,  GPIO_DIR0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_DIR1_GPIO_Port,  GPIO_DIR1_Pin, GPIO_PIN_SET);
	uint16_t lastKeyPress = 0;
	uint16_t n = 0;
	for (;;)
	{
		uint16_t KeyPress = keys.keys;
		if (KeyPress != lastKeyPress)
		{
			char buf[20];
			snprintf(buf, sizeof(buf), "%04X", KeyPress );
			display.Clear();
			display.Text(0, 0, buf);
			display.Refresh();
			lastKeyPress = KeyPress;
		}
			
		//HAL_GPIO_TogglePin(GPIO_LED,  GPIO_STEP1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_STEP0_GPIO_Port,  GPIO_STEP0_Pin, GPIO_PIN_SET);
		HAL_Delay(1); // ms
		HAL_GPIO_WritePin(GPIO_STEP0_GPIO_Port,  GPIO_STEP0_Pin, GPIO_PIN_RESET);
		n++;
		if (n % 2 == 0)
		{
			HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_SET);
			HAL_Delay(1); // ms
			HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_RESET);
		}
		HAL_Delay(1); // ms
//		HAL_GPIO_TogglePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin);
//		HAL_Delay(1000); // ms
		
		if(TimeUpdate)
		{
			RTC_TimeTypeDef time;
			HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
			char buf[20];
			snprintf(buf, sizeof(buf), "%02d:%02d:%02d", time.Hours, time.Minutes, time.Seconds);
			display.Text(0, 10, buf);
			display.Refresh();
			TimeUpdate = false;
		}
		
	}
}