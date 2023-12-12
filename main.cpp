#include "mbed.h"
#include "LCD_DISCO_F469NI.h"
#include "stm32469i_discovery_lcd.h"
#include <chrono>
#include <stack>

LCD_DISCO_F469NI lcd;

Thread thread1;
Thread thread2;
Thread thread3;
Thread thread4;
Thread thread5;
Thread thread6;

Mutex parkingMutex;
Semaphore parkingSemaphore(4);

const int numParkingSpaces = 4;
std::stack<int>  freeParkingSpaces;

int xSize;
int ySize;

typedef struct {
    uint32_t color;
    uint32_t number;
    uint32_t park_time;
    uint32_t drive_time;
} Car;

void parkCar(Car* car) {

    parkingSemaphore.acquire();

    parkingMutex.lock();

    int parkingSpace = -1;
    if (!freeParkingSpaces.empty()) {
        parkingSpace = freeParkingSpaces.top();
        freeParkingSpaces.pop();
    }

    parkingMutex.unlock();
    ThisThread::sleep_for(std::chrono::milliseconds(500));

    if (parkingSpace != -1) {
            lcd.SetTextColor(car->color);
            lcd.FillRect(parkingSpace * (xSize / numParkingSpaces), 0, xSize / numParkingSpaces, ySize);

            ThisThread::sleep_for(std::chrono::seconds(car->park_time));

            parkingMutex.lock();

            lcd.SetTextColor(LCD_COLOR_BLACK);
            lcd.FillRect(parkingSpace * (xSize / numParkingSpaces), 0, xSize / numParkingSpaces, ySize);

            freeParkingSpaces.push(parkingSpace);
            parkingMutex.unlock();

            parkingSemaphore.release();

            ThisThread::sleep_for(std::chrono::seconds(car->drive_time));
    }
}

void carThread(Car* car) {
    while (true) {
        parkCar(car);
    }
}

int main() {
    xSize = lcd.GetXSize();
    ySize = lcd.GetYSize();

    for (int i = numParkingSpaces; i > 0; i--) {
        freeParkingSpaces.push(i);
    }

    Car cars[6];
    cars[0].color = LCD_COLOR_WHITE;
    cars[1].color = LCD_COLOR_RED;
    cars[2].color = LCD_COLOR_BLUE;
    cars[3].color = LCD_COLOR_GREEN;
    cars[4].color = LCD_COLOR_YELLOW;
    cars[5].color = LCD_COLOR_GRAY;

    for (int i = 0; i < 6; i++) {
        cars[i].park_time = rand() % 5 + 1;
        cars[i].drive_time = rand() % 5 + 1;
        cars[i].number = i;
        
           switch (i) {
                case 0:
                    thread1.start(callback(carThread,&cars[i]));
                    break;
                case 1:
                    thread2.start(callback(carThread,&cars[i]));
                    break;
                case 2:
                    thread3.start(callback(carThread,&cars[i]));
                    break;
                case 3:
                    thread4.start(callback(carThread,&cars[i]));
                    break;
                case 4:
                    thread5.start(callback(carThread,&cars[i]));
                    break;
                case 5:
                    thread6.start(callback(carThread,&cars[i]));
                    break;
            }
        }


    while (true) {
    }
}
