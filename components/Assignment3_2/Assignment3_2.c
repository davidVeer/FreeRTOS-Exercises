#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment3_2.h"
#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "factory with cueues";

QueueHandle_t DB_queue;   // data buffer
QueueHandle_t PA_queue;   // pallet A
QueueHandle_t PB_queue;   // pallet B
QueueHandle_t PC_queue;   // pallet C

char productA = 'A';
char productB = 'B';
char productC = 'C';

void ProducerTask(void *pvParameters) {
    char productType = *(char*)pvParameters;
    char product;
    ESP_LOGI(TAG,"programma is in de producer task met product type %c", productType);
    for(;;){
        product = productType;
        if (xQueueSend(DB_queue, &product, portMAX_DELAY) == pdPASS) {
            ESP_LOGI(TAG,"Producer %c -> geplaatst in DB", productType);
        }

        vTaskDelay((500 + random() % 500)/portTICK_PERIOD_MS);
    }
}

void ConsumerTask(void *pvParameters) {
    char consumerType = *(char *)pvParameters;
    char product;

    for(;;){
        if (xQueueReceive(DB_queue, &product, portMAX_DELAY) == pdPASS) {
            if (product == consumerType){
            QueueHandle_t targetPallet;
            switch (consumerType) {
                case 'A': 
                    targetPallet = PA_queue; 
                    break;
                case 'B':
                    targetPallet = PB_queue;
                    break;
                case 'C': 
                    targetPallet = PC_queue; 
                    break;
                 default:
                    targetPallet = PA_queue; 
                    break;
                }

                xQueueSend(targetPallet, &product, portMAX_DELAY);
                ESP_LOGI(TAG,"Consumer %c <- gepakt uit DB en geplaatst op pallet", consumerType);
            }
           else {
                xQueueSendToFront(DB_queue, &product, portMAX_DELAY);
                ESP_LOGI(TAG,"Package was placed back to db queue");
           }
        }
    }
}

void ShowStatusTask(void *pvParameters) {
    while (1) {
        printf("\n--- Queue Status ---\n");
        printf("DB  : %d\n", uxQueueMessagesWaiting(DB_queue));
        printf("PA  : %d\n", uxQueueMessagesWaiting(PA_queue));
        printf("PB  : %d\n", uxQueueMessagesWaiting(PB_queue));
        printf("PC  : %d\n", uxQueueMessagesWaiting(PC_queue));
        printf("--------------------\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void run_Assignment3_2(void) {
    DB_queue = xQueueCreate(100, sizeof(char));
    PA_queue = xQueueCreate(100, sizeof(productA));
    PB_queue = xQueueCreate(100, sizeof(productB));
    PC_queue = xQueueCreate(100, sizeof(productC));

    if (DB_queue == NULL || PA_queue == NULL || PB_queue == NULL || PC_queue == NULL) {
        ESP_LOGI(TAG,"FOUT: Queue creatie mislukt.");
        return;
    }

    xTaskCreate(ProducerTask, "ProducerA", 10000, &productA, 1, NULL);
    xTaskCreate(ProducerTask, "ProducerB", 10000, &productB, 1, NULL);
    xTaskCreate(ProducerTask, "ProducerC", 10000, &productC, 1, NULL);

    xTaskCreate(ConsumerTask, "ConsumerA", 10000, &productA, 1, NULL);
    xTaskCreate(ConsumerTask, "ConsumerB", 10000, &productB, 1, NULL);
    xTaskCreate(ConsumerTask, "ConsumerC", 10000, &productC, 1, NULL);

    xTaskCreate(ShowStatusTask, "Status", 10000, NULL, 1, NULL);
}

