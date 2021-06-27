#pragma once

#include <stdio.h>
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

#define ACCELERATION			10

namespace EDir
{
	enum EDir
	{
		Forward,
		Reverse
	};
}

class PlanetMotion
{
public:
	double angle;
	int32_t stepsPerRev;
	int velocity;
	int new_velocity;
	GPIO_TypeDef *port;
	int pin;
	int32_t position;
	uint32_t velocityCount;
	
public:
	PlanetMotion(double StepsPerRev, GPIO_TypeDef *PORT, int PIN, GPIO_TypeDef *DIR_PORT, int DIR_PIN, EDir::EDir dir)
	{
		stepsPerRev = StepsPerRev;
		angle = 0;
		velocity = 0;
		port = PORT;
		pin = PIN;
		position = 0;
		velocityCount = 0;
		
		HAL_GPIO_WritePin(DIR_PORT, DIR_PIN, dir == EDir::Forward ? GPIO_PIN_SET : GPIO_PIN_RESET);
	}
	
	void SetPosition(double newAngle)
	{
		angle = newAngle;
		position = newAngle * (double)stepsPerRev / 360.0;
		velocityCount = 0;
	}
	
	void UpdatePosition(double newAngle)
	{
		int32_t newPosition = newAngle * (double)stepsPerRev / 360.0;
		angle = newAngle;
		
		int32_t delta = newPosition - position;
		delta = delta % stepsPerRev;
		delta += (delta > stepsPerRev/2) ? -stepsPerRev : (delta < -stepsPerRev/2) ? stepsPerRev : 0;	// delta between -stepsPerRev/2 and stepsPerRev/2
		new_velocity = delta < 0 ? -delta : delta;	// velocity = steps per second
	}
	int Velocity()
	{
		return velocity;
	}
	bool Step( int nTick )
	{
		if (velocity != new_velocity)
		{
			if (velocity + ACCELERATION > new_velocity)
				velocity  = new_velocity;
			else
				velocity += ACCELERATION;
		}
		velocityCount += velocity;
		if (velocityCount > T2_FREQ)
		{
			HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
			velocityCount -= T2_FREQ;
			position++;
		}
		return false;
	}
	bool Unstep()
	{
		HAL_GPIO_WritePin(port,  pin, GPIO_PIN_RESET);
		return false;
	}
};


