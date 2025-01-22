/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

// The libraries for sensors: DS1307, LCD, SHT21
#include "sht2x_for_stm32_hal.h"
#include "i2c-lcd.h"
#include "I2C_DS3231.h"
#include "print_cli.h"
#include <stdbool.h>

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
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;
I2C_HandleTypeDef hi2c3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* Definitions for MeasureTemp */
osThreadId_t MeasureTempHandle;
const osThreadAttr_t MeasureTemp_attributes = {
  .name = "MeasureTemp",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for Realtime */
osThreadId_t RealtimeHandle;
const osThreadAttr_t Realtime_attributes = {
  .name = "Realtime",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal5,
};
/* Definitions for DisplayTemp */
osThreadId_t DisplayTempHandle;
const osThreadAttr_t DisplayTemp_attributes = {
  .name = "DisplayTemp",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for DisplayTime */
osThreadId_t DisplayTimeHandle;
const osThreadAttr_t DisplayTime_attributes = {
  .name = "DisplayTime",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal4,
};
/* Definitions for myTask05 */
osThreadId_t myTask05Handle;
const osThreadAttr_t myTask05_attributes = {
  .name = "myTask05",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal3,
};
/* Definitions for myTask06 */
osThreadId_t myTask06Handle;
const osThreadAttr_t myTask06_attributes = {
  .name = "myTask06",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myTask07 */
osThreadId_t myTask07Handle;
const osThreadAttr_t myTask07_attributes = {
  .name = "myTask07",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for myQueue01 */
osMessageQueueId_t myQueue01Handle;
const osMessageQueueAttr_t myQueue01_attributes = {
  .name = "myQueue01"
};
/* Definitions for myQueue02 */
osMessageQueueId_t myQueue02Handle;
const osMessageQueueAttr_t myQueue02_attributes = {
  .name = "myQueue02"
};
/* Definitions for myQueue03 */
osMessageQueueId_t myQueue03Handle;
const osMessageQueueAttr_t myQueue03_attributes = {
  .name = "myQueue03"
};
/* Definitions for myQueue04 */
osMessageQueueId_t myQueue04Handle;
const osMessageQueueAttr_t myQueue04_attributes = {
  .name = "myQueue04"
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};
/* Definitions for myBinarySem02 */
osSemaphoreId_t myBinarySem02Handle;
const osSemaphoreAttr_t myBinarySem02_attributes = {
  .name = "myBinarySem02"
};
/* USER CODE BEGIN PV */
// DS1307, Step 1:
DateTime date_time;
// Task deadlines
TickType_t taskReadTempDeadline;
TickType_t taskReadTimeDeadline;
TickType_t taskDisplayTempDeadline;
TickType_t taskDisplayTimeDeadline;
TickType_t taskReadRhDeadline;
TickType_t taskDisplayRhDeadline;
typedef struct{
	int id;
	int period;
	int execTime;
	int deadline;
	int priotity;
	int allPeriod;
	float wcet;
	bool changed;
} Task;
Task tasks[6] = {
        {0, 2250, 50, 100, 5, 10, 0, false},  // Task 1
        {1, 900, 4, 200, 11, 10, 0, false}, // Task 2
        {2, 3000, 4, 300, 17, 10, 0, false}, // Task 3
        {3, 1000, 4, 400, 23, 10, 0, false}, // Task 4
        {4, 2000, 50, 500, 29, 10, 0, false}, // Task 5
        {5, 4500, 4, 600, 35, 10, 0, false}  // Task 6
    };
Task prev_tasks[6] = {
        {0, 2250, 50, 100, 5, 10, 0, false},  // Task 1
        {1, 900, 4, 200, 11, 10, 0, false}, // Task 2
        {2, 3000, 4, 300, 17, 10, 0, false}, // Task 3
        {3, 1000, 4, 400, 23, 10, 0, false}, // Task 4
        {4, 2000, 50, 500, 29, 10, 0, false}, // Task 5
        {5, 4500, 4, 600, 35, 10, 0, false}  // Task 6
    };
#define MAX_STRING_SIZE 20

#define RX_BUFFER_SIZE 30
uint8_t rx_buffer[RX_BUFFER_SIZE];
char rx_byte;
uint16_t rx_index = 0;
typedef struct {
    char task[MAX_STRING_SIZE];  // Trường chứa chuỗi "task1"
    int values[5];               // Mảng chứa 5 số nguyên
} TaskData;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_I2C3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);
void StartTask06(void *argument);
void StartTask07(void *argument);

/* USER CODE BEGIN PFP */
// Hàm phát hiện thay đổi
bool detectChange(Task *current, Task *previous);
void updatePrevious(Task *previous, Task *current);
// Hàm sắp xếp các task theo chu kỳ (tăng dần)
void sort_tasks_by_period(Task *tasks, int num_tasks);

// Hàm cập nhật chu kỳ và mức độ ưu tiên (sử dụng con trỏ)
void update_single_task_period(Task *tasks, int num_tasks, int task_id, int new_period);
void display_tasks(Task *tasks, int num_tasks);
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
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  //Init SHT21, set resolution
  SHT2x_Init(&hi2c1);
  SHT2x_SetResolution(RES_14_12);
  print_cli("Inited SHT21 successfully\n");

  //Init LCD, set start time
  rtc_init(&hi2c3);
  date_time.date = 20;
  date_time.day = 20;
  date_time.hour = 10;
  date_time.i2c = 02;
  date_time.min = 41;
  date_time.mon = 1;
  date_time.sec = 12;
  date_time.year = 25;
  rtc_write_time(&date_time);

  //Init lcd
  lcd_init();

  HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* creation of myBinarySem02 */
  myBinarySem02Handle = osSemaphoreNew(1, 1, &myBinarySem02_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of myQueue01 */
  myQueue01Handle = osMessageQueueNew (5, sizeof(float), &myQueue01_attributes);

  /* creation of myQueue02 */
  myQueue02Handle = osMessageQueueNew (5, sizeof(DateTime), &myQueue02_attributes);

  /* creation of myQueue03 */
  myQueue03Handle = osMessageQueueNew (16, sizeof(float), &myQueue03_attributes);

  /* creation of myQueue04 */
  myQueue04Handle = osMessageQueueNew (16, sizeof(uint8_t) * 15, &myQueue04_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of MeasureTemp */
  MeasureTempHandle = osThreadNew(StartDefaultTask, NULL, &MeasureTemp_attributes);

  /* creation of Realtime */
  RealtimeHandle = osThreadNew(StartTask02, NULL, &Realtime_attributes);

  /* creation of DisplayTemp */
  DisplayTempHandle = osThreadNew(StartTask03, NULL, &DisplayTemp_attributes);

  /* creation of DisplayTime */
  DisplayTimeHandle = osThreadNew(StartTask04, NULL, &DisplayTime_attributes);

  /* creation of myTask05 */
  myTask05Handle = osThreadNew(StartTask05, NULL, &myTask05_attributes);

  /* creation of myTask06 */
  myTask06Handle = osThreadNew(StartTask06, NULL, &myTask06_attributes);

  /* creation of myTask07 */
  myTask07Handle = osThreadNew(StartTask07, NULL, &myTask07_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief I2C3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C3_Init(void)
{

  /* USER CODE BEGIN I2C3_Init 0 */

  /* USER CODE END I2C3_Init 0 */

  /* USER CODE BEGIN I2C3_Init 1 */

  /* USER CODE END I2C3_Init 1 */
  hi2c3.Instance = I2C3;
  hi2c3.Init.ClockSpeed = 100000;
  hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c3.Init.OwnAddress1 = 0;
  hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c3.Init.OwnAddress2 = 0;
  hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C3_Init 2 */

  /* USER CODE END I2C3_Init 2 */

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

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {  // Thay USART1 bằng UART của bạn
        if (rx_byte == '\n') {       // Kiểm tra ký tự LF
            rx_buffer[rx_index] = '\0'; // Kết thúc chuỗi
            rx_index = 0;            // Reset index
			osMessageQueuePut(myQueue04Handle, &rx_buffer, 0U, 0U);
        }
         else {
            if (rx_index < RX_BUFFER_SIZE - 1) {
                rx_buffer[rx_index++] = rx_byte; // Lưu byte vào buffer
            }
        }
        // Nhận tiếp byte mới
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
    }
}
// Hàm sắp xếp các task theo chu kỳ (tăng dần)
void sort_tasks_by_period(Task *tasks, int num_tasks) {
    for (int i = 0; i < num_tasks - 1; i++) {
        for (int j = i + 1; j < num_tasks; j++) {
            if ((tasks + i)->period > (tasks + j)->period) {
                // Hoán đổi task[i] và task[j]
                Task temp = *(tasks + i);
                *(tasks + i) = *(tasks + j);
                *(tasks + j) = temp;
            }
        }
    }
}

// Hàm cập nhật chu kỳ cho một task và điều chỉnh mức độ ưu tiên
void update_single_task_period(Task *tasks, int num_tasks, int task_id, int new_period) {
    // Tìm task theo ID và cập nhật chu kỳ
    for (int i = 0; i < num_tasks; i++) {
        if ((tasks + i)->id == task_id) {
            if ((tasks + i)->period != new_period) {
                (tasks + i)->period = new_period;  // Cập nhật chu kỳ
                (tasks + i)->changed = true;       // Đánh dấu đã thay đổi
            } else {
                (tasks + i)->changed = false;      // Không thay đổi
            }
            break;
        }
    }

    // Sắp xếp lại các task theo chu kỳ
    sort_tasks_by_period(tasks, num_tasks);

    // Cập nhật mức độ ưu tiên từ 29 đến 24
    for (int i = 0; i < num_tasks; i++) {
        (tasks + i)->priotity = 29 - i; // Gán mức độ ưu tiên
    }
}

// Hàm hiển thị thông tin các task
void display_tasks(Task *tasks, int num_tasks) {
    printf("ID\tPeriod\tExecTime\tDeadline\tPriority\tChanged\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("%d\t%d\t%d\t\t%d\t\t%d\t\t%s\n",
               (tasks + i)->id,
               (tasks + i)->period,
               (tasks + i)->execTime,
               (tasks + i)->deadline,
               (tasks + i)->priotity,
               (tasks + i)->changed ? "Yes" : "No");
    }
}
void updatePrevious(Task *previous, Task *current) {
    previous->period = current->period;
    previous->execTime = current->execTime;
    previous->deadline = current->deadline;
    previous->allPeriod = current->allPeriod;
    previous->priotity = current->priotity;
}
bool detectChange(Task *current, Task *previous){
    // So sánh từng trường
    if (current->period != previous->period ||
        current->execTime != previous->execTime ||
        current->deadline != previous->deadline ||
        current->priotity != previous->priotity ||
		current->allPeriod != previous->allPeriod) {
        current->changed = true; // Đánh dấu thay đổi
        return true;             // Có thay đổi
    }
    current->changed = false;    // Không có thay đổi
    return false;
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the MeasureTemp thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	//The parameters of task
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskReadTempDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[0].deadline);

	float temp;
	float timeInSeconds;
	//union FloatToBytes dataSend;
  /* Infinite loop */
  for(;;)
  {
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem bat dau task do nhiet do: %.3f\n", timeInSeconds);
	  temp = SHT2x_GetTemperature(1);
	 // print_cli("Nhiet do la %.3f", temp);

	  if (osKernelGetTickCount() > taskReadTempDeadline)
	  {
		  print_cli("Task Read Temperature missed deadline\n");
	  }
	  if (detectChange(&tasks[0], &prev_tasks[0]))
		{
			if(tasks[0].deadline != prev_tasks[0].deadline)
			{
				taskReadTempDeadline = taskReadTempDeadline + pdMS_TO_TICKS(tasks[0].period)
						- pdMS_TO_TICKS(prev_tasks[0].deadline) + pdMS_TO_TICKS(tasks[0].deadline);
				print_cli("TASK 01 THAY DOI DEADLINE\n");
			}
			if(tasks[0].priotity != prev_tasks[0].priotity)
			{
				osThreadSetPriority(MeasureTempHandle, tasks[0].priotity);
				print_cli("TASK 01 THAY DOI MUC DO UU TIEN\n");
			}
			// Cập nhật giá trị trước đó
			updatePrevious(&prev_tasks[0], &tasks[0]);
		 }

	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem ket thuc task do nhiet do: %.3f\n", timeInSeconds);
	  osMessageQueuePut(myQueue01Handle, &temp, 0U, 0U);
	  vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(tasks[0].period));
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the Realtime thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskReadTimeDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[1].deadline);
	DateTime dateTimeSend;
	float timeInSeconds;
  /* Infinite loop */
  for(;;)
  {
	timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	print_cli("Thoi diem bat dau task do thoi gian: %.3f\n", timeInSeconds);
	rtc_read_time(&dateTimeSend);

	//Check Deadline
	if (osKernelGetTickCount() > taskReadTimeDeadline)
	{
		print_cli("Task Read Time missed deadline\n");
	}
	if (detectChange(&tasks[1], &prev_tasks[1]))
	{
		// Cập nhật giá trị trước đó
		if(tasks[1].deadline != tasks[1].deadline)
		{
			taskReadTimeDeadline = taskReadTimeDeadline + pdMS_TO_TICKS(tasks[1].period)
							- pdMS_TO_TICKS(prev_tasks[1].deadline) + pdMS_TO_TICKS(tasks[1].deadline);
			print_cli("TASK 2 THAY DOI DEADLINE\n");
		}
		if(tasks[1].priotity != tasks[1].priotity)
		{
			osThreadSetPriority(RealtimeHandle, tasks[1].priotity);
			print_cli("TASK 2 THAY DOI MUC DO UU TIEN\n");
		}
		updatePrevious(&prev_tasks[1], &tasks[1]);
	 }
	timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	print_cli("Thoi diem ket thuc task do thoi gian: %.3f\n", timeInSeconds);
	osMessageQueuePut(myQueue02Handle, &dateTimeSend, 0U, 0U);
	//Delay until next period
	vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(pdMS_TO_TICKS(tasks[1].period)));
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the SendUart thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskDisplayTempDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[2].deadline);
	float tempRecv;
	char temStr[6];
	float timeInSeconds;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(myQueue01Handle, &tempRecv, NULL, osWaitForever);
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem bat dau task send nhiet do: %.3f\n", timeInSeconds);
	  sprintf(temStr, "T:%.3f", tempRecv);
	  print_cli("%s", temStr);
	  lcd_put_cur(0, 9);
	  lcd_send_string(&temStr);
	  	// Check deadline
		if (xTaskGetTickCount() > taskDisplayTempDeadline) {
			print_cli("Task Display Temperature missed deadline\n");
		}
		if (detectChange(&tasks[2], &prev_tasks[2]))
		{
			if(tasks[2].deadline != prev_tasks[2].deadline)
			{
				taskDisplayTempDeadline = taskDisplayTempDeadline + pdMS_TO_TICKS(tasks[2].period)
									- pdMS_TO_TICKS(prev_tasks[2].deadline) + pdMS_TO_TICKS(tasks[2].deadline);
				print_cli("TASK 3 THAY DOI DEADLINE\n");
			}
			if(tasks[2].priotity != prev_tasks[2].priotity)
			{
				osThreadSetPriority(DisplayTempHandle, tasks[2].priotity);
				print_cli("TASK 3 THAY DOI MUC DO UU TIEN\n");
			}
			// Cập nhật giá trị trước đó
			updatePrevious(&prev_tasks[2], &tasks[2]);
		 }
		timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
		print_cli("Thoi diem ket thuc task send nhiet do: %.3f\n", timeInSeconds);
		// Delay until next period
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(tasks[2].period));
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the SendLCD thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskDisplayTimeDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[3].deadline);
	DateTime dateTimeRecv;
	char timeStrTime[9];
	char timeStrDay[10];
	float timeInSeconds;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(myQueue02Handle, &dateTimeRecv, NULL, osWaitForever);
	  print_cli("Bat dau task display time\n");
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem bat dau task send thoi gian: %.3f\n", timeInSeconds);
	  sprintf(timeStrTime, "%02d:%02d:%02d", dateTimeRecv.hour, dateTimeRecv.min, dateTimeRecv.sec);
	  sprintf(timeStrDay, "%02d/%02d/20%02d", dateTimeRecv.day, dateTimeRecv.mon, dateTimeRecv.year);
	  lcd_put_cur(0, 0);
	  lcd_send_string(&timeStrTime);
	  print_cli("Current time: %s \nDay: %s\n", timeStrTime, timeStrDay);
	  lcd_put_cur(1, 0);
	  lcd_send_string(&timeStrDay);
	// Check deadline
	if (xTaskGetTickCount() > taskDisplayTimeDeadline) {
		print_cli("Task Display Time missed deadline\n");
	}
	if (detectChange(&tasks[3], &prev_tasks[3]))
	{
		if(tasks[3].deadline != prev_tasks[3].deadline)
		{
			taskDisplayTimeDeadline = taskDisplayTimeDeadline + pdMS_TO_TICKS(tasks[3].period)
							- pdMS_TO_TICKS(prev_tasks[3].deadline) + pdMS_TO_TICKS(tasks[3].deadline);
			print_cli("TASK 4 THAY DOI DEADLINE\n");
		}
		if(tasks[3].priotity != prev_tasks[3].priotity)
		{
			osThreadSetPriority(DisplayTimeHandle, tasks[3].priotity);
			print_cli("TASK 04 THAY DOI MUC DO UU TIEN\n");
		}
		// Cập nhật giá trị trước đó
		updatePrevious(&prev_tasks[3], &tasks[3]);
	 }
	timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	print_cli("Thoi diem ket thuc task send thoi gian: %.3f\n", timeInSeconds);
	// Delay until next period
	vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(tasks[3].period));
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the myTask05 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
	float rh;
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskReadRhDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[4].deadline);
	float timeInSeconds;
  /* Infinite loop */
  for(;;)
  {
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem bat dau task do do am: %.3f\n", timeInSeconds);
	  rh = SHT2x_GetRelativeHumidity(1);
	  if (osKernelGetTickCount() > taskReadRhDeadline)
		  {
			  print_cli("Task Read Temperature missed deadline\n");
		  }
	  if (detectChange(&tasks[4], &prev_tasks[4]))
	{
		  if(tasks[4].deadline != prev_tasks[4].deadline)
		  {
			  taskReadRhDeadline = taskReadRhDeadline + pdMS_TO_TICKS(tasks[4].period)
			  				- pdMS_TO_TICKS(prev_tasks[4].deadline) + pdMS_TO_TICKS(tasks[4].deadline);
			  print_cli("TASK 05 THAY DOI DEADLINE\n");
		  }
		  if(tasks[4].priotity != prev_tasks[4].priotity)
		  {
			  osThreadSetPriority(myTask05Handle, tasks[4].priotity);
			  print_cli("TASK 05 THAY DOI MUC DO UU TIEN\n");
		  }
		  // Cập nhật giá trị trước đó
		  updatePrevious(&prev_tasks[4], &tasks[4]);
	 }
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem ket thuc task do do am: %.3f\n", timeInSeconds);
	  osMessageQueuePut(myQueue03Handle, &rh, 0U, 0U);
	  vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(tasks[4].period));
  }
  /* USER CODE END StartTask05 */
}

