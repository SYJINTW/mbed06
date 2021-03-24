#include "mbed.h"
#include "mbed_events.h"
using namespace std::chrono;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn btn(USER_BUTTON);

EventQueue printfQueue;
EventQueue eventQueue;

void blink_led2() {
// this runs in the normal priority thread
led2 = !led2;
}

void print_toggle_led() {
// this runs in the lower priority thread
printf("Toggle LED!\r\n");
}

void btn_fall_irq() {
led1 = !led1;
// defer the printf call to the low priority thread
printfQueue.call(&print_toggle_led);
}

int main() {

// low priority thread for calling printf()
Thread printfThread(osPriorityLow);
printfThread.start(callback(&printfQueue, &EventQueue::dispatch_forever));

// normal priority thread for other events
Thread eventThread(osPriorityNormal);
eventThread.start(callback(&eventQueue, &EventQueue::dispatch_forever));

// call blink_led2 every second, automatically defering to the eventThread
Ticker ledTicker;
ledTicker.attach(eventQueue.event(&blink_led2), 1s);

// button fall still runs in the ISR
btn.fall(&btn_fall_irq);

while (1) {ThisThread::sleep_for(1s);}
}


/*#include "mbed.h"
#include "mbed_events.h"
using namespace std::chrono;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
InterruptIn btn(USER_BUTTON);

EventQueue LowQueue;
EventQueue NormalQueue;

void print_toggle_low() {
    printf("Low!\r\n");
}

void print_toggle_normal()
{
    printf("Normal!\r\n");
}

void btn_fall() {
    led1 = !led1;
    LowQueue.call(&print_toggle_low);
}

void btn_rise(){
    led2 = !led2;
    NormalQueue.call(&print_toggle_normal);
}

int main() {

    Thread LowThread(osPriorityLow);
    LowThread.start(callback(&LowQueue, &EventQueue::dispatch_forever));

    Thread NormalThread(osPriorityNormal);
    NormalThread.start(callback(&NormalQueue, &EventQueue::dispatch_forever));

    btn.rise(&btn_rise);
    btn.fall(&btn_fall);


    while (1) {ThisThread::sleep_for(1s);}

}
*/