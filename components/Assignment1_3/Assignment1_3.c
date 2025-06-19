#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment1_3.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "esp_mac.h"

TaskHandle_t task1;
TaskHandle_t task2;

static const char *TAG = "CoreTasks";

void runAssignment_1_3(){
    xTaskCreatePinnedToCore(TaskCode, "Task1", 10000,NULL,1,&task1,0);
    xTaskCreatePinnedToCore(TaskCode, "Task2", 10000,NULL,10,&task2,1);
}

void TaskCode(void * parameter){
    for(;;){
    ESP_LOGI(TAG, "Task is running on core %u",(uint) xPortGetCoreID());
    }
}


