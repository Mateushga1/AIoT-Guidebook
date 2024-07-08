#include "mbed.h"

DigitalOut R(D9);
DigitalOut G(D10);
DigitalOut B(D11);

int main()
{
    printf("\n\r LED example ON/OFF\n\r");

    while(1) {
        R = 0; G = 0; B = 0;
        ThisThread::sleep_for(1000ms); // wait 1 second
        R = 1; G = 0; B = 0;
        ThisThread::sleep_for(1000ms); // wait 1 second
        R = 0; G = 1; B = 0;
        ThisThread::sleep_for(1000ms); // wait 1 second
        R = 0; G = 0; B = 1;
        ThisThread::sleep_for(1000ms); // wait 1 second
        R = 1; G = 1; B = 1;
        ThisThread::sleep_for(1000ms); // wait 1 second
    }
}