#include "mbed.h"

// Sensors drivers present in the BSP library
#include "stm32l475e_iot01_accelero.h"
#include "stm32l475e_iot01_gyro.h"
#include "stm32l475e_iot01_hsensor.h"
#include "stm32l475e_iot01_magneto.h"
#include "stm32l475e_iot01_psensor.h"
#include "stm32l475e_iot01_tsensor.h"

DigitalOut led(LED1);

int main() {
  float sensor_value = 0;
  int16_t pDataXYZ[3] = {0};
  float pGyroDataXYZ[3] = {0};

  printf("Start sensor init\n");

  BSP_TSENSOR_Init();
  BSP_HSENSOR_Init();
  BSP_PSENSOR_Init();
  BSP_MAGNETO_Init();
  BSP_GYRO_Init();
  BSP_ACCELERO_Init();

  printf("\n\nLED1 should blink during sensor read\n");

  while (1) {
    led = 1;

    sensor_value = BSP_TSENSOR_ReadTemp();
    printf("\nTEMPERATURE = %.2f degC ", sensor_value);

    sensor_value = BSP_HSENSOR_ReadHumidity();
    printf("HUMIDITY = %.2f %% ", sensor_value);

    sensor_value = BSP_PSENSOR_ReadPressure();
    printf("PRESSURE is = %.2f mBar\n", sensor_value);

    led = 0;

    ThisThread::sleep_for(1000ms);

    led = 1;

    BSP_MAGNETO_GetXYZ(pDataXYZ);
    printf("MAGNETO_X,Y,Z = %d \t%d \t%d \n", pDataXYZ[0], pDataXYZ[1], pDataXYZ[2]);

    BSP_GYRO_GetXYZ(pGyroDataXYZ);
    printf("GYRO_X,Y,Z = %.2f \t%.2f \t%.2f \n", pGyroDataXYZ[0], pGyroDataXYZ[1], pGyroDataXYZ[2]);

    BSP_ACCELERO_AccGetXYZ(pDataXYZ);
    printf("ACCELERO_X,Y,Z = %d \t%d \t%d \n", pDataXYZ[0], pDataXYZ[1], pDataXYZ[2]);

    led = 0;

    ThisThread::sleep_for(1000ms);
  }
}