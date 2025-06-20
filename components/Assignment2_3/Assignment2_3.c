#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "Assignment2_3.h"

static const char *TAG = "Assignment2_3";

void run_Assignment2_3(){
    
}

void GenericTaskCode(int taskNumber){
    for(;;){
        ESP_LOGI(TAG, "this is Task %d", taskNumber);
    }
}

void DelayedTaskCode(int taskNumber){
    for(;;){
        ESP_LOGI(TAG, "this is Task %d", taskNumber);
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

void WaitingTaskCode(int taskNumber){
    for(;;){
        ESP_LOGI(TAG, "this is Task %d", taskNumber);
        
    }
}