/* USER CODE BEGIN Header_StartTask06 */
/**
* @brief Function implementing the myTask06 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask06 */
void StartTask06(void *argument)
{
  /* USER CODE BEGIN StartTask06 */
	TickType_t lastWakeTime = osKernelGetTickCount();
	taskDisplayRhDeadline = lastWakeTime + pdMS_TO_TICKS(tasks[5].deadline);
	float rhRecv;
	char rhStr[6];
	float timeInSeconds;
  /* Infinite loop */
  for(;;)
  {
	  osMessageQueueGet(myQueue03Handle, &rhRecv, NULL, osWaitForever);
	  timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
	  print_cli("Thoi diem bat dau task send do am: %.3f\n", timeInSeconds);
	  sprintf(rhStr, "r:%.1f", rhRecv);
	  print_cli("%s\n", rhStr);
	  lcd_put_cur(1, 10);
	  lcd_send_string(&rhStr);
	  // Check deadline
		if (xTaskGetTickCount() > taskDisplayRhDeadline) {
			print_cli("Task Display Temperature missed deadline\n");
		}
		if (detectChange(&tasks[5], &prev_tasks[5]))
		{
			if(tasks[5].deadline != prev_tasks[5].deadline)
			{
				taskDisplayRhDeadline = taskDisplayRhDeadline + pdMS_TO_TICKS(tasks[5].period)
									- pdMS_TO_TICKS(prev_tasks[5].deadline) + pdMS_TO_TICKS(tasks[5].deadline);
				print_cli("TASK 06 DA THAY DOI DEADLINE\n");
			}
			if(tasks[5].priotity != prev_tasks[5].priotity)
			{
				osThreadSetPriority(myTask05Handle, tasks[5].priotity);
				print_cli("TASK 06 DA THAY DOI MUC DO UU TIEN\n");
			}
			// Cập nhật giá trị trước đó
			updatePrevious(&prev_tasks[5], &tasks[5]);
		 }
		timeInSeconds = (float)osKernelGetTickCount() / configTICK_RATE_HZ;
		print_cli("Thoi diem ket thuc task send do am: %.3f\n", timeInSeconds);
		// Delay until next period
		vTaskDelayUntil(&lastWakeTime, pdMS_TO_TICKS(tasks[5].period));
  }
  /* USER CODE END StartTask06 */
}

