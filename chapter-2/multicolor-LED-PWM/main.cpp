#include "mbed.h"

PwmOut R(D9);
PwmOut G(D10);
PwmOut B(D11);

int val;

int main()
{
    printf("\n\r LED example with PWM\n\r");

    while(1) {
        R.write(0); G.write(0); B.write(0);
        ThisThread::sleep_for(1000ms); // wait 1 second

        for (val = 0; val <= 1000; val++) {
            R.write((double)val / 1000.0);
            ThisThread::sleep_for(10ms); // wait 0.01 second
        }

        for (val = 0; val <= 1000; val++) {
            G.write((double)val / 1000.0);
            ThisThread::sleep_for(10ms); // wait 0.01 second
        }

        for (val = 0; val <= 1000; val++) {
            B.write((double)val / 1000.0);
            ThisThread::sleep_for(10ms); // wait 0.01 second
        }

        ThisThread::sleep_for(1000ms); // wait 1 second
    }
}