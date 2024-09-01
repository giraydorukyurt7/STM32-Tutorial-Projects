// ------------------Functions------------------
//
// lcd_send_cmd    : LCD'ye komut gönderir. 
//                   Komutların üst ve alt yarısını gönderir 
//                   ve her iki durumda da enable (E) 
//                   pinini kontrol eder.
//
// lcd_send_data   : LCD'ye veri gönderir. 
//                   Verinin üst ve alt yarısını gönderir 
//                   ve enable (E) pinini kontrol eder.
//
// lcd_clear       : LCD ekranını temizler.
//
// lcd_init        : LCD'yi başlatır ve gerekli başlangıç 
//                   komutlarını gönderir.
//
// lcd_send_string : LCD'ye bir dizi karakter gönderir.
//
// lcd_put_cur     : LCD'deki belirli bir konuma gitmek 
//                   için kullanılır (satır ve sütun konumu).
//




#include "i2c-lcd.h"
#include "stm32f1xx_hal.h"

extern I2C_HandleTypeDef hi2c1;

#define LCD_ADDR 0x4E // LCD adresi, kontrol edin ve gerekirse değiştirin

// LCD'ye komut gönderir
void lcd_send_cmd(char cmd) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (cmd & 0xF0);
    data_l = ((cmd << 4) & 0xF0);
    data_t[0] = data_u | 0x0C; // RS=0, RW=0, E=1
    data_t[1] = data_u | 0x08; // RS=0, RW=0, E=0
    data_t[2] = data_l | 0x0C; // RS=0, RW=0, E=1
    data_t[3] = data_l | 0x08; // RS=0, RW=0, E=0
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_t, 4, 100);
}

// LCD'ye veri gönderir
void lcd_send_data(char data) {
    char data_u, data_l;
    uint8_t data_t[4];
    data_u = (data & 0xF0);
    data_l = ((data << 4) & 0xF0);
    data_t[0] = data_u | 0x0D; // RS=1, RW=0, E=1
    data_t[1] = data_u | 0x09; // RS=1, RW=0, E=0
    data_t[2] = data_l | 0x0D; // RS=1, RW=0, E=1
    data_t[3] = data_l | 0x09; // RS=1, RW=0, E=0
    HAL_I2C_Master_Transmit(&hi2c1, LCD_ADDR, data_t, 4, 100);
}

// LCD ekranını temizler
void lcd_clear(void) {
    lcd_send_cmd(0x01); // Clear display command
    HAL_Delay(2); // LCD'nin ekranı temizleme süresi
}

// LCD'yi başlatır
void lcd_init(void) {
    HAL_Delay(50); // Güç açma gecikmesi
    lcd_send_cmd(0x30);
    HAL_Delay(5);
    lcd_send_cmd(0x30);
    HAL_Delay(1);
    lcd_send_cmd(0x30);
    HAL_Delay(10);
    lcd_send_cmd(0x20); // 4-bit mod
    HAL_Delay(10);

    lcd_send_cmd(0x28); // 4-bit mod, 2 satır, 5x8 font
    HAL_Delay(1);
    lcd_send_cmd(0x08); // Ekran kapalı
    HAL_Delay(1);
    lcd_send_cmd(0x01); // Ekranı temizle
    HAL_Delay(1);
    lcd_send_cmd(0x06); // Giriş modunu ayarla
    HAL_Delay(1);
    lcd_send_cmd(0x0C); // Ekranı aç, imleç kapalı
}

// LCD'ye bir dizi karakter gönderir
void lcd_send_string(char *str) {
    while (*str) lcd_send_data(*str++);
}

// LCD'deki belirli bir konuma gitmek için fonksiyon
void lcd_put_cur(uint8_t row, uint8_t col) {
    uint8_t addr;
    if (row == 0) addr = 0x80 + col; // İlk satır
    else if (row == 1) addr = 0xC0 + col; // İkinci satır
    lcd_send_cmd(addr);
}
