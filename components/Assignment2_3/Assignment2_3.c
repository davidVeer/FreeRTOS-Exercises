#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "Assignment2_3.h"

static const char *TAG = "Assignment2_3";

void run_Assignment2_3(){
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task1",10000,1,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task2",10000,2,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task3",10000,3,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task4",10000,4,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task5",10000,5,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task6",10000,6,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task7",10000,7,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task8",10000,8,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task9",10000,9,10,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task10",10000,10,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task11",10000,11,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task12",10000,12,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task13",10000,13,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task14",10000,14,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task15",10000,15,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task16",10000,16,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task17",10000,17,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task18",10000,18,1,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task19",10000,19,10,NULL,0);
    xTaskCreatePinnedToCore(
        GenericTaskCode,"Task20",10000,20,1,NULL,0);
}

void GenericTaskCode(int taskNumber){
    for(;;){
        ESP_LOGI(TAG, "this is Task %d", taskNumber);
    }
}

void DelayedTaskCode(int taskNumber){
    for(;;){
        ESP_LOGI(TAG, "this is Task %d", taskNumber);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}


