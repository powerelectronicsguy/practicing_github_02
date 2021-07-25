/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c123
  * @brief          : Main program body321
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.xx
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "core_mqtt.h"
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

osThreadId defaultTaskHandle;
uint32_t defaultTaskBuffer[ 2048 ];
osStaticThreadDef_t defaultTaskControlBlock;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadStaticDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 2048, defaultTaskBuffer, &defaultTaskControlBlock);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
 
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
  /**USART1 GPIO Configuration  
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_10;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USART1 interrupt Init */
  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(USART1_IRQn);

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART1, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART1);
  LL_USART_Enable(USART1);
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
  /**USART2 GPIO Configuration  
  PD5   ------> USART2_TX
  PD6   ------> USART2_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_5|LL_GPIO_PIN_6;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USART2 interrupt Init */
  NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(USART2_IRQn);

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART2, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART2);
  LL_USART_Enable(USART2);
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  LL_USART_InitTypeDef USART_InitStruct = {0};

  LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Peripheral clock enable */
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
  
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD);
  /**USART3 GPIO Configuration  
  PD8   ------> USART3_TX
  PD9   ------> USART3_RX 
  */
  GPIO_InitStruct.Pin = LL_GPIO_PIN_8|LL_GPIO_PIN_9;
  GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
  GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
  GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
  GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
  LL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USART3 interrupt Init */
  NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),5, 0));
  NVIC_EnableIRQ(USART3_IRQn);

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  USART_InitStruct.BaudRate = 115200;
  USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
  USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
  USART_InitStruct.Parity = LL_USART_PARITY_NONE;
  USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
  USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
  USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
  LL_USART_Init(USART3, &USART_InitStruct);
  LL_USART_ConfigAsyncMode(USART3);
  LL_USART_Enable(USART3);
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */
// ima ovde jos dosta posla
#define democonfigCLIENT_IDENTIFIER "miloradpetrovic20210630"
#define mqttexampleTOPIC "miloradpetrovic20210630/example/topic"
#define mqttexampleMESSAGE "Hello World!"

#define mqttexampleKEEP_ALIVE_TIMEOUT_SECONDS (60U)
#define mqttexampleCONNACK_RECV_TIMEOUT_MS    (10000U)
#define mqttexamplePROCESS_LOOP_TIMEOUT_MS    (1000U)

#define mqttexampleSHARED_BUFFER_SIZE (500U)

static uint16_t usSubscribePacketIdentifier, usUnsubscribePacketIdentifier;

static uint8_t ucSharedBuffer[mqttexampleSHARED_BUFFER_SIZE];

static MQTTFixedBuffer_t xBuffer =
{
    .pBuffer = ucSharedBuffer,
    .size    = mqttexampleSHARED_BUFFER_SIZE
};

struct NetworkContext
{
	uint32_t dummy;
};

static NetworkContext_t Milorad_NetworkContext;

#define huartWiFiModule   huart3
#define huartBLEModule    huart2
#define huartLaptop       huart1

#define U32_RECEIVE_BUFFER_FOR_WIFI_MODULE_CAPACITY ((uint32_t)2048)
#define U32_TRANSMIT_BUFFER_FOR_WIFI_MODULE_CAPACITY ((uint32_t)2048)

/* wifi module receive buffer info */
volatile uint8_t vau8ReceiveBufferForWifiModuleData[U32_RECEIVE_BUFFER_FOR_WIFI_MODULE_CAPACITY];
volatile uint32_t vu32ReceiveBufferForWifiModuleFirstFreeSlot;
uint32_t u32ReceiveBufferForWifiModuleFirstFilledSlot;

int32_t i32InterruptHandlerImplementationForUSART3(void)
{
	/* Is a RXNE interrupt pending? */
	if (LL_USART_IsEnabledIT_RXNE(USART3) && LL_USART_IsActiveFlag_RXNE(USART3)) /* yes */
	{
		/* read the received byte */
		uint8_t u8ReceivedByteViaUART = LL_USART_ReceiveData8(USART3);

		/* insert recevied byte into receive buffer */
		vau8ReceiveBufferForWifiModuleData[vu32ReceiveBufferForWifiModuleFirstFreeSlot] = u8ReceivedByteViaUART;
		vu32ReceiveBufferForWifiModuleFirstFreeSlot++;
		if (vu32ReceiveBufferForWifiModuleFirstFreeSlot == U32_RECEIVE_BUFFER_FOR_WIFI_MODULE_CAPACITY)
		{
			vu32ReceiveBufferForWifiModuleFirstFreeSlot = (uint32_t)0;
		}
	}

	return (int32_t)0;
}

