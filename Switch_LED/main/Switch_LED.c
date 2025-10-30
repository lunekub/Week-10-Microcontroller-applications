#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    // ตัวแปรสถานะ
    int SW1_Status = 0;
    int LED1_Status = 0;
    int SW2_Status = 0;
    int LED2_Status = 0;

    // -------------------- CONFIG --------------------
    // GPIO25, GPIO26 -> LED
    gpio_reset_pin(GPIO_NUM_25);
    gpio_set_direction(GPIO_NUM_25, GPIO_MODE_OUTPUT);

    gpio_reset_pin(GPIO_NUM_26);
    gpio_set_direction(GPIO_NUM_26, GPIO_MODE_OUTPUT);

    // GPIO32, GPIO33 -> Switch (input)
    gpio_reset_pin(GPIO_NUM_32);
    gpio_set_direction(GPIO_NUM_32, GPIO_MODE_INPUT);

    gpio_reset_pin(GPIO_NUM_33);
    gpio_set_direction(GPIO_NUM_33, GPIO_MODE_INPUT);

    // -------------------- MAIN LOOP --------------------
    while (1)
    {
        // อ่านค่าจากสวิตช์
        SW1_Status = gpio_get_level(GPIO_NUM_32);
        SW2_Status = gpio_get_level(GPIO_NUM_33);

        // สลับสถานะ LED ตามสวิตช์
        LED1_Status = !SW1_Status;
        LED2_Status = !SW2_Status;

        gpio_set_level(GPIO_NUM_25, LED1_Status);
        gpio_set_level(GPIO_NUM_26, LED2_Status);

        vTaskDelay(pdMS_TO_TICKS(100)); // 100 ms
    }
}
