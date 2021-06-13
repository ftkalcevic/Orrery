#include "main.h"
#include "AnalogKeys.h"

AnalogKeys *AnalogKeys::instance = NULL;

static SKeyMap keys2[] =
{ 
	{  KEY_JOYSTICK_RIGHT, 359 },
	{  KEY_JOYSTICK_LEFT, 1124 },
	{  KEY_JOYSTICK_UP, 1968 },
	{  KEY_JOYSTICK_CENTER, 2802 },
	{  KEY_JOYSTICK_DOWN, 3646 },
	{  KEY_NONE, 0 }
};

static SKeyMap keys1[] =
{ 
	{  KEY_B3, 653 },
	{  KEY_B2, 1998 },
	{  KEY_B1, 3393 },
	{  KEY_NONE, 0 }
};

	
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if (hadc == AnalogKeys::instance->hadc )
	{
		AnalogKeys::instance->HandleInterrupt();
	}
}


void AnalogKeys::Start()
{
	HAL_ADC_Start_DMA(hadc, (uint32_t*)adc_buffer, countof(adc_buffer));
}

EKeyCodes AnalogKeys::ProcessKeys(uint16_t *buf, int count, SKeyMap *map)
{
	uint16_t sum = buf[0];
	for (int i = 1; i < count; i++)
		sum += buf[i];
	sum /= count;
	
	EKeyCodes key = KEY_NONE;
	while (map->keyCode != KEY_NONE)
	{
		if (sum < map->adcThreshold)
		{
			key = map->keyCode;
			break;
		}
		map++;
	}
	// TODO - debounce - interrupts approx once every 1 ms, so count 20ms for a stable signal.
	return key;
}

void AnalogKeys::HandleInterrupt()
{
	keys = 0;
	EKeyCodes code;
	code = ProcessKeys(adc_buffer + 0, 4, keys1);
	if (code != KEY_NONE)
		keys |= 1 << ((int)code - 1);
	code = ProcessKeys(adc_buffer + 4, 4, keys2);
	if (code != KEY_NONE)
		keys |= 1 << ((int)code - 1);
}
