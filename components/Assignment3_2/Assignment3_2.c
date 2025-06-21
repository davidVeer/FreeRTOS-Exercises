#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Assignment3_2.h"
#include "freertos/queue.h"

QueueHandle_t DB_queue;   // data buffer
QueueHandle_t PA_queue;   // pallet A
QueueHandle_t PB_queue;   // pallet B
QueueHandle_t PC_queue;   // pallet C

typedef struct {
    char type; // 'A', 'B' of 'C'
} Product;

void ProducerTask(void *pvParameters) {
    char productType = *(char *)pvParameters;
    Product p;

    while (1) {
        p.type = productType;

        if (xQueueSend(DB_queue, &p, portMAX_DELAY) == pdPASS) {
            printf("Producer %c -> geplaatst in DB\n", productType);
        }

        vTaskDelay((500 + random() % 500)/portTICK_PERIOD_MS);
    }
}

void ConsumerTask(void *pvParameters) {
    char consumerType = *(char *)pvParameters;
    Product p;

    while (1) {
        if (xQueueReceive(DB_queue, &p, portMAX_DELAY) == pdPASS && p.type == consumerType) {
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

                xQueueSend(targetPallet, &p, portMAX_DELAY);
                printf("Consumer %c <- gepakt uit DB en geplaatst op pallet\n", consumerType);
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
    DB_queue = xQueueCreate(10, sizeof(Product));
    PA_queue = xQueueCreate(10, sizeof(Product));
    PB_queue = xQueueCreate(10, sizeof(Product));
    PC_queue = xQueueCreate(10, sizeof(Product));

    if (DB_queue == NULL || PA_queue == NULL || PB_queue == NULL || PC_queue == NULL) {
        printf("FOUT: Queue creatie mislukt.\n");
        while (1);
    }

    static char a = 'A', b = 'B', c = 'C';

    xTaskCreate(ProducerTask, "ProducerA", 1000, &a, 1, NULL);
    xTaskCreate(ProducerTask, "ProducerB", 1000, &b, 1, NULL);
    xTaskCreate(ProducerTask, "ProducerC", 1000, &c, 1, NULL);

    xTaskCreate(ConsumerTask, "ConsumerA", 1000, &a, 1, NULL);
    xTaskCreate(ConsumerTask, "ConsumerB", 1000, &b, 1, NULL);
    xTaskCreate(ConsumerTask, "ConsumerC", 1000, &c, 1, NULL);

    xTaskCreate(ShowStatusTask, "Status", 1000, NULL, 1, NULL);
}