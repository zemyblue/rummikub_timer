// reference: https://github.com/hibit-dev/buzzer/tree/master/lib
#include <pitches.h>
#include <millisDelay.h>
#include "PlayBuzzer.h"

int buzzer = 9;

int timer_melody[] = {
  NOTE_F4,10,
  NOTE_F4,10,
  NOTE_F4,10,
  NOTE_B5,5
};

// about buzzer codes
// int duration = 1;
// int divider = 0, noteDuration = 0;

// millisDelay buzzerDelay;
// bool buzzerOn = false;
// int buzzerNote = 0;
// int notes = sizeof(timer_melody) / sizeof(int) / 2;

// void playTone() {
//   // start timer buzzer
//   divider = timer_melody[buzzerNote + 1];
//   noteDuration = 20000 / divider;

//   // play the note for 40% of the duration, leaving 60% as a pause.
//   tone(buzzer, timer_melody[buzzerNote], noteDuration * 0.4);

//   // Wait for the specief duration before playing the next note.
//   buzzerDelay.start(noteDuration);
// }

// bool runTimerBuzzer() {
//   if (buzzerDelay.justFinished()) {
//     // stop the waveform generation before the next note.
//     noTone(buzzer);

//     buzzerNote += 2;
//     if (buzzerNote >= notes * 2) {
//       buzzerDelay.stop();
//       buzzerNote = 0;
//       buzzerOn = false;
//       Serial.println("Buzzer end");
//       return false;
//     }

//     playTone();
//     Serial.print("Note["); Serial.print(buzzerNote); Serial.println("] finish");
//   }
  
//   if (!buzzerOn) {
//     playTone();
//     Serial.println("start timer buzzer");

//     buzzerOn = true;
//   }

//   return true;
// }

PlayBuzzer timerBuzzer(buzzer, timer_melody, sizeof(timer_melody) / sizeof(int) / 2);


void setup() {
  Serial.begin(9600);
  Serial.println("buzzer test");

  // int notes = sizeof(timer_melody) / sizeof(int) / 2;
  // for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
  //   divider = timer_melody[thisNote + 1];
  //   noteDuration = 20000 / divider;

  //   Serial.println(noteDuration);
  //   tone(buzzer, timer_melody[thisNote], noteDuration * 0.4);

  //   delay(noteDuration);

  //   noTone(buzzer);
  // }

  // Serial.println("END");
}

bool isPlaying = true;
void loop() {
  if (isPlaying) {
    // if (!runTimerBuzzer()) {
    if (!timerBuzzer.play()) {
      isPlaying = false;
    }
  }
}
