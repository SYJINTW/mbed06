#include "mbed.h"
class Counter
{
    public:
    Counter(PinName pin): _interrupt(pin)
    {
        _interrupt.rise(callback(this, &Counter::increment));
    }

    void increment()
    {
        _count++;
    }

    int read()
    {
        return _count;
    }

    private:
    InterruptIn _interrupt;
    volatile int _count;
};

Counter counter(USER_BUTTON);

int main()
{
    while(1)
    {
        printf("Count so far: %d\n", counter.read());
        ThisThread::sleep_for(2s);
    }
}
