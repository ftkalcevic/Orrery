#include "Orrery.h"
#include "SH1106.h"
#include "Planets.h"
#include <string>
SH1106 display;


void Orrery::main()
{
	#ifdef DEBUG
		printf("Starting orrery\n");
	#endif
	
	display.init();

	display.Text(0, 0, "Starting Orrery...");
	display.Refresh();
	
	CalculatePlanets();

	HAL_GPIO_WritePin(GPIO_ENABLE_GPIO_Port, GPIO_ENABLE_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_DIR1_GPIO_Port,  GPIO_DIR1_Pin, GPIO_PIN_RESET);
	for (;;)
	{
		//HAL_GPIO_TogglePin(GPIO_LED,  GPIO_STEP1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_SET);
		HAL_Delay(1); // ms
		HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_RESET);
		HAL_Delay(100); // ms
		
//		HAL_GPIO_TogglePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin);
//		HAL_Delay(1000); // ms
	}
}