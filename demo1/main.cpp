// Switch the blue LED every 500ms without using the wait function.
#include "mbed.h"

using namespace std::chrono;

Ticker flipper;

DigitalOut led(LED3);

void flip()
{
	led = !led;
}


int main()
{
	led = 1;
	flipper.attach(&flip, 500ms);
	
	while(1);
}
