#ifndef PlayBuzzer_h
#define PlayBuzzer_h

#include <millisDelay.h>

class PlayBuzzer {
  public:
    PlayBuzzer(int pin);
    void playTone(int melody, unsigned long duration);
    void loop();

    void stop();
    bool isPlaying();

  private:
    int m_buzzerPin;
    bool m_isPlaying;
    millisDelay m_delay;
};

#endif // PlayBuzzer_h