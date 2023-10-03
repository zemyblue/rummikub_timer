#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// speaker image 16x16 (real size 10x10)
static const unsigned char PROGMEM speaker_image[] = 
{
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b01000000,
  0b00000001, 0b01100000,
  0b00000011, 0b00110000,
  0b00011111, 0b00011000,
  0b00011111, 0b01011000,
  0b00011111, 0b01011000,
  0b00011111, 0b00011000,
  0b00000011, 0b00110000,
  0b00000001, 0b01100000,
  0b00000000, 0b01000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
  0b00000000, 0b00000000,
};

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void drawTime(int x, int y, int cur) {
  char buffer[6];
  sprintf(buffer, "%02d:%02d", cur / 60, cur % 60);
  // display.drawRect(x, y, 117, 29, WHITE);  // frame
  display.setTextSize(4);
  display.setTextColor(WHITE);
  display.setCursor(x, y);

  // Display time
  display.println(buffer);
}

// draw setting time "%d min"
void drawSettingTime(int x, int y, int setTime) {
  const static int SetTimeW = 36;
  int16_t x1, y1;
  uint16_t w, h;
  char buffer[8];
  snprintf(buffer, 7, "%d min", setTime / 60);
  // sprintf(buffer, "%d min", setTime/60);
  // Serial.print("settime: "); Serial.println(buffer);
  // display.drawRect(x, y, SetTimeW, 8, WHITE);  // frame

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.getTextBounds(buffer, x, y, &x1, &y1, &w, &h);
  display.setCursor(x + (SetTimeW - w), y);

  // Display time
  display.print(buffer);
}

// draw timerbar. default w and h is 116, 10.
// percent should be between 0 and 1.
void drawTimerbar(int x, int y, float percent) {
  const static int timerbarW = 116;
  const static int timerbarH = 10;
  display.drawRect(x, y, timerbarW, timerbarH, WHITE);
  int w = int((timerbarW - 2) * percent);
  // Serial.print("percent: "); Serial.println(percent);
  // Serial.print("width: "); Serial.println(w);
  display.fillRect(x + (timerbarW - w), y + 1, w, timerbarH - 2, WHITE);
}

// display sound setting
void drawSoundSetting(int x, int y, bool enable) {
  // display.drawRect(x, y, 12, 12, WHITE);
  display.drawBitmap(x - 3, y - 3, speaker_image, 16, 16, 1);
  if (!enable) {
    display.drawLine(x, y, x + 10, y + 10, WHITE);
    display.drawLine(x + 1, y, x + 11, y + 10, WHITE);
  }
}

// draw full timer screen (128x64)
void drawTimerScreen(int setting, int cur, bool sound) {
  display.clearDisplay();

  drawSettingTime(0, 0, setting);
  drawSoundSetting(110, 0, sound);
  drawTimerbar(6, 15, (float)cur / setting);
  drawTime(6, 32, cur);

  display.display();
}