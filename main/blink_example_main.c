#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "Assignment1Component.h"


static const char *TAG = "LED";

void app_main(void)
{
    run_Blink();
}
