/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.h
  * @author  MCD Application Team
  * @brief   NetXDuo applicative header file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_NETXDUO_H__
#define __APP_NETXDUO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "nx_api.h"

/* Private includes ----------------------------------------------------------*/

/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "main.h"
#include "nxd_dhcp_client.h"
#include "nx_driver_emw3080.h" 
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define PRINT_IP_ADDRESS(addr)             do { \
                                                printf("STM32 %s: %lu.%lu.%lu.%lu \n", #addr, \
                                                (addr >> 24) & 0xff, \
                                                (addr >> 16) & 0xff, \
                                                (addr >> 8) & 0xff, \
                                                addr& 0xff);\
                                           }while(0)

#define PRINT_DATA(addr, port, data)       do { \
                                                printf("[%lu.%lu.%lu.%lu:%u] -> '%s' \n", \
                                                (addr >> 24) & 0xff, \
                                                (addr >> 16) & 0xff, \
                                                (addr >> 8) & 0xff,  \
                                                (addr & 0xff), port, data); \
                                           } while(0)
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
UINT MX_NetXDuo_Init(VOID *memory_ptr);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PAYLOAD_SIZE             1544
#define NX_PACKET_POOL_SIZE      (( PAYLOAD_SIZE + sizeof(NX_PACKET)) * 10)
#define WINDOW_SIZE              512

#define DEFAULT_MEMORY_SIZE      1024
#define DEFAULT_PRIORITY         10

#define NULL_ADDRESS             0

#define DEFAULT_PORT             6000
#define TCP_SERVER_PORT          80  // Port 80 for HTTP
#define TCP_SERVER_ADDRESS       IP_ADDRESS(184, 106, 153, 149) // ThingSpeak server IP

#define DEFAULT_TIMEOUT          10 * NX_IP_PERIODIC_RATE
#define THINGSPEAK_API_KEY       "Q7G63OMFJK1H2T5W" // Write key
#define THINGSPEAK_FIELD_VALUE   100  // Value we want to send
/* USER CODE END PD */

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

#ifdef __cplusplus
}
#endif
#endif /* __APP_NETXDUO_H__ */
