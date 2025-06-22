#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "Assignment3_1.h"
/**
 * ESP32 Dining Philosophers
 * 
 * The classic "Dining Philosophers" problem in FreeRTOS form.
 * 
 * Based on http://www.cs.virginia.edu/luther/COA2/S2019/pa05-dp.html
 * 
 * Date: February 8, 2021
 * Author: Shawn Hymel
 * License: 0BSD
 */

static const char *TAG = "Dining Philosophers";

// Use only core 1 for demo purposes
static const BaseType_t app_cpu = 1;

// Settings
enum { NUM_TASKS = 5 };           // Number of tasks (philosophers)
enum { TASK_STACK_SIZE = 2048 };  // Bytes in ESP32, words in vanilla FreeRTOS

// Globals
static SemaphoreHandle_t bin_sem;   // Wait for parameters to be read
static SemaphoreHandle_t done_sem;  // Notifies main task when done
static SemaphoreHandle_t fork[NUM_TASKS];
static int ledPins[] = {23,22,21,19,18};

//*****************************************************************************
// Tasks

// The only task: eating
void eat(void *parameters) {
  int num, delay, lowerValueFork, higherValueFork;
  char buf[50];
  

  // Copy parameter and increment semaphore count
  num = *(int *)parameters;
  xSemaphoreGive(bin_sem);

    //determining the lower value fork
    int leftfork = num;
    int rightfork = (num+1)%NUM_TASKS;

    if (leftfork < rightfork){
        lowerValueFork = leftfork;
        higherValueFork = rightfork;
    }
    else{
        lowerValueFork = rightfork;
        higherValueFork = leftfork;
    }

    for(;;){

    xSemaphoreTake(fork[lowerValueFork], portMAX_DELAY);
    sprintf(buf, "Philosopher %i took chopstick %i", num, lowerValueFork);
    ESP_LOGI(TAG,"%s", buf);

    // Add some delay to force deadlock
    vTaskDelay(1 / portTICK_PERIOD_MS);

    xSemaphoreTake(fork[higherValueFork], portMAX_DELAY);
    sprintf(buf, "Philosopher %i took chopstick %i", num, higherValueFork);
    ESP_LOGI(TAG,"%s", buf);

    // Do some eating
    sprintf(buf, "Philosopher %i is eating", num);
    ESP_LOGI(TAG,"%s", buf);
    blink_led(ledPins[num], 1);
    delay = random()%1000;
    vTaskDelay(delay / portTICK_PERIOD_MS);
    blink_led(ledPins[num], 0);

    // Put down right chopstick
    xSemaphoreGive(fork[higherValueFork]);
    sprintf(buf, "Philosopher %i returned chopstick %i", num, higherValueFork);
    ESP_LOGI(TAG,"%s", buf);

    // Put down left chopstick
    xSemaphoreGive(fork[lowerValueFork]);
    sprintf(buf, "Philosopher %i returned chopstick %i", num, lowerValueFork);
    ESP_LOGI(TAG,"%s", buf);

    delay = random()%1000;
    vTaskDelay(delay / portTICK_PERIOD_MS);
    ESP_LOGI(TAG,"Philosopher is thinking for %d milliseconds", delay);
    }
}

//*****************************************************************************
// Main (runs as its own task with priority 1 on core 0 )

void run_Assignment3_1() {

  char task_name[20];
  ESP_LOGI(TAG,"---FreeRTOS Dining Philosophers Challenge---");

  // Create kernel objects before starting tasks
  bin_sem = xSemaphoreCreateBinary();
  for (int i = 0; i < NUM_TASKS; i++) {
    configure_led(ledPins[i]);
    fork[i] = xSemaphoreCreateMutex();
  }

  // Have the philosphers start eating
  for (int i = 0; i < NUM_TASKS; i++) {
    sprintf(task_name, "Philosopher %u", i);
    xTaskCreatePinnedToCore(eat,
                            task_name,
                            TASK_STACK_SIZE,
                            (void *)&i,
                            1,
                            NULL,
                            app_cpu);
    xSemaphoreTake(bin_sem, portMAX_DELAY);
  }
}

static void configure_led(int pin)
{
    ESP_LOGI(TAG, "Example configured to blink GPIO LED!");
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}

static void blink_led(int pin, int state)
{
    gpio_set_level(pin, state);
}
