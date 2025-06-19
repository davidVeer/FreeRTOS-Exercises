#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment1_3.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_mac.h"

TaskHandle_t task1;
TaskHandle_t task2;

static const char *TAG = "LED";

void runAssignment_1_3(){
    xTaskCreate(Task1Code, "Task1", 10000,NULL,1,&task1);
    xTaskCreate(Task2Code, "Task2", 10000,NULL,10,&task2);
}

void Task1Code(void * parameter){
    for(;;){
    ESP_LOGI(TAG, "Task 1");
    }
}

void Task2Code(void * parameter){
    for(;;){
    ESP_LOGI(TAG, "Task 2");
    vTaskDelay(1);
    }
}

