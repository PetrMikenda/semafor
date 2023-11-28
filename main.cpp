#include "mbed.h"

#include "LCD_DISCO_F469NI.h"

LCD_DISCO_F469NI lcd;

Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;
Thread thread5;
Thread thread6;

int xSize;
int ySize;

typedef struct {
    uint32_t color;
    uint32_t park_time;
    uint32_t drive_time;
} Car;



// void ctvrty() {
//     //lcd.Clear(LCD_COLOR_BLUE);
    
//     lcd.SetTextColor(LCD_COLOR_YELLOW);
    
//     //lcd.DrawRect(0,0,lcd.GetXSize()/2,lcd.GetYSize()/2);
//     lcd.FillRect(lcd.GetXSize()/2,lcd.GetYSize()/2, lcd.GetXSize()/2,lcd.GetYSize()/2);
// }
// main() runs in its own thread in the OS
int main()
{   
    Car cars[6];
    cars[0].color = LCD_COLOR_WHITE;
    cars[1].color = LCD_COLOR_RED;
    cars[2].color = LCD_COLOR_BLUE;
    cars[3].color = LCD_COLOR_GREEN;
    cars[4].color = LCD_COLOR_YELLOW;
    cars[5].color = LCD_COLOR_ORANGE;

    for (int i = 0; i < 5; i++) {
        
        cars[i].park_time = rand() % 5 + 1; // Simulace náhodné doby parkování (1-5 sekund)
        cars[i].drive_time = rand() % 5 + 1; // Simulace náhodné doby jízdy mimo parkoviště (1-5 sekund)
    }

    while (true) {
        
    }
}

