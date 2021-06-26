#include "RTC_time_t.h"

volatile bool RTC_time_t::TimeUpdate;
  
extern "C" void RTC_time_t_RTC_IRQHandler()
{
	RTC->CRL = ~RTC_FLAG_OW;
	RTC->CRL = ~RTC_FLAG_SEC;
	
	RTC_time_t::TimeUpdate = true;
}
