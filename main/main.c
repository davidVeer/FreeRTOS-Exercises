#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "Assignment1_3.h"


static const char *TAG = "LED";

void app_main(void)
{
    runAssignment_1_3();
}
