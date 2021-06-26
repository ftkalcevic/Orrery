#pragma  once

#include "main.h"
#include <time.h>
#include "stm32f1xx_ll_rtc.h"

#define BASE_TIME 1577797200	// 1/1/2020 0:0:0

class RTC_time_t
{
public:
	static volatile bool TimeUpdate;
	
	static void Init()
	{
		TimeUpdate = false;
		
//		LL_PWR_EnableBkUpAccess();
//		/* Enable BKP CLK enable for backup registers */
//		LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_BKP);
//		/* Peripheral clock enable */
//		LL_RCC_EnableRTC();


//		/** Initialize RTC */
//		LL_RTC_InitTypeDef RTC_InitStruct = {0};
//		RTC_InitStruct.AsynchPrescaler = 0xFFFFFFFFU;
//		LL_RTC_Init(RTC, &RTC_InitStruct);
//		LL_RTC_SetAsynchPrescaler(RTC, 0xFFFFFFFFU);
		
		////__HAL_RTC_WRITEPROTECTION_DISABLE(RTC);
		//SET_BIT(RTC->CRL, RTC_CRL_CNF);
		//
		//// set prescaler for 1 sec
		//uint32_t prescaler = HAL_RCCEx_GetPeriphCLKFreq(RCC_PERIPHCLK_RTC) - 1U;
		//MODIFY_REG(RTC->PRLH, RTC_PRLH_PRL, (prescaler >> 16U));
		//MODIFY_REG(RTC->PRLL, RTC_PRLL_PRL, (prescaler & RTC_PRLL_PRL));
		//
		////__HAL_RTC_WRITEPROTECTION_ENABLE(RTC);
		//CLEAR_BIT(RTC->CRL, RTC_CRL_CNF);
		//
		///* RTC interrupt Init */
		//NVIC_SetPriority(RTC_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
		//NVIC_EnableIRQ(RTC_IRQn);
		//
		//// 1 sec interrupt
		//SET_BIT(RTC->CRH, RTC_IT_SEC);
	}

	static void SetTime(time_t t)
	{
		// We use time from 1/1/2000 0:0:0 onwards otherwise we'd stop at 2031.
		t -= BASE_TIME;
		
		uint32_t tickstart = HAL_GetTick();
		while ( (RTC->CRL & RTC_CRL_RTOFF) == (uint32_t)RESET )
		{
			if ((HAL_GetTick() - tickstart) >  RTC_TIMEOUT_VALUE)
				return ;//HAL_TIMEOUT;
		}

		//__HAL_RTC_WRITEPROTECTION_DISABLE(RTC);
		SET_BIT(RTC->CRL, RTC_CRL_CNF);

		WRITE_REG(RTC->CNTH, (t >> 16U));
		WRITE_REG(RTC->CNTL, (t & RTC_CNTL_RTC_CNT));

		//__HAL_RTC_WRITEPROTECTION_ENABLE(RTC);
		CLEAR_BIT(RTC->CRL, RTC_CRL_CNF);
	}
	
	static time_t GetTime()
	{
		uint16_t high1, high2, low;
		time_t t = 0U;

		high1 = READ_REG(RTC->CNTH & RTC_CNTH_RTC_CNT);
		low   = READ_REG(RTC->CNTL & RTC_CNTL_RTC_CNT);
		high2 = READ_REG(RTC->CNTH & RTC_CNTH_RTC_CNT);

		if (high1 != high2)
		{
			/* In this case the counter roll over during reading of CNTL and CNTH registers, read again CNTL register then return the counter value */
			low = READ_REG(RTC->CNTL & RTC_CNTL_RTC_CNT);
			t = (((uint32_t) high2 << 16U) | low);
		}
		else
		{
			t = (((uint32_t) high1 << 16U) | low);
		}

		return t + BASE_TIME;
	}		

};