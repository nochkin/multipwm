/* Very basic example to test the pwm library
 * Hook up an LED to pins 12, 13, 15, and you should see the intensity change
 *
 * Part of esp-open-rtos
 * Copyright (C) 2015 Javier Cardona (https://github.com/jcard0na)
 * BSD Licensed as described in the file LICENSE
 */
#include "espressif/esp_common.h"
#include "esp/uart.h"
#include "FreeRTOS.h"
#include "task.h"
#include "pwm.h"

void pwm_task(void *pvParameters)
{
    uint32_t counts[] = {500, 2100, 3000};
    int32_t   steps[] = {100,  300,  200};
    uint8_t    pins[] = { 12,   13,   15};

    pwm_init(3, pins, false);

    while(1) {
        pwm_stop();
        for (uint8_t ii=0; ii<3; ii++) {
            pwm_set_duty_channel(ii, counts[ii]);
            counts[ii] += steps[ii];
            if ((counts[ii] >= 10000) || (counts[ii] == 0)) {
                steps[ii] = -steps[ii];
            }
        }
        pwm_start();
        vTaskDelay(1);
    }
}

void user_init(void)
{
    uart_set_baud(0, 115200);
    printf("SDK version:%s\n", sdk_system_get_sdk_version());

    xTaskCreate(pwm_task, "tsk1", 256, NULL, 2, NULL);
}
