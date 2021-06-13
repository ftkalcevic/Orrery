#pragma once
#include "TMC2130_bitfields.h"

const uint8_t TMC_WRITE = 0x80;

enum EMicrosteps 
{
	FULLSTEP=8,
	HALFSTEP=7,
	QUARTERSTEP=6,
	STEP8=5,
	STEP16=4,
	STEP32=3,
	STEP64=2,
	STEP128=1,
	STEP256=0
};
	
class TMC2130
{
private:
	SPI_HandleTypeDef *hspi;
	double rsense;
	GCONF_t GCONF;
	CHOPCONF_t CHOPCONF;
	COOLCONF_t COOLCONF;
	IHOLD_IRUN_t IHOLD_IRUN;
	PWMCONF_t PWMCONF;
	double holdMultiplier;

	void CS_Select()
	{
		HAL_GPIO_WritePin(GPIO_SPI_NSS_GPIO_Port, GPIO_SPI_NSS_Pin, GPIO_PIN_RESET);
	}
	
	void CS_Deselect()
	{
		HAL_GPIO_WritePin(GPIO_SPI_NSS_GPIO_Port, GPIO_SPI_NSS_Pin, GPIO_PIN_SET);
	}

	void write( uint8_t address, uint32_t data )
	{
		uint8_t buffer[5];
		buffer[0] = address | TMC_WRITE;
		buffer[1] = ((uint8_t *)&data)[3];
		buffer[2] = ((uint8_t *)&data)[2];
		buffer[3] = ((uint8_t *)&data)[1];
		buffer[4] = ((uint8_t *)&data)[0];
		
		CS_Select();
		HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, buffer, 5, HAL_MAX_DELAY);
		CS_Deselect();
	}
	

public:
	TMC2130(SPI_HandleTypeDef *hSpi, double rsense)
	{
		this->hspi = hSpi;
		this->rsense = rsense;
		
		GCONF.sr = 0;	
		CHOPCONF.sr = 0x8008;	
		COOLCONF.sr = 0;	
		IHOLD_IRUN.sr = 0;	
		PWMCONF.sr = 0x00050480;
		
		holdMultiplier = 0.5;
	}
	
	void toff(uint32_t n)
	{
		CHOPCONF.toff = (n & 0b1111);
		write(CHOPCONF.address, CHOPCONF.sr);
	}
	
	void tbl(uint32_t n)
	{
		CHOPCONF.tbl = (n & 0b1111);
		write(CHOPCONF.address, CHOPCONF.sr);
	}
	void rms_current(uint32_t mA)		// Set motor RMS current
	{
		// From https://teemuatlut.github.io/TMCStepper/_t_m_c_stepper_8cpp_source.html
		uint8_t CS = 32.0*1.41421*mA/1000.0*(rsense+0.02)/0.325 - 1;
		
		// If Current Scale is too low, turn on high sensitivity R_sense and calculate again
		if (CS < 16) 
		{
			CHOPCONF.vsense = true;
			CS = 32.0*1.41421*mA/1000.0*(rsense+0.02)/0.180 - 1;
		} 
		else 
		{ 
			// If CS >= 16, turn off high_sense_r
			CHOPCONF.vsense = false;
		}
  
	   if (CS > 31)
		 CS = 31;
  
		IHOLD_IRUN.irun = CS;
		IHOLD_IRUN.ihold = CS * holdMultiplier;
	
		write(CHOPCONF.address, CHOPCONF.sr);
		write(IHOLD_IRUN.address, IHOLD_IRUN.sr);
	}
	
	void microsteps(EMicrosteps s)         // Set microsteps to 1/16th
	{
		CHOPCONF.mres = s & 0b1111;
		write(CHOPCONF.address, CHOPCONF.sr);
	}
	
	
	void I_scale_analog(uint32_t n)		// AIN 
	{
		GCONF.i_scale_analog = n & 1;
		write(GCONF.address, GCONF.sr);		
	}
	
	void en_pwm_mode(uint32_t n)		// Toggle stealthChop on TMC2130/2160/5130/5160
	{
		GCONF.en_pwm_mode = n & 1;
		write(GCONF.address, GCONF.sr);		
	}
		
	void pwm_autoscale(uint32_t n)		// Needed for stealthChop
	{
		PWMCONF.pwm_autoscale = n & 1;
		write(PWMCONF.address, PWMCONF.sr);		
	}
	
	void Init()
	{
		toff(8); //off_time(8);
		tbl(1); //blank_time(24);		
	}
};



/*


Before
GCONF=0
IHOLD_IRUN=0
XDIRECT=0
DCCTRL=0
VDCMIN=0
CHOPCONF=8008
COOLCONF=0
PWMCONF=50480

After
GCONF=4
IHOLD_IRUN=201
XDIRECT=0
DCCTRL=0
VDCMIN=0
CHOPCONF=8028005
COOLCONF=0
PWMCONF=50480

*/