#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment2_0.h"
#include "esp_log.h"

static const char *TAG = "Assignment-0";

TaskHandle_t Task1;
TaskHandle_t Task2;

void Task1code( void * parameter ){
ESP_LOGI(TAG,"Task1 running on core ");
ESP_LOGI(TAG, "%d", (uint) xPortGetCoreID());
for(;;){}
}

void Task2code( void * pvParameters ){
ESP_LOGI(TAG,"Task2 running on core ");
ESP_LOGI(TAG,"%d", (uint) xPortGetCoreID());
for(;;){}
}

void setup() {
xTaskCreatePinnedToCore(Task1code,"Task1",10000,NULL,1,&Task1,0);
xTaskCreatePinnedToCore(Task2code,"Task2",10000,NULL,1,&Task2,1);
}
