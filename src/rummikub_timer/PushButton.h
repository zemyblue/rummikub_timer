#ifndef PushButton_h
#define PushButton_h

#define LONGPRESS_TIME 3000

typedef void (*pushBtn_handler)();

class PushButton {
  private:
    int _pin;
    bool _isPushed;
    long _pressTime;
    void *_handler;       // pointer to the handler function
    void *_longPressHandler;

  public:
    PushButton(int pin, pushBtn_handler handler, pushBtn_handler longPressHandler = NULL) {
      _pin = pin;
      _isPushed = false;
      _handler = handler;
      _longPressHandler = longPressHandler;

      pinMode(pin, INPUT);
    }

    void checkIfPushed() {
      if (digitalRead(_pin) == HIGH) {
        if (!_isPushed) {
          _isPushed = true;
          _pressTime = millis();
        }
      } else if(_isPushed) {
        if (millis() - _pressTime >= LONGPRESS_TIME) {
          Serial.print(F("Release(long) BTN: ")); Serial.println(_pin);
          if (_longPressHandler) {
            (*(pushBtn_handler)_longPressHandler)();
          }
        } else {
          Serial.print(F("Release BTN: ")); Serial.println(_pin);
          (*(pushBtn_handler)_handler)();
        }

        _isPushed = false;
      }
    }

    bool isPushed() {
      return _isPushed;
    }
};

#endif
