#include "Arduino.h"
#include <pitches.h>
#include <millisDelay.h>

#include "PlayBuzzer.h"

PlayBuzzer::PlayBuzzer(int pin, int *melody, int melodySize) {
  m_buzzerPin = pin;
  m_melody = melody;
  m_noteSize = melodySize;
}

void PlayBuzzer::_reset() {
  m_noteIdx = 0;
  m_isPlaying = false;
}

bool PlayBuzzer::play()
{
  if (m_delay.justFinished()) {
    // stop the waveform generation before the next note.
    noTone(m_buzzerPin);

    m_noteIdx += 2;
    if (m_noteIdx >= m_noteSize * 2) {
      m_delay.stop();
      _reset();
      Serial.println("Buzzer end");
      return false;
    }

    _playTone();
    Serial.print("Note["); Serial.print(m_noteIdx); Serial.println("] finish");
  }

  if (!m_isPlaying) {
    _playTone();
    Serial.println("start timer buzzer");
    Serial.print("noteSize: "); Serial.println(m_noteSize);

    m_isPlaying = true;
  }

  return true;
}

void PlayBuzzer::_playTone()
{
  // start timer buzzer
  m_divider = m_melody[m_noteIdx + 1];
  m_noteDuration = 20000 / m_divider;

  // play the note for 40% of the duration, leaving 60% as a pause.
  tone(m_buzzerPin, m_melody[m_noteIdx],   m_noteDuration * 0.4);

  // Wait for the specief duration before playing the next note.
  m_delay.start(m_noteDuration);
}

bool PlayBuzzer::isPlaying() {
  return m_isPlaying;
}

void PlayBuzzer::stop()
{
  if (m_isPlaying) {
    noTone(m_buzzerPin);
    m_delay.stop();
    _reset();
  }
}
