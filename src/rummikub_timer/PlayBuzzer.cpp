#include "Arduino.h"
#include <pitches.h>
#include <millisDelay.h>

#include "PlayBuzzer.h"

PlayBuzzer::PlayBuzzer(int pin) {
  m_buzzerPin = pin;
}

void PlayBuzzer::playTone(int melody, unsigned long duration) {
  tone(m_buzzerPin, melody, duration);
  m_delay.start(duration);
  m_isPlaying = true;
  Serial.print(F("Buzzer play")); Serial.println(melody);
}

void PlayBuzzer::loop() {
  if (m_isPlaying && m_delay.justFinished()) {
    m_delay.stop();
    noTone(m_buzzerPin);
    m_isPlaying = false;
    Serial.println(F("Buzzer end"));
  }
}

bool PlayBuzzer::isPlaying() {
  return m_isPlaying;
}

void PlayBuzzer::stop()
{
  if (m_isPlaying) {
    noTone(m_buzzerPin);
    m_delay.stop();
  }
}
