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
    int timesDelayed = 0;
    ESP_LOGI(TAG, "Task is opgezet");
    for(;;){
    vTaskDelay(4000/portTICK_PERIOD_MS);
    ESP_LOGI(TAG, "weer 4 seconde");
    timesDelayed++;
    timesDelayed = CheckAndUpdatePriority(timesDelayed);
    }
}

int CheckAndUpdatePriority(int timesDelayed){
    static int priority;

    if (timesDelayed < 2) return timesDelayed;

    timesDelayed = 0;
    priority = uxTaskPriorityGet(NULL) -1;
    vTaskPrioritySet(NULL,priority);
    ESP_LOGI(TAG, "Task currently has a Priority of: %d",priority);

    if (priority > 1) return timesDelayed;

    ESP_LOGE(TAG, "Task is being deleted");
    vTaskDelete(NULL);

    return NULL;
}
