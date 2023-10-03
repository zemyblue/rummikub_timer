#include "Arduino.h"
#include <pitches.h>
#include <millisDelay.h>

#include "PlayBuzzer.h"

PlayBuzzer::PlayBuzzer(int pin) {
  _buzzerPin = pin;
}

void PlayBuzzer::playTone(int melody, unsigned long duration) {
  if (_isMute) {
    return;
  }

  tone(_buzzerPin, melody, duration);
  _delay.start(duration);
  _isPlaying = true;
  Serial.print(F("Buzzer play")); Serial.println(melody);
}

void PlayBuzzer::loop() {
  if (!_isMute && _isPlaying && _delay.justFinished()) {
    _reset();
  }
}

bool PlayBuzzer::isPlaying() {
  return _isPlaying;
}

void PlayBuzzer::stop()
{
  if (_isPlaying) {
    noTone(_buzzerPin);
    _delay.stop();
  }
}

void PlayBuzzer::_reset() {
  if (_isPlaying) {
    _delay.stop();
    noTone(_buzzerPin);
    _isPlaying = false;
    Serial.println(F("Buzzer end"));
  }
}

void PlayBuzzer::setMute(bool mute) {
  _isMute = mute;

  if (mute) {
    _reset();
  }
}

bool PlayBuzzer::isMute() {
  return _isMute;
}