/* USER CODE BEGIN Header_StartTask07 */
/**
* @brief Function implementing the myTask07 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask07 */
void StartTask07(void *argument)
{
  /* USER CODE BEGIN StartTask07 */
	 uint8_t Recv_ISR[20];
	TaskData taskData;
	int size;
	char m;
	int fieldRecv[12];
	int field[6];
	int idx;
	/* Infinite loop */
  for(;;)
  {
	osMessageQueueGet(myQueue04Handle, &Recv_ISR, NULL, osWaitForever);
	print_cli("Nhan tu ngat yeu cau thay doi thong so lap lich\n");
	// Chuyển đổi ký tự ASCII sang số nguyên
	    for (int i = 0; i < 12; i++) {
	        fieldRecv[i] = Recv_ISR[i] - '0'; // Trừ '0' để chuyển ký tự sang số
	    }

	    // Ghép các cặp số thành số có 2 chữ số
	    for (int j = 0; j < 6; j++) {
	        field[j] = fieldRecv[2 * j] * 10 + fieldRecv[2 * j + 1]; // Ghép số
	    }
	idx = field[0];
	for(int i = 0; i <= 5; i++)
		print_cli("IDX LA %d, %d\n", i, field[i]);
	//print_cli("Thay doi thong so Task %d\n", i+1);
	if(field[1] != 0 && tasks[idx].period != field[1] *100)
	{
		//tasks[i].period = field[1] * 100;
		update_single_task_period(tasks, 6, idx, field[1] * 100);
		print_cli("Chu ky thay doi %d\n",idx);
	}
	if(field[2] != 0)
	{
		print_cli("Thay doi thoi gian thuc thi\n");
	}
	if(field[3] != 0 && tasks[idx].deadline != field[3] * 100)
	{
		print_cli("Deadline thay doi %d\n", idx);
		tasks[idx].deadline = field[3] * 100;
	}
	if(field[4] != 0 && tasks[idx].allPeriod != field[4] * 100)
	{
		print_cli("Thay doi chu ky toan bo\n");
		for (int i = 0; i <= 5; i++)
			tasks[i].allPeriod = field[4] * 100;
	}if(field[5] != 0 && field[5] != tasks[idx].priotity)
	{
		print_cli("Muc uu tien phu thuoc vao deadline\n");
		tasks[idx].priotity = field[5];
	}
    osThreadYield();
  }
  /* USER CODE END StartTask07 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
