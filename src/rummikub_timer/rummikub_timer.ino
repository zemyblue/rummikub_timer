// reference: https://github.com/hibit-dev/buzzer/tree/master/lib
#include <pitches.h>
#include <millisDelay.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "PlayBuzzer.h"
#include "TimerDisplay.h"

#define TIMER_INTERVAL_MS    2000

int BUZZERPIN = 9;

int timer_melody[] = {
  NOTE_F4,10,
  NOTE_F4,10,
  NOTE_F4,10,
  NOTE_B5,5
};

PlayBuzzer buzzer(BUZZERPIN);

// setting data
int settingTime = 20;
int current = settingTime;

// state data
bool isSoundOn = true;
bool isRunning = true;


void setup() {
  Serial.begin(9600);
  Serial.println("Rummikub Timer");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // draw init screen
  drawTimerScreen(settingTime, current, isSoundOn);
}

void loop() {
  static uint32_t lastTime = 0;
  static uint32_t currTime;

  currTime = millis();
  if (currTime - lastTime > TIMER_INTERVAL_MS) {
    lastTime = currTime;

    if (isRunning) {
      if (current >= 0) {
        drawTimerScreen(settingTime, current, isSoundOn);
        Serial.print("rest time: "); Serial.println(current);

        // play buzzer
        if (current == 0) {
          buzzer.playTone(NOTE_B5, 2000);
        } else if (current < 10) {
          buzzer.playTone(NOTE_B4, 600);
        } else if (current < 30) {
          buzzer.playTone(NOTE_A3, 200);
        }

        current--;
      } else {
        // stop && reset
        isRunning = false;
        current = settingTime;
      }
    }
  }

  buzzer.loop();
}
