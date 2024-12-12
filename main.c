#ifndef F_CPU
#define F_CPU 16000000ul
#endif
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#include "include/h_bridge.h"
#include "include/math.h"
#include "include/control.h"

#include "h_bridge.c"
#include "math.c"
#include "control.c"



int main(void)
{	
	init_h_bridge();
 	while (1)
	{
		
		for (int i = 0; i < 100; i++)
		{
			h_bridge_set_percentage(i);
			_delay_ms(100);
		}
		for (int i = 100; i > 0; i--)
		{
			h_bridge_set_percentage(i);
			_delay_ms(100);
		}
		_delay_ms(1000);
		for (int i = 0; i > -100; i--)
		{
			h_bridge_set_percentage(i);
			_delay_ms(100);
		}
		for (int i = -100; i < 0; i++)
		{
			h_bridge_set_percentage(i);
			_delay_ms(100);
		}
		_delay_ms(1000);
	}

	return 0;
}
