#include "mbed.h"

int main() {
    // Initialise the digital pins LED1, LED2 and LED3 as outputs
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);
    DigitalOut led3(LED3);

    led1 = 0;
    led2 = 1;
    led3 = 0;

    printf("starting blinking \n\r");

    while (true) {
    led1 = !led1;
    led2 = !led2;
    led3 = !led3;
    ThisThread::sleep_for(500ms);
    }
}
