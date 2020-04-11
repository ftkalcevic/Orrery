#include "Orrery.h"
#include "SH1106.h"

SH1106 display;

void Orrery::main()
{
	#ifdef DEBUG
		printf("Starting orrery\n");
	#endif
	
	display.init();
	for (;;)
	{
	}
}