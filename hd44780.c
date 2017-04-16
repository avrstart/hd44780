#include "hd44780.h"  

struct hd44780_operations *lcd_ops;

static void lcd_set_nibble(uint8_t data_byte);
static void lcd_send_nibble(uint8_t data_byte, uint8_t datacom);
static void lcd_send(uint8_t data_byte, uint8_t dc);

static void lcd_set_nibble(uint8_t data_byte) 
{
    lcd_ops->hd44780_write_pin(HD44780_D4_PIN, 0);
    lcd_ops->hd44780_write_pin(HD44780_D5_PIN, 0);
    lcd_ops->hd44780_write_pin(HD44780_D6_PIN, 0);
    lcd_ops->hd44780_write_pin(HD44780_D7_PIN, 0);
    
	if (data_byte & 0x1) {  lcd_ops->hd44780_write_pin(HD44780_D4_PIN, 1); }
	if (data_byte & 0x2) {  lcd_ops->hd44780_write_pin(HD44780_D5_PIN, 1); }
	if (data_byte & 0x4) {	lcd_ops->hd44780_write_pin(HD44780_D6_PIN, 1); }
	if (data_byte & 0x8) {	lcd_ops->hd44780_write_pin(HD44780_D7_PIN, 1); }    
}

static void lcd_send_nibble(uint8_t data_byte, uint8_t datacom) 
{
    lcd_ops->hd44780_write_pin(HD44780_EN_PIN, 0);
    lcd_ops->hd44780_write_pin(HD44780_RS_PIN, 0);

	lcd_set_nibble(data_byte);

	if (datacom) {
		lcd_ops->hd44780_write_pin(HD44780_RS_PIN, 1);
	}
    lcd_ops->hd44780_delay_us(10);
	lcd_ops->hd44780_write_pin(HD44780_EN_PIN, 1);
}

static void lcd_send(uint8_t data_byte, uint8_t dc) 
{
	uint8_t data_tbyte;

	lcd_ops->hd44780_write_pin(HD44780_EN_PIN, 0);
    lcd_ops->hd44780_write_pin(HD44780_RS_PIN, 0);
    
	lcd_set_nibble(0x0);

	data_tbyte = data_byte;
	data_tbyte >>= 4;
	lcd_send_nibble(data_tbyte, dc);
    lcd_ops->hd44780_delay_ms(1);
	lcd_ops->hd44780_write_pin(HD44780_EN_PIN, 0);
    
    lcd_ops->hd44780_delay_us(40); 
    
	lcd_send_nibble(data_byte, dc);
    lcd_ops->hd44780_delay_us(2);
    
	lcd_ops->hd44780_write_pin(HD44780_EN_PIN, 0);   
    lcd_ops->hd44780_delay_us(40);
}

void hd44780_gotoxy(uint8_t pos_x, uint8_t pos_y) 
{
	if (pos_y == 0) {
		lcd_send(((1 << 7) | (pos_x)), 0);
	} else {
		lcd_send(((3 << 6) | (pos_x)), 0);
	}
}

void hd44780_clear(void) 
{
	lcd_send(0x01, 0);
    lcd_ops->hd44780_delay_ms(2);
}

void hd44780_putchar(uint8_t ascii_symb)
{
    lcd_send(ascii_symb, 1);
}

void hd44780_init(struct hd44780_operations *init_hd44780) 
{
    lcd_ops = init_hd44780;
    
    lcd_ops->hd44780_delay_ms(40);

	lcd_send_nibble(0x3, 0);

    lcd_ops->hd44780_delay_ms(5);
	lcd_send_nibble(0x03, 0);

    lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x03, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x02, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x02, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x08, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x0, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x01, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x0, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x0f, 0);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x0, 1);

	lcd_ops->hd44780_delay_us(200);
	lcd_send_nibble(0x0, 1);

	lcd_ops->hd44780_delay_us(200);
	lcd_send(0x08, 0);
	lcd_send(0x0c, 0);
	hd44780_clear();
	lcd_send(0x06, 0);

    lcd_ops->hd44780_delay_ms(100);
}
