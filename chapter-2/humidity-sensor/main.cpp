#include "DHT11.h"
#include "mbed.h"

DHT11 sensor(D4);

int main() 
{
  int error = 0;
  int h, t;

  printf("Startting reading \n\r");

  while (1) {
    ThisThread::sleep_for(2000ms);
    error = sensor.readData();
    if (error == 0) {
      t = sensor.readTemperature();
      h = sensor.readHumidity();
      printf("Temperature is : %d \n\r", t);
      printf("Humidity is : %d \n\r", h);
    } else {
      printf("Error: %d\n", error);
    }
  }
}