#include <stdarg.h>



// ==================== SPLASH ====================
void splashScreen() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(48, 18, "MP3 POD");

  // 3 little dots
  u8g2.drawDisc(60, 22, 1);
  u8g2.drawDisc(64, 22, 1);
  u8g2.drawDisc(68, 22, 1);

  u8g2.sendBuffer();
}

// ==================== ICONES ====================
void showMusicBits() {
  static const unsigned char image_music_bits[] U8X8_PROGMEM = {
    0x00,0x3e,0xf0,0x21,0x10,0x20,0x10,0x3e,0xf0,0x23,0x10,0x20,
    0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x20,0x10,0x1c,0x0e,0x22,
    0x11,0x22,0x11,0x1c,0x0e,0x00,0x00,0x00
  };
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP(57, 8, 14, 16, image_music_bits);
}

void showBLEBits() {
  static const unsigned char image_bluetooth_bits[] U8X8_PROGMEM = {
    0x80,0x00,0x40,0x01,0x40,0x02,0x44,0x04,0x48,0x04,0x50,0x02,
    0x60,0x01,0xc0,0x00,0x60,0x01,0x50,0x02,0x48,0x04,0x44,0x04,
    0x40,0x02,0x40,0x01,0x80,0x00,0x00,0x00
  };
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP(100, 8, 14, 16, image_bluetooth_bits);
}

void showVolumeBits() {
  static const unsigned char image_volume_low_bits[] U8X8_PROGMEM = {
    0x80,0x03,0x00,0x40,0x02,0x00,0x20,0x02,0x00,0x10,0x02,0x00,
    0x0f,0x0a,0x00,0x01,0x12,0x00,0x01,0x22,0x00,0x01,0x22,0x00,
    0x01,0x22,0x00,0x01,0x12,0x00,0x0f,0x0a,0x00,0x10,0x02,0x00,
    0x20,0x02,0x00,0x40,0x02,0x00,0x80,0x03,0x00,0x00,0x00,0x00
  };
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  // volume 
  u8g2.drawXBMP(14, 8, 18, 16, image_volume_low_bits);
}

// ==================== SELECTION / FLECHES ====================
void drawRect(int x, int y) {
  u8g2.setDrawColor(2);
  u8g2.drawBox(x - 2, y - 2, 20, 20);
  u8g2.setDrawColor(1);
}

void leftArrow(void) {
  static const unsigned char image_ButtonLeft_bits[] U8X8_PROGMEM = {
    0x08,0x0c,0x0e,0x0f,0x0e,0x0c,0x08
  };
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP(10, 13, 4, 7, image_ButtonLeft_bits);
}

void rightArrow(void) {
  static const unsigned char image_ButtonRight_bits[] U8X8_PROGMEM = {
    0x01,0x03,0x07,0x0f,0x07,0x03,0x01
  };
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);
  u8g2.drawXBMP(114, 13, 4, 7, image_ButtonRight_bits);
}

// ==================== TEXTE (varargs) ====================
void showText(const char* fmt, ...) {
  char buf[32];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);

  u8g2.setFont(u8g2_font_6x10_tr);
  u8g2.drawStr(43, 20, buf);
  u8g2.sendBuffer();
}

// ==================== MENUS ====================
void showVolumeMenu() {
  showText("Volume : %d", volume);
  leftArrow();
  rightArrow();
}

void showTrackMenu() {
  showText("Track : %d", tracks);
  leftArrow();
  rightArrow();
}

void showBLEMenu() {
  showText("connection...");
  leftArrow();
  rightArrow();
}

// ==================== MENU PRINCIPAL ====================
void showMenu() {
  u8g2.clearBuffer();
  showMusicBits();
  showBLEBits();
  showVolumeBits();
  u8g2.sendBuffer();
}

void drawMenu() {
  showMusicBits();
  showBLEBits();
  showVolumeBits();
}

// ==================== INPUT ====================
void updateSelection() {
  unsigned long now = millis();
  if (now - lastPress < DEBOUNCE_MS) return;
  if (digitalRead(PREV_PIN) == LOW) {
    lastPress = now;
    Serial.println("press gauche\n");
    update = true;
  }
  else if (digitalRead(NEXT_PIN) == LOW) {
    lastPress = now;
    Serial.println("press droite\n");
    update = true;
  }
  else if (digitalRead(PLAY_PIN) == LOW) {
    lastPress = now;
    Serial.println("press centre\n");
    update = true;
  }
}



// ==================== AFFICHAGE ====================

void updateScreen() {

  updateSelection();
  
  if (!update) return;
  update = false;
  
    if (inMenu) {
      u8g2.clearBuffer();
      drawMenu();
      if (selection == 1) {
        drawRect(14,8);
      } else if (selection == 2) {
        drawRect(57,8);
       } else {
        drawRect(100,8);
      }
      u8g2.sendBuffer();

    }

  
}