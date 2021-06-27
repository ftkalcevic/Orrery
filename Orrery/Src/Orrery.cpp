#include "Orrery.h"
#include "SH1106.h"
#include "Planets.h"
#include "PlanetMotion.h"
#include "AnalogKeys.h"
#include <string>
#include <time.h>
#include "TMC2130.h"
#include "RTC_time_t.h"	

#define RSENSE	1.2

#define PLANET_COUNT	7


static PlanetMotion planets[PLANET_COUNT] =
{ 
	{ /* Mercury    */ SHAFT_SCALE,		GPIO_STEP4_GPIO_Port,  GPIO_STEP4_Pin, GPIO_DIR4_GPIO_Port,  GPIO_DIR4_Pin, EDir::Forward },
	{ /* Venus		*/ SHAFT_SCALE,		GPIO_STEP3_GPIO_Port,  GPIO_STEP3_Pin, GPIO_DIR3_GPIO_Port,  GPIO_DIR3_Pin, EDir::Forward },
	{ /* Earth		*/ SHAFT_SCALE,		GPIO_STEP2_GPIO_Port,  GPIO_STEP2_Pin, GPIO_DIR2_GPIO_Port,  GPIO_DIR2_Pin, EDir::Forward },
	{ /* Earth-Spin	*/ SHAFT_SCALE/2, GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_DIR1_GPIO_Port,  GPIO_DIR1_Pin, EDir::Forward },
	{ /* Moon		*/ SHAFT_SCALE/2, GPIO_STEP0_GPIO_Port,  GPIO_STEP0_Pin, GPIO_DIR0_GPIO_Port,  GPIO_DIR0_Pin, EDir::Forward },
	{ /* Mars		*/ SHAFT_SCALE,		GPIO_STEP9_GPIO_Port,  GPIO_STEP9_Pin, GPIO_DIR9_GPIO_Port,  GPIO_DIR9_Pin, EDir::Forward },
	{ /* Jupiter	*/ SHAFT_SCALE,		GPIO_STEP8_GPIO_Port,  GPIO_STEP8_Pin, GPIO_DIR8_GPIO_Port,  GPIO_DIR8_Pin, EDir::Forward },
	//{ /* Saturn		*/ SHAFT_SCALE },
	//{ /* Uranus		*/ SHAFT_SCALE },
	//{ /* Neptune	*/ SHAFT_SCALE },
};

SH1106 display;
AnalogKeys keys(&hadc1);
TMC2130 stepperDriver(&hspi2, RSENSE);
static volatile bool stepperUpdate = false;

#define DWT_TIMER
#ifdef DWT_TIMER
#define CFG_CPU_FREQ	72000000
#define SYSTEM_TICKS_1US    ((CFG_CPU_FREQ + 500000)  / 1000000)      // number of system ticks in 1us
#define SYSTEM_TICKS_01US   ((CFG_CPU_FREQ + 5000000) / 10000000)     // number of system ticks in 0.1us (rounding needed for sys frequencies that are not multiple of 10MHz)

void delaysInit(void)
{
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
  DWT->CYCCNT = 0;
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_01us(uint16_t nb)
{
  volatile uint32_t dwtStart = DWT->CYCCNT;
  volatile uint32_t dwtTotal = (SYSTEM_TICKS_01US * nb) - 10;
  while ((DWT->CYCCNT - dwtStart) < dwtTotal);
}

void delay_us(uint16_t nb)
{
  volatile uint32_t dwtStart = DWT->CYCCNT;
  volatile uint32_t dwtTotal = (SYSTEM_TICKS_1US * nb) - 10;
  while ((DWT->CYCCNT - dwtStart) < dwtTotal);
}

void delay_ms(uint32_t ms)
{
  while (ms--) {
    delay_us(1000);
  }
}
#endif

extern "C" void TIM3_IRQHandler()
{
	__HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE);
	stepperUpdate = true;
}

extern "C" void TIM2_IRQHandler()
{
	static int n = 0;
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
	
	HAL_GPIO_WritePin(GPIO_RGB_LED_GPIO_Port, GPIO_RGB_LED_Pin, GPIO_PIN_SET);
	
	for (int i = 0; i < PLANET_COUNT; i++)
		planets[i].Step(n);
	for (int i = 0; i < PLANET_COUNT; i++)
		planets[i].Unstep();
	HAL_GPIO_WritePin(GPIO_RGB_LED_GPIO_Port, GPIO_RGB_LED_Pin, GPIO_PIN_RESET);

	n++;
}

