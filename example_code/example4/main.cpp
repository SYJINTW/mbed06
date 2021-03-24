#include "mbed.h"

using namespace std::chrono;

//Timeout flipper;
Ticker flipper;

DigitalOut led1(LED1);
DigitalOut led2(LED3);

void flip()
{
    led2 = !led2;
}

int main()
{
    led2 = 1;
    flipper.attach(&flip, 2s);
    
    while(1)
    {
        led1 = !led1;
        ThisThread::sleep_for(200ms);
    }
}
