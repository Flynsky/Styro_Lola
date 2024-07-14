#include <Arduino.h>
#include "header.h"
#include "debug_in_color.h"

void setup()
{
  Serial.begin(69);
  Serial.println("Start");
  for (uint8_t i = PIN_FIRST_PAD; i < (PIN_FIRST_PAD + nPAD); i++)
  {
    pinMode(i, INPUT);
  }
}

void loop()
{
  debug("pressed keys:");
  debugln(scan_keys(),BIN);
  delay(100);
}

uint32_t scan_keys()
{
  uint32_t buffer = 0;
  for (uint8_t i = 0; i < 29; i++)
  {
    buffer | i<<digitalRead(i);
  }
  return buffer;
}
