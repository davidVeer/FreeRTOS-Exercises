#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment2_1.h"
#include "esp_log.h"

static const char *TAG = "Assignment2-1";

void run_Assignment2_1(){
    xTaskCreatePinnedToCore(Core_0_TaskLifecycle,"DecayTask",10000,NULL,6,NULL,0);
}

void Core_0_TaskLifecycle(){
    for(;;){
    static int timesDelayed = 0;
    int priority = uxTaskPriorityGet(NULL);
    ESP_LOGI(TAG, "Task currently has a Priority of: %d",priority);
    vTaskDelay(4000/portTICK_PERIOD_MS);
    }
}