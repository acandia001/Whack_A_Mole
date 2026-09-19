#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>


#define SLEEP_TIME_MS   250

#define angle 0

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct pwm_dt_spec servo_pwm = PWM_DT_SPEC_GET_BY_IDX(DT_PATH(zephyr_user),0);

int main() {
    int ret;

    if(!gpio_is_ready_dt(&led)) {
        return 0;
    }
    if (!pwm_is_ready_dt(&servo_pwm)) {
        return 0;
    }
    ret = gpio_pin_configure_dt(&led , GPIO_OUTPUT_ACTIVE);
    if(ret < 0) {
        return 0;
    }
    uint32_t pulse_ns = 500000 + (angle / 180) * (2500000 - 500000);

    pwm_set_pulse_dt(&servo_pwm, pulse_ns);
    while(1) {
        ret = gpio_pin_toggle_dt(&led);
        if(ret < 0) {
            return 0;
        }
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}