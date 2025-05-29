#include "debug_in_color.h"
#include "header.h"
#include <Arduino.h>
#include <I2S.h>

/**
 * usefull commands:
 * Compile, flash and monitor:
 * ❯ pio run --target upload --target monitor
 * Linux
 * ❯ sudo ~/.platformio/penv/bin/pio run --target upload 
 * clean
 * ❯ pio run --target fullclean --environment phenobottle_firmware 
 * Generate compile_commands.json (for clang-uml/neovim or simular):
 * ❯ pio run -t compiledb
 * List installed Libaries
 * ❯ platformio lib list
 * Install Libarie
 * ❯ platformio lib install "ArduinoJson"
 */

void check_headphones();

I2S i2s(OUTPUT, PIN_AUDIO_BCK, PIN_AUDIO_DIN);

void setup() {
  Serial.begin(69);
  Serial.println("Start");
  // for (uint8_t i = PIN_FIRST_PAD; i < (PIN_FIRST_PAD + nPAD); i++) {
  //   pinMode(i, INPUT);
  // }
  // test Audio Jack
  i2s.setBitsPerSample(32);
  if (!i2s.begin(32000)) {
    while (1) {
      Serial.println("Failed to initialize I2S!");
      delay(100);
    }
  }
  // test BUZZER
  // pinMode(PIN_BUZZ, OUTPUT);
  // analogWriteFreq(300);
  // analogWriteRange(100);
  // analogWrite(PIN_BUZZ, 50);
  pinMode(PIN_BUZZ, INPUT_PULLUP);
}

const int frequency = 440; // frequency of square wave in Hz
const int amplitude = 500; // amplitude of square wave
const int sampleRate = 32000; // minimum for UDA1334A

const int halfWavelength = (sampleRate / frequency); // half wavelength of square wave

int16_t sample = amplitude; // current sample value
int count = 0;
void loop() {
  // check_headphones();

  if (count % halfWavelength == 0) {
    sample = -1 * sample;
  }
  i2s.write(sample);
  i2s.write(sample);
  count++;
  //
  // static int i = 0;
  // float angle = 2 * PI * 440.0 * i / 44100;
  // int16_t sample = sin(angle) * 32767;
  // i2s.write(sample); // Left
  // i2s.write(sample); // Right
  // i++;
  // if (i >= 44100)
  //   i = 0;
}

uint32_t scan_keys() {
  uint32_t buffer = 0;
  for (uint8_t i = 0; i < 29; i++) {
    buffer | i << digitalRead(i);
  }
  return buffer;
}

void check_headphones() {
  const int DELAY = 100;
  static unsigned long timestamp = millis() + DELAY;
  if (millis() > timestamp) {
    timestamp = millis() + DELAY;

    static int print_before = 0;
    if (digitalRead(PIN_BUZZ) && !print_before) {
      Serial.print("Headphone plugged\n");
      print_before = 1;
    } else if (!digitalRead(PIN_BUZZ) && print_before) {
      Serial.print("Headphone unplugged\n");
      print_before = 0;
    }
  }
}
