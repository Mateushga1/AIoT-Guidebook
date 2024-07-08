#include "mbed.h"

AnalogIn analog_value0(A0);
AnalogIn analog_value1(A1);

DigitalIn pb(D8);

PwmOut R(D9);
PwmOut G(D10);
PwmOut B(D11);

int val;

int main() {
  float meas_r0, meas_r1;
  float red, green, blue;
  int but;

  printf("\nJoystick example\n\r");

  while (1) {
    meas_r0 = analog_value0.read();
    // Read the analog input value (value from 0.0 to 1.0 = full ADC conversion range)

    meas_r1 = analog_value1.read();
    // Read the analog input value (value from 0.0 to 1.0 = full ADC conversion range)

    but = pb;

    // Display values
    printf("measure x = %f, y = %f, sw = %d \n\r", meas_r0, meas_r1, but);

    // Set the RGB LED color
    red = meas_r0; 
    green = meas_r1;
    blue = 1.0 - meas_r0; 

    R.write(red);
    G.write(green);
    B.write(blue);

    ThisThread::sleep_for(100ms); // 1 second
  }
}