int32_t i32GetByteFromReceiveBufferForWifiModule(uint8_t* const cpu8ReceivedByte)
{
	NVIC_DisableIRQ(USART3_IRQn);
	uint32_t u32ReceiveBufferForWifiModuleFirstFreeSlotCurrent = vu32ReceiveBufferForWifiModuleFirstFreeSlot;
	NVIC_EnableIRQ(USART3_IRQn);

	if (u32ReceiveBufferForWifiModuleFirstFilledSlot == u32ReceiveBufferForWifiModuleFirstFreeSlotCurrent)
	{
		return (int32_t)0;
	}
	else
	{
		*cpu8ReceivedByte = vau8ReceiveBufferForWifiModuleData[u32ReceiveBufferForWifiModuleFirstFilledSlot];
		u32ReceiveBufferForWifiModuleFirstFilledSlot++;
		if (u32ReceiveBufferForWifiModuleFirstFilledSlot == U32_RECEIVE_BUFFER_FOR_WIFI_MODULE_CAPACITY)
		{
			u32ReceiveBufferForWifiModuleFirstFilledSlot = (uint32_t)0;
		}

		return (int32_t)1;
	}
}

int32_t i32TransmitByteArrayToWifiModule(const uint8_t* const cpcu8ByteArray, const uint32_t cu32Length)
{
	for (uint32_t u32Index = (uint32_t)0; u32Index < cu32Length; u32Index++)
	{
		LL_USART_TransmitData8(USART3, cpcu8ByteArray[u32Index]);
		while(!LL_USART_IsActiveFlag_TXE(USART3));
	}
	while(!LL_USART_IsActiveFlag_TC(USART3));

	return (int32_t)1;
}


int32_t i32TransmitByteArrayToLaptop(const uint8_t* const cpcu8ByteArray, const uint32_t cu32Length)
{
	for (uint32_t u32Index = (uint32_t)0; u32Index < cu32Length; u32Index++)
	{
		LL_USART_TransmitData8(USART1, cpcu8ByteArray[u32Index]);
		while(!LL_USART_IsActiveFlag_TXE(USART1));
	}
	while(!LL_USART_IsActiveFlag_TC(USART1));

	return (int32_t)1;
}

void vFlushWiFiModuleReceiveBufferToLaptop(void)
{
	uint8_t some_byte;
	while (i32GetByteFromReceiveBufferForWifiModule(&some_byte))
	{
		i32TransmitByteArrayToLaptop(&some_byte, 1);
	}
}

// Network send.
int32_t Milorad_Plaintext_send(NetworkContext_t* pContext, const void* pBuffer, size_t bytes )
{
	const uint8_t* pcu8DataToSend = (const uint8_t*)pBuffer;
	i32TransmitByteArrayToWifiModule(pcu8DataToSend, bytes);

	return bytes;
}



// Network receive.
int32_t Milorad_Plaintext_recv(NetworkContext_t* pContext, void* pBuffer, size_t bytes )
{

	uint32_t bytes_received = 0;
	uint8_t* pu8ReceivedData = (uint8_t*)pBuffer;

	uint8_t some_byte;
	uint32_t u32StartTime = xTaskGetTickCount();
	uint32_t u32CurrentTime = xTaskGetTickCount();
	while (u32CurrentTime - u32StartTime <= (uint32_t)100)
	{
		if (i32GetByteFromReceiveBufferForWifiModule(&some_byte))
		{
			pu8ReceivedData[bytes_received] = some_byte;
			bytes_received++;

			if (bytes_received == bytes)
			{
				break;
			}
		}
		u32CurrentTime = xTaskGetTickCount();
	}

	return bytes_received;
}

