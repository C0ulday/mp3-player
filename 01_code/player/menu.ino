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


void drawScreen_1(void) {
   
}

void drawTrackMenu(){
  static const unsigned char image_arrow_diagonal_left_down_bits[] U8X8_PROGMEM = {0x10,0x09,0x05,0x03,0x0f};
  static const unsigned char image_music_next_bits[] U8X8_PROGMEM = {0x00,0x00,0x07,0xf0,0x09,0x90,0x31,0x90,0x41,0x90,0x81,0x91,0x01,0x92,0x01,0x9c,0x01,0x9c,0x01,0x92,0x81,0x91,0x41,0x90,0x31,0x90,0x09,0x90,0x07,0xf0,0x00,0x00};
  static const unsigned char image_music_previous_bits[] U8X8_PROGMEM = {0x00,0x00,0x0f,0xe0,0x09,0x90,0x09,0x8c,0x09,0x82,0x89,0x81,0x49,0x80,0x39,0x80,0x39,0x80,0x49,0x80,0x89,0x81,0x09,0x82,0x09,0x8c,0x09,0x90,0x0f,0xe0,0x00,0x00};
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  u8g2.setFont(u8g2_font_profont12_tr);

    // arrow_diagonal_left_down
  u8g2.drawXBMP(3, 24, 5, 5, image_arrow_diagonal_left_down_bits);
    // ellipse 11
    u8g2.drawEllipse(64, 11, 5, 5);
    
    
    // music_next
  u8g2.drawXBMP(80, 4, 16, 16, image_music_next_bits);
    // music_previous
  u8g2.drawXBMP(33, 4, 16, 16, image_music_previous_bits);

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

void drawVolumeMenu() {
    static const unsigned char image_arrow_diagonal_left_down_bits[] U8X8_PROGMEM = {0x10,0x09,0x05,0x03,0x0f};
    static const unsigned char image_SmallArrowDown_bits[] U8X8_PROGMEM = {0x1f,0x0e,0x04};
    static const unsigned char image_SmallArrowUp_bits[] U8X8_PROGMEM = {0x04,0x0e,0x1f};


    u8g2.setFontMode(1);
    u8g2.setBitmapMode(1);
    
    char buffer[3];
    sprintf(buffer,"%d",volume);
    u8g2.setFont(u8g2_font_6x10_tr);
    if (buffer[2] == '\0') {
      u8g2.drawStr(59, 20, buffer);
    } else {
      u8g2.drawStr(62, 20, buffer);
      
    }
    
    // SmallArrowUp
    u8g2.drawXBMP(62, 8, 5, 3, image_SmallArrowUp_bits);
    // SmallArrowDown
    u8g2.drawXBMP(62, 23, 5, 3, image_SmallArrowDown_bits);
    // arrow_diagonal_left_down
    u8g2.drawXBMP(3, 24, 5, 5, image_arrow_diagonal_left_down_bits);
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

// ==================== MENUS MANAGEMENT ====================

void manageMenu(){

  unsigned long now = millis();
  int dir = 0;

  if (now - lastPress < DEBOUNCE_MS) return;


  u8g2.clearBuffer();

  drawMenu();       
  
  if (digitalRead(PREV_PIN) == LOW) {
    lastPress = now;
    Serial.println("press gauche"); 
    dir--;
  }
  else if (digitalRead(NEXT_PIN) == LOW) {
    lastPress = now;
    Serial.println("press droite");
    dir++;
  }
  selection = (selection + dir + 3) % 3;

  if (digitalRead(PLAY_PIN) == LOW) {
    lastPress = now;
    Serial.println("press centre");
    inMenu = false;
  }

    switch (selection) {
      case 0:
        u8g2.setDrawColor(2);
        u8g2.drawBox(14 - 2, 8 - 2, 20, 20);
        break;
      case 1:
        u8g2.setDrawColor(2);
        u8g2.drawBox(57 - 2, 8 - 2, 20, 20);
        break;
      case 2:
        u8g2.setDrawColor(2);
        u8g2.drawBox(100 - 2, 8 - 2, 20, 20);
        break;

    }  

  

  u8g2.sendBuffer();
}

void manageVolumeMenu(){

  u8g2.clearBuffer();
  drawVolumeMenu();              

  unsigned long now = millis();
  int dir = 0;

  if (now - lastPress < DEBOUNCE_MS) return;

  if (digitalRead(PLAY_PIN) == LOW) {
    lastPress = now;
    Serial.println("press gauche");
    u8g2.setDrawColor(2);
    u8g2.drawBox(60, 22, 9, 5);
    
    dir--;
  }
  else if (digitalRead(NEXT_PIN) == LOW) {
    lastPress = now;
    Serial.println("press droite");
    u8g2.setDrawColor(2);
    u8g2.drawBox(60, 7, 9, 5);
    dir++;
  }

  volume = (volume + dir + 30) % 30;

  if (digitalRead(PREV_PIN) == LOW) {
    lastPress = now;
    Serial.println("retour");
    u8g2.setDrawColor(2);
    u8g2.drawBox(2, 23, 7, 7);
    inMenu = true;
  }
  u8g2.sendBuffer();
}

void manageTrackMenu(){

  u8g2.clearBuffer();

  drawTrackMenu();

  unsigned long now = millis();
  int dir = 0;

  if (digitalRead(PLAY_PIN) == LOW && now - lastPress > DEBOUNCE_MS) {
    lastPress = now;
    Serial.println("press centre");
    u8g2.drawFilledEllipse(64, 11, 5, 5); 
    isPlaying = !isPlaying;
  }

  else if (digitalRead(NEXT_PIN) == LOW) {

    Serial.println("press droite");
    u8g2.setDrawColor(2);
    u8g2.drawBox(79, 4, 18, 16);
    dir++;

    if ( now - lastPress > DEBOUNCE_MS + 100 ) {
      currentFolder++;

    lastPress = now;
    }
    
  }

  else if (digitalRead(PREV_PIN) == LOW) {

    Serial.println("press gauche");
    u8g2.setDrawColor(2);
    u8g2.drawBox(32, 4, 18, 16);
    dir--;

    if ( now - lastPress > DEBOUNCE_MS + 100 ) {
      currentFolder--;
    }
    
    lastPress = now;
    
  }

  currentTrack = (currentTrack + dir + tracks) % tracks + 1;

  if (currentFolder > folders) {
    currentFolder = 1;
  }
  if (currentFolder < 1) {
    currentFolder = folders;
  }

  if (isPlaying) {
    player.playFolder(currentFolder, currentTrack);
  } else { 
    player.pause();
  }

  u8g2.sendBuffer();
}

void manageBLEMenu(){
  return;
}

// ==================== AFFICHAGE ====================

void updateScreen() {

  if (inMenu) {
    manageMenu();
    return;
  }

  switch (selection){

    case 0:
      manageVolumeMenu();
      break;
    case 1:
    manageTrackMenu();
      break;
    case 2:
      manageBLEMenu();
      break;

  }
}
