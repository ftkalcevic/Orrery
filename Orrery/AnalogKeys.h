#pragma once

#define CHANNELS		2
#define AVG_BUFFER		4


enum EKeyCodes
{
	KEY_NONE = 0,
	KEY_JOYSTICK_LEFT,
	KEY_JOYSTICK_UP,
	KEY_JOYSTICK_RIGHT,
	KEY_JOYSTICK_DOWN,
	KEY_JOYSTICK_CENTER,
	KEY_B1,
	KEY_B2,
	KEY_B3
};


struct SKeyMap
{
	EKeyCodes keyCode;
	uint16_t adcThreshold;
};


class AnalogKeys
{
	uint16_t adc_buffer[CHANNELS * AVG_BUFFER];
	
public:
	AnalogKeys(ADC_HandleTypeDef *hAdc)
		: hadc( hAdc )
	{
		AnalogKeys::instance = this;
	}
	
	ADC_HandleTypeDef *hadc;
	static AnalogKeys *instance;
	
	void HandleInterrupt();
	void Start();
	EKeyCodes ProcessKeys(uint16_t *buf, int count, SKeyMap *map);
	
	uint16_t keys;
};