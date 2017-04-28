#include "hd44780.h"

struct hd44780_operations hd44780_ops = {
        .hd44780_delay_us = delay_us,
        .hd44780_delay_ms = delay_ms,    
        .hd44780_write_pin = gpio_set_value_remote
};

void gpio_set_value_remote(uint16_t pin, uint8_t value)
{
    switch (pin) {
        case HD44780_EN_PIN:
            i2c_write_pin(2, value);
            break;
        case HD44780_RS_PIN:
            i2c_write_pin(0, value);
            break;
        case HD44780_RW_PIN:
            i2c_write_pin(1, value);
            break;       
        case HD44780_D4_PIN:
            i2c_write_pin(4, value);
            break;
        case HD44780_D5_PIN:
            i2c_write_pin(5, value);
            break;
        case HD44780_D6_PIN:
            i2c_write_pin(6, value);
            break;
        case HD44780_D7_PIN:
            i2c_write_pin(7, value);
            break;
        default:
            break;
    }
}

void main(void)
{   
    hd44780_init(&hd44780_ops); 
    hd44780_puts("hello");       
}



