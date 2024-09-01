#include <stdint.h>

#ifndef __I2C_LCD_H
#define __I2C_LCD_H

void lcd_init(void);
void lcd_send_cmd(char cmd);
void lcd_send_data(char data);
void lcd_send_string(char *str);
void lcd_clear(void);
void lcd_put_cur(uint8_t row, uint8_t col);

#endif
