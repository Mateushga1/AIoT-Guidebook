#include "mbed.h"

AnalogIn analogPin(A0);

DigitalIn digitalPin(D2);

DigitalOut led(LED1);

int digitalVal; // digital readings
float analogVal; //analog readings

int main()
{   
    while(1){
        // Read the digital interface
        digitalVal = digitalPin.read(); 
        if(digitalVal == 1) // if temperature threshold reached
        {
            led = 1; // turn ON LED
            printf("\nThreshold reached");
        }
        else
        {
            led = 0; // turn OFF LED
        }

        // Read the analog interface
        analogVal = analogPin.read(); 
        printf("\nAnalog mesure: %.2f", analogVal); // print analog value to serial

        // Print raw ADC value
        uint16_t rawADCValue = analogPin.read_u16();
        printf("\nRaw ADC value: %u\n", rawADCValue);

        ThisThread::sleep_for(100ms);
    }
}