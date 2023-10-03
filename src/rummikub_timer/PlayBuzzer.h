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

    void setMute(bool mute);
    bool isMute();

  private:
    int _buzzerPin;
    bool _isPlaying;
    bool _isMute;
    millisDelay _delay;

    void _reset();
};

#endif // PlayBuzzer_h