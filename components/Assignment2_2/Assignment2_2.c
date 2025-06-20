#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment2_2.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "Assignment2_2";
    int greenLedTaskParameters[2] = {18,200};
    int redLedTaskParameters[2] = {23,1000};


void run_Assignment2_2(){
    configureLed(redLedTaskParameters[0]);
    configureLed(greenLedTaskParameters[0]);
    
    xTaskCreatePinnedToCore(
        BlinkLedWithInterval,           //Task function
        "redLedTask",                   // task Name
        10000,                          //stackDepth
        (void *)redLedTaskParameters,   //parameters
        10,                             // priority
        NULL,                           // Taskhandle
        0                               // Core ID
    );

    xTaskCreatePinnedToCore(
        BlinkLedWithInterval,           //Task function
        "greenLedTask",                 // task Name
        10000,                          //stackDepth
        (void *)greenLedTaskParameters, //parameters
        10,                             // priority
        NULL,                           // Taskhandle
        1                               // Core ID
    );
}

void BlinkLedWithInterval(void * pvParameters){
    int ledState = 0;
    int *parameters = pvParameters;
    int pin = *(parameters);
    int interval = *(parameters + 1);

    for(;;){
        gpio_set_level(pin, ledState);
        ledState = !ledState;
        ESP_LOGI(TAG, "Changed pin: %d state to %d", pin, ledState);
        vTaskDelay(interval/portTICK_PERIOD_MS);
    }
}

void configureLed(int pin){
    ESP_LOGI(TAG, "configured Led on pin: %d", pin);
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}



