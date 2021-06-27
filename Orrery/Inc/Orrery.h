#ifndef __ORRERY_H
#define __ORRERY_H

#define T2_FREQ						(16000)		// 4000 ticks per sec (Hz)
#define STEPPER_UPDATES_PER_SECOND	(10)
#define SECONDS_PER_DAY				3

class Orrery
{
public:
	Orrery() {}
	void main();
};

#endif