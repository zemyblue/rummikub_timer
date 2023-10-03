// reference: https://github.com/hibit-dev/buzzer/tree/master/lib
#include <pitches.h>
#include <millisDelay.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "PlayBuzzer.h"
#include "TimerDisplay.h"
#include "PushButton.h"

#define TIMER_INTERVAL_MS    2000
static const int Timers[] = {60, 180, 300, 600, 1800, 3000, 3600};
static const int TimersSize = 7;

int pinBUZZER = 9;
int pinMuteButton = 4;
int pinTimerSetButton = 5;
int pinStartButton = 6;

// function prototypes
void muteBtnHandler();
void timerSetBtnHandler();
void startBtnHandler();
// end function prototypes

PlayBuzzer buzzer(pinBUZZER);
PushButton muteBtn(pinMuteButton, muteBtnHandler);
PushButton timerBtn(pinTimerSetButton, timerSetBtnHandler);
PushButton startBtn(pinStartButton, startBtnHandler);

// setting data
int settingTimeIdx = 0;
int settingTime = Timers[settingTimeIdx];
int current = settingTime;

// state data
bool isRunning = false;


void setup() {
  Serial.begin(9600);
  Serial.println("Rummikub Timer");

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  // draw init screen
  drawTimerScreen(settingTime, current, !buzzer.isMute());
}

void loop() {
  static uint32_t lastTime = 0;
  static uint32_t currTime;

  muteBtn.checkIfPushed();
  timerBtn.checkIfPushed();
  startBtn.checkIfPushed();

  currTime = millis();
  if (currTime - lastTime > TIMER_INTERVAL_MS) {
    lastTime = currTime;

    if (isRunning) {
      if (current >= 0) {
        drawTimerScreen(settingTime, current, !buzzer.isMute());
        Serial.print("rest time: "); Serial.println(current);

        // play buzzer
        if (current == 0) {
          buzzer.playTone(NOTE_B5, 2000);
        } else if (current < 10) {
          buzzer.playTone(NOTE_B4, 600);
        } else if (current < 20) {
          buzzer.playTone(NOTE_A3, 200);
        }

        current--;
      } else {
        // stop && reset
        isRunning = false;
        current = settingTime;
        drawTimerScreen(settingTime, current, !buzzer.isMute());
      }
    }
  }

  buzzer.loop();

  delay(5);
}

void muteBtnHandler() {
  buzzer.setMute(!buzzer.isMute());

  // redraw screen
  drawTimerScreen(settingTime, current, !buzzer.isMute());
  Serial.print("Mute Button Pushed => "); Serial.println(buzzer.isMute());
}

void timerSetBtnHandler() {
  if (isRunning) {
    Serial.println(F("Timer Set Button Pushed. But isRunning"));
    return;
  }

  settingTimeIdx++;
  if (settingTimeIdx >= TimersSize) {
    settingTimeIdx = 0;
  }
  settingTime = Timers[settingTimeIdx];
  current = settingTime;

  // redraw screen
  drawTimerScreen(settingTime, current, !buzzer.isMute());

  Serial.print("Timer Set Button Pushed =>"); Serial.println(settingTime);
}

void startBtnHandler() {
  Serial.println("Start Button Pushed");

  buzzer.stop();
  isRunning = true;
  current = settingTime;

  // redraw screen
  drawTimerScreen(settingTime, current, !buzzer.isMute());
}