static void prvEventCallback( MQTTContext_t * pxMQTTContext,
                              MQTTPacketInfo_t * pxPacketInfo,
                              MQTTDeserializedInfo_t * pxDeserializedInfo )
{
    if( ( pxPacketInfo->type & 0xF0U ) == MQTT_PACKET_TYPE_PUBLISH )
    {
    	i32TransmitByteArrayToLaptop("Publish event happend!\r\n", sizeof("Publish event happend!\r\n"));
    	i32TransmitByteArrayToLaptop(pxDeserializedInfo->pPublishInfo->pPayload, pxDeserializedInfo->pPublishInfo->payloadLength);
    	i32TransmitByteArrayToLaptop("\r\n\r\n\r\n", sizeof("\r\n\r\n\r\n"));
    }
    else
    {
    	i32TransmitByteArrayToLaptop("'Else' event happend!\r\n", sizeof("'Else' event happend!\r\n"));
    }
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN 5 */
	/* enable Rx for WiFi module */
	LL_USART_EnableIT_RXNE(USART3);

	i32TransmitByteArrayToLaptop("Program started\r\n", sizeof("Program started\r\n"));
	osDelay(10000);
	i32TransmitByteArrayToLaptop("Go!\r\n", sizeof("Go!\r\n"));
	osDelay(1000);
	/* Infinite loop */
  for(;;)
  {
	  i32TransmitByteArrayToWifiModule("AT\r\n", sizeof("AT\r\n"));
	  osDelay(1000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+UART_CUR=115200,8,1,0,0\r\n", sizeof("AT+UART_CUR=115200,8,1,0,0\r\n"));
	  osDelay(1000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+UART_CUR?\r\n", sizeof("AT+UART_CUR?\r\n"));
	  osDelay(1000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CWMODE=3\r\n", sizeof("AT+CWMODE=3\r\n"));
	  osDelay(1000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CWJAP=\"51cf7b\",\"272089548\"\r\n", sizeof("AT+CWJAP=\"51cf7b\",\"272089548\"\r\n"));
	  osDelay(10000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CIFSR\r\n", sizeof("AT+CIFSR\r\n"));
	  osDelay(5000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CIPSTART=\"TCP\",\"broker.hivemq.com\",1883\r\n", sizeof("AT+CIPSTART=\"TCP\",\"broker.hivemq.com\",1883\r\n"));
	  osDelay(2000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CIPMODE=1\r\n", sizeof("AT+CIPMODE=1\r\n"));
	  osDelay(2000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

	  i32TransmitByteArrayToWifiModule("AT+CIPSEND\r\n", sizeof("AT+CIPSEND\r\n"));
	  osDelay(2000);
	  vFlushWiFiModuleReceiveBufferToLaptop();

		/* now comes the MQTT part */
		MQTTStatus_t xResult;
		MQTTContext_t xMQTTContext;
		MQTTConnectInfo_t xConnectInfo;
		TransportInterface_t xTransport;
		bool xSessionPresent;
		MQTTSubscribeInfo_t xMQTTSubscription;
		MQTTPublishInfo_t xMQTTPublishInfo;


	    xTransport.pNetworkContext = &Milorad_NetworkContext; /* #TBD */
	    xTransport.send = Milorad_Plaintext_send;
	    xTransport.recv = Milorad_Plaintext_recv;

	    xResult = MQTT_Init(&xMQTTContext, &xTransport, xTaskGetTickCount /*prvGetTimeMs*/, prvEventCallback, &xBuffer );
	    if (xResult != MQTTSuccess)
	    {
	    	while (1);
	    }

	    (void)memset((void*)&xConnectInfo, 0x00, sizeof(xConnectInfo));
	    xConnectInfo.cleanSession = true;
	    xConnectInfo.pClientIdentifier = democonfigCLIENT_IDENTIFIER;
	    xConnectInfo.clientIdentifierLength = (uint16_t)strlen(democonfigCLIENT_IDENTIFIER);
	    xConnectInfo.keepAliveSeconds = mqttexampleKEEP_ALIVE_TIMEOUT_SECONDS;

	    osDelay(3000);
	    xResult = MQTT_Connect( &xMQTTContext,
	                            &xConnectInfo,
	                            NULL,
	                            mqttexampleCONNACK_RECV_TIMEOUT_MS,
	                            &xSessionPresent);

	    osDelay(1000);
	    uint8_t bla[100];
	    Milorad_Plaintext_recv(NULL, bla, 1);

	    if (xResult != MQTTSuccess)
	    {
	    	osDelay(1000);
	    	while (1);
	    }

	    osDelay(1000);

	    (void)memset((void*)&xMQTTSubscription, 0x00, sizeof(xMQTTSubscription));
	    usSubscribePacketIdentifier = MQTT_GetPacketId(&xMQTTContext);
	    xMQTTSubscription.qos = MQTTQoS0;
	    xMQTTSubscription.pTopicFilter = mqttexampleTOPIC;
	    xMQTTSubscription.topicFilterLength = (uint16_t)strlen(mqttexampleTOPIC);

	    /* subscribe to given topic */
      xResult = MQTT_Subscribe( &xMQTTContext,
                                &xMQTTSubscription,
                                (uint32_t)1,
                                usSubscribePacketIdentifier);

	    if (xResult != MQTTSuccess)
	    {
	    	while (1);
	    }

      xResult = MQTT_ProcessLoop(&xMQTTContext, mqttexamplePROCESS_LOOP_TIMEOUT_MS);

      if (xResult != MQTTSuccess)
	    {
	    	while (1);
	    }

      /* publish given message to given topic */
      (void)memset((void*)&xMQTTPublishInfo, 0x00, sizeof(xMQTTPublishInfo));
      xMQTTPublishInfo.qos = MQTTQoS0;
      xMQTTPublishInfo.retain = false;
      xMQTTPublishInfo.pTopicName = mqttexampleTOPIC;
      xMQTTPublishInfo.topicNameLength = (uint16_t)strlen(mqttexampleTOPIC);
      xMQTTPublishInfo.pPayload = mqttexampleMESSAGE;
      xMQTTPublishInfo.payloadLength = strlen(mqttexampleMESSAGE);

      while(1)
      {
		  for (int i = 0; i < 100; i++)
		  {
			  uint8_t mqtt_message_to_publish[10];
			  mqtt_message_to_publish[0] = 'p';
			  mqtt_message_to_publish[1] = 'o';
			  mqtt_message_to_publish[2] = 'r';
			  mqtt_message_to_publish[3] = 'u';
			  mqtt_message_to_publish[4] = 'k';
			  mqtt_message_to_publish[5] = 'a';
			  mqtt_message_to_publish[6] = ':';
			  mqtt_message_to_publish[7] = '0' + (i / 10);
			  mqtt_message_to_publish[8] = '0' + (i % 10);
			  mqtt_message_to_publish[9] = 0;

			  xMQTTPublishInfo.pPayload = mqtt_message_to_publish;
			  xMQTTPublishInfo.payloadLength = (uint32_t)10;

			  xResult = MQTT_Publish(&xMQTTContext, &xMQTTPublishInfo, 0U);

			  if (xResult != MQTTSuccess)
				{
					while (1);
				}

			  xResult = MQTT_ProcessLoop(&xMQTTContext, mqttexamplePROCESS_LOOP_TIMEOUT_MS);

			  if (xResult != MQTTSuccess)
				{
					while (1);
				}

			  /* Leave the connection idle for some time. */
			  osDelay(1000);
		  }
      }

      /******************** Unsubscribe from the topic. *********************/
      (void)memset((void*)&xMQTTSubscription, 0x00, sizeof(xMQTTSubscription));
      usSubscribePacketIdentifier = MQTT_GetPacketId(&xMQTTContext);
      xMQTTSubscription.qos = MQTTQoS0;
      xMQTTSubscription.pTopicFilter = mqttexampleTOPIC;
      xMQTTSubscription.topicFilterLength = (uint16_t)strlen(mqttexampleTOPIC);
      usUnsubscribePacketIdentifier = MQTT_GetPacketId(&xMQTTContext);

      xResult = MQTT_Unsubscribe( &xMQTTContext,
                                  &xMQTTSubscription,
                                  1,
                                  usUnsubscribePacketIdentifier);

      if (xResult != MQTTSuccess)
	    {
	    	while (1);
	    }

      xResult = MQTT_ProcessLoop(&xMQTTContext, mqttexamplePROCESS_LOOP_TIMEOUT_MS);

      if (xResult != MQTTSuccess)
	    {
	    	while (1);
	    }


	  for(;;)
	  {
		  osDelay(1000);
		  i32TransmitByteArrayToLaptop(".", 1);
		  vFlushWiFiModuleReceiveBufferToLaptop();
	  }
  }
  /* USER CODE END 5 */ 
}

 /**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM3 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM3) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
