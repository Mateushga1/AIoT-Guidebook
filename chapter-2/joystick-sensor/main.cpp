#include "mbed.h"

AnalogIn analog_value0(A0);
AnalogIn analog_value1(A1);

DigitalIn pb(D8);
DigitalOut led(LED1);

int main()
{
    float meas_r0, meas_r1;
    float meas_v0, meas_v1;
    int but;

    printf("\nJoystick example\n\r");

    while(1) {
        meas_r0 = analog_value0.read();
        // Read the analog input value (value from 0.0 to 1.0 = full ADC conversion range)
        meas_v0 = meas_r0 * 3300;
        // Converts value in the 0V-3.3V range
        meas_r1 = analog_value1.read();
        // Read the analog input value (value from 0.0 to 1.0 = full ADC conversion range)
        meas_v1 = meas_r1 * 3300;
        // Converts value in the 0V-3.3V range
        but = pb;

        // Display values
        printf("measure x= %f = %.0f mV y= %f = %.0f mV %d \n\r", meas_r0, meas_v0, meas_r1, meas_v1, but);

        // LED is ON when the button is pushed
        led = pb;

        ThisThread::sleep_for(1000ms); // 1 second
    }
}