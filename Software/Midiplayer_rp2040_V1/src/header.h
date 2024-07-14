/*-----------Header file for global defines, objekts, variables and functions-----------*/
#ifndef HEADER_H
#define HEADER_H

#include <Arduino.h>
/*--------Settings-----------------------*/
#define DEBUG_MODE 1    /*actrivates debug statements. 0=disable,1=Serial,2=TCP*/
#define COLOUR_SERIAL 1 /*activates/deactivates Serial.printing with color*/
#define USB_ENABLE 0    /*enables single drive USB functions*/
#define ADC_REF 3.0
#define ADC_RES 12 // ADC Resolution in Bit
#define ADC_MAX_READ (pow(2, ADC_RES) - 1)
const unsigned int ADC_MAX_WRITE = 100; //  Value where analogRrite = 100% duty cycle
const unsigned int ADC_FREQ_WRITE = 30000;

#define WATCHDOG_TIMEOUT 2000 // neds to be 8000ms max i think
#define CONNECTIONTIMEOUT 20  /*Conntection Timeout of the tcp client*/

extern unsigned long nMOTHERBOARD_BOOTUPS; // this number is stored in the flash and increses with every reset of th uC
/*----------------Pin mapping-------------*/
typedef enum
{
    PIN_FIRST_PAD = 0,
    nPAD = 16,
    PIN_PAD_TOP = 18,
    PIN_PAD_BOTTOM = 19,
    PIN_BUTTON_0 = 20,
    PIN_BUTTON_1 = 21,
    PIN_BUZZ = 22,
    PIN_HEADPHONE_CONNECT = 22,
    PIN_AUDIO_0 = 23,
    PIN_SD_MOSI = 24,
    PIN_SD_CS = 25,
    PIN_SD_SCK = 26,
    PIN_SD_MISO = 27,
    PIN_AUDIO_1 = 28,
    PIN_AUDIO_2 = 29
} PIN_MAPPING;

uint32_t scan_keys();

#endif