void Orrery::main()
{
	#ifdef DEBUG
		printf("Starting orrery\n");
	#endif
	
	#ifdef DWT_TIMER
	delaysInit();
	#endif
		
	keys.Start();
	display.init();

	display.Text(0, 0, "Starting Orrery...");
	display.Refresh();
	
	HAL_GPIO_WritePin(GPIO_ENABLE_GPIO_Port, GPIO_ENABLE_Pin, GPIO_PIN_RESET);
	
	stepperDriver.toff(5);					// Enables driver in software
	//stepperDriver.I_scale_analog(false);
	stepperDriver.rms_current(70);			// Set motor RMS current
	stepperDriver.microsteps(STEP8);		// Set microsteps to 1/16th
	stepperDriver.intpol(true);				// interpolation
	stepperDriver.en_pwm_mode(true);		// Toggle stealthChop on TMC2130/2160/5130/5160
	stepperDriver.pwm_autoscale(true);		// Needed for stealthChop

	
	struct tm tm_time;
	memset(&tm_time, 0, sizeof(tm_time));
	time_t time_speed = 86400/SECONDS_PER_DAY;		// how fast are we moving in time - 1 real time.  86400 is 1day in 1 second.
	time_t current_time = 0;
	double planets_position[PLANET_COUNT];

	
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
		
	bool bFirst = true;
	uint16_t lastKeyPress = 0;
	uint16_t n = 0;
	for (;;)
	{
		uint16_t KeyPress = keys.keys;
		if (KeyPress != lastKeyPress)
		{
			char buf[20];
			snprintf(buf, sizeof(buf), "%04X", KeyPress );
			//display.Clear();
			display.Text(0, 0, buf);
			display.Refresh();
			lastKeyPress = KeyPress;
		}

		
		if (RTC_time_t::TimeUpdate)
		{
			RTC_time_t::TimeUpdate = false;
			
			// Refresh display
			time_t real_time = RTC_time_t::GetTime();
			struct tm real_time_tm;
			gmtime_r(&real_time, &real_time_tm);
			char buf[20];
			snprintf(buf, sizeof(buf), "%02d:%02d:%02d", real_time_tm.tm_hour, real_time_tm.tm_min, real_time_tm.tm_sec);
			display.Text(0, 10, buf);
			display.Refresh();
		}
		
		if (stepperUpdate)
		{
			stepperUpdate = false;
			if (bFirst)
			{
				current_time = RTC_time_t::GetTime();
				gmtime_r(&current_time, &tm_time);

				CalculatePlanets(&tm_time, planets_position, PLANET_COUNT);
				for (int i = 0; i < PLANET_COUNT; i++)
					planets[i].SetPosition(planets_position[i]);

				current_time += time_speed/STEPPER_UPDATES_PER_SECOND;
				gmtime_r(&current_time, &tm_time);
				CalculatePlanets(&tm_time, planets_position, PLANET_COUNT);
			}
			else
			{
				// Update motor speeds
				for (int i = 0; i < PLANET_COUNT; i++)
					planets[i].UpdatePosition(planets_position[i]);
				
//				printf("%08X %04d/%02d/%02d %02d:%02d:%02d ", *(((uint32_t*)&current_time) + 0), tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
//				for (int i = 0; i < PLANET_COUNT; i++)
//				{
//					//planets[i].UpdatePosition(planets_position[i]);
//					printf("%3d.%02d:", (int)(planets_position[i]), (int)((planets_position[i] * 100 - (int)(planets_position[i] * 100)) * 100));
//					//printf("%d->%dd%d:", planets[i].position, planets[i].newPosition, planets[i].delta);
//					printf("%d ", planets[i].velocity);
//					//if (planets[i].Velocity() < 0)
//					//	break;
//				}
//				printf("\n");
				
				// Compute next
				current_time += time_speed/STEPPER_UPDATES_PER_SECOND;
				gmtime_r(&current_time, &tm_time);
				CalculatePlanets(&tm_time, planets_position, PLANET_COUNT);
			}
			
			bFirst = false;
		}
	}
}