#ifndef HD44780_H
#define HD44780_H

#include <stdint.h>

typedef enum
{ 
    HD44780_EN_PIN = 0,
    HD44780_RS_PIN = 1,
    HD44780_RW_PIN = 2,
    HD44780_D4_PIN = 3,
    HD44780_D5_PIN = 4,
    HD44780_D6_PIN = 5,
    HD44780_D7_PIN = 6
}HD44780_PINS;

struct hd44780_operations {
    
    void (*hd44780_delay_us) (uint32_t us);
    void (*hd44780_delay_ms) (uint32_t ms);    
    void (*hd44780_write_pin) (uint16_t gpio_pin, uint8_t pin_state);
};

void hd44780_gotoxy(uint8_t pos_x, uint8_t pos_y);
void hd44780_clear(void);
void hd44780_init(struct hd44780_operations *init_hd44780);
void hd44780_putchar(uint8_t ascii_symb);
void hd44780_puts(const uint8_t *ascii_string);
void hd44780_cursor(uint8_t cur_state);
    
#endif 

