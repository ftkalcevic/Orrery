#include "Orrery.h"
#include "SH1106.h"
#include "Planets.h"
#include "AnalogKeys.h"
#include <string>
#include <time.h>
#include "TMC2130.h"
#include "RTC_time_t.h"	

#define RSENSE	1.2

#define PLANET_COUNT	6

/*
Stepper		20 steps
Microsteps	8
stepper gearbox ratio	99.3:1
gearbox pinion	20
drive			80

earth-spin
	bevel	15:30
	elbow	15:15
moon=rotation
	bevel	20:40
	elbow	22:22

how does earth-rotation effect earth-spin and moon-rotation?
	1 earth rotation is equivalent to -1 shaft rotation
	
 */

#define STEPPER_STEPS_PER_REV	20.0
#define MICROSTEPS				8.0
#define STEPPER_GEAR			10.0		// Guess to get 99.3 ratio
#define STEPPER_GEARBOX_GEAR	993.0
#define GEARBOX_GEAR			20.0
#define SHAFT_GEAR				80.0

#define SHAFT_SCALE				(STEPPER_STEPS_PER_REV * MICROSTEPS * STEPPER_GEARBOX_GEAR / STEPPER_GEAR * SHAFT_GEAR / GEARBOX_GEAR)

class Planet
{
	double angle;
	double scale;
	int velocity;
	
public:
	Planet(double Scale)
	{
		scale = Scale;
		angle = 0;
		velocity = 0;
	}
	
	void SetPosition(double newAngle)
	{
		angle = newAngle;
	}
	void UpdatePosition(double newAngle)
	{
		double delta = newAngle - angle;
		delta += (delta > 180) ? -360 : (delta < -180) ? 360 : 0;	// delta between -pi and pi
		angle = newAngle;
		
		velocity = delta * scale;	// truncate to nearest int
		velocity = delta * 100;
	}
	int Velocity()
	{
		return velocity;
	}
};

static Planet planets[PLANET_COUNT] =
{ 
	{ /* Mercury    */ SHAFT_SCALE },
	{ /* Venus		*/ SHAFT_SCALE },
	{ /* Earth		*/ SHAFT_SCALE },
	{ /* Earth-Spin	*/ SHAFT_SCALE },
	{ /* Moon		*/ SHAFT_SCALE },
	{ /* Mars		*/ SHAFT_SCALE },
	//{ /* Jupiter	*/ SHAFT_SCALE },
	//{ /* Saturn		*/ SHAFT_SCALE },
	//{ /* Uranus		*/ SHAFT_SCALE },
	//{ /* Neptune	*/ SHAFT_SCALE },
};

SH1106 display;
AnalogKeys keys(&hadc1);
TMC2130 stepperDriver(&hspi2, RSENSE);

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

extern "C" void TIM2_IRQHandler()
{
	static int n = 0;
	__HAL_TIM_CLEAR_IT(&htim2, TIM_IT_UPDATE);
	
	// Earth rotation 1
	// Moon around earth 28 days
	// earth around sun 365
	// venus around sun 225
	// mercury around sun 88 days
	//if ( n % 88 == 0 ) 
	HAL_GPIO_WritePin(GPIO_STEP4_GPIO_Port,  GPIO_STEP4_Pin, GPIO_PIN_SET);			// Mercury
	//if ( n % 225 == 0 ) 
	HAL_GPIO_WritePin(GPIO_STEP3_GPIO_Port,  GPIO_STEP3_Pin, GPIO_PIN_SET);			// Venus
	//if ( n % 365 == 0 )  
	HAL_GPIO_WritePin(GPIO_STEP2_GPIO_Port,  GPIO_STEP2_Pin, GPIO_PIN_SET);		// Earth around Sun
	HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_SET);								// Earth axis 1:2 diff ratio
	//if ( n % 28 == 0 ) 
	if ( n % 2 == 0 )	HAL_GPIO_WritePin(GPIO_STEP0_GPIO_Port,  GPIO_STEP0_Pin, GPIO_PIN_SET);			// Moon around earth 1:2 diff ratio
//HAL_Delay(1); // ms
	HAL_GPIO_WritePin(GPIO_STEP4_GPIO_Port,  GPIO_STEP4_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_STEP3_GPIO_Port,  GPIO_STEP3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_STEP2_GPIO_Port,  GPIO_STEP2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_STEP1_GPIO_Port,  GPIO_STEP1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_STEP0_GPIO_Port,  GPIO_STEP0_Pin, GPIO_PIN_RESET);
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
	
//  Estimate calculation time	
//	{
//		uint32_t dwtStart = DWT->CYCCNT;
//		for ( int i = 0; i < 100; i++ )
//			CalculatePlanets();
//		uint32_t dwtEnd = DWT->CYCCNT;
//	
//		uint32_t dwtTotal = (dwtEnd - dwtStart)/100/(SYSTEM_TICKS_1US);
//		char buf[20];
//		snprintf(buf, sizeof(buf), "%d", dwtTotal);                                                                                                                                                                                                                                                                                                         
//		display.Text(0, 24, buf);
//		display.Refresh();
//	}

	
	struct tm tm_time;
	memset(&tm_time, 0, sizeof(tm_time));
	time_t time_speed = 86400;		// how fast are we moving in time - 1 real time.  86400 is 1day in 1 second.
	time_t current_time = 0;
	double planets_position[PLANET_COUNT];

	HAL_GPIO_WritePin(GPIO_DIR0_GPIO_Port, GPIO_DIR0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_DIR1_GPIO_Port,  GPIO_DIR1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_DIR2_GPIO_Port,  GPIO_DIR2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIO_DIR3_GPIO_Port,  GPIO_DIR3_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIO_DIR4_GPIO_Port,  GPIO_DIR4_Pin, GPIO_PIN_SET);
	
	HAL_TIM_Base_Start_IT(&htim2);
		
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

		
		if(RTC_time_t::TimeUpdate)
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

			if (bFirst)
			{
				current_time = real_time;

				CalculatePlanets(&real_time_tm, planets_position, PLANET_COUNT);
				for(int i = 0 ; i < PLANET_COUNT ; i++)
					planets[i].SetPosition(planets_position[i]);
				
				current_time += time_speed;
				gmtime_r(&current_time, &tm_time);
				CalculatePlanets(&tm_time, planets_position, PLANET_COUNT);
			}
			else
			{
				// Update motor speeds
				printf("%08X %04d/%02d/%02d %02d:%02d:%02d ", *(((uint32_t*)&current_time)+0), tm_time.tm_year+1900, tm_time.tm_mon+1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
				for(int i = 0 ; i < PLANET_COUNT ; i++)
				{
					planets[i].UpdatePosition(planets_position[i]);
					printf("%3d.%02d:", (int)(planets_position[i]), (int)((planets_position[i]*100 - (int)(planets_position[i]*100))*100) );
					printf("%d ", planets[i].Velocity());
					//if (planets[i].Velocity() < 0)
					//	break;
				}
				printf("\n");
				
				// Compute next
				current_time += time_speed;
				gmtime_r(&current_time, &tm_time);
				CalculatePlanets(&tm_time, planets_position, PLANET_COUNT);
			}
			
			bFirst = false;
		}
	}
}