#ifndef PlayBuzzer_h
#define PlayBuzzer_h

#include <millisDelay.h>

class PlayBuzzer {
  public:
    PlayBuzzer(int pin, int *melody, int melodySize);
    bool play();
    void stop();
    bool isPlaying();

  private:
    int m_buzzerPin;
    bool m_isPlaying;
    int m_noteIdx;
    int m_noteSize;
    int m_duration = 1;
    int m_divider = 0;
    int m_noteDuration = 0;
    millisDelay m_delay;
    int *m_melody;

    void _playTone();
    void _reset();
};

#endif // PlayBuzzer_h