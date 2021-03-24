#include "mbed.h"

InterruptIn button(USER_BUTTON);
DigitalOut led(LED1);
DigitalOut flash(LED3);

void flip()
{
    led = !led;
}

int main()
{
    button.fall(&flip);
    while(1)
    {
        flash = !flash;
        ThisThread::sleep_for(250ms);
    }
}