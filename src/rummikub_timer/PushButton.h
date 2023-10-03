#ifndef PushButton_h
#define PushButton_h

typedef void (*pushBtn_handler)();

class PushButton {
  private:
    int _pin;
    bool _isPushed;
    void *_handler;       // pointer to the handler function

  public:
    PushButton(int pin, pushBtn_handler handler) {
      _pin = pin;
      _isPushed = false;
      _handler = handler;

      pinMode(pin, INPUT);
    }

    void checkIfPushed() {
      if (digitalRead(_pin) == HIGH) {
        if (!_isPushed) {
          _isPushed = true;
        }
      } else if(_isPushed) {
        Serial.print(F("Release BTN: ")); Serial.println(_pin);
        (*(pushBtn_handler)_handler)();

        _isPushed = false;
      }
    }

    bool isPushed() {
      return _isPushed;
    }
};

#endif
