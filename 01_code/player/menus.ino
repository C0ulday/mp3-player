void showMessage(const char* l1) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0, 12, l1);
  u8g2.sendBuffer();
}

void splashScreen() {
  u8g2.clearBuffer();
  u8g2.setFontMode(1);
  u8g2.setBitmapMode(1);

  u8g2.setFont(u8g2_font_5x8_tr);
  u8g2.drawStr(48, 18, "MP3 POD");

  // trois petits points
  u8g2.drawDisc(60, 22, 1);
  u8g2.drawDisc(64, 22, 1);
  u8g2.drawDisc(68, 22, 1);

  u8g2.sendBuffer();
}

void showMenu(){
  showLeftArrow();
  showRightArrow();
}

void showLeftArrow(){
 
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(34, 10, "<");
  u8g2.sendBuffer();    
}

void showRightArrow(){
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(24, 20, ">");
  u8g2.sendBuffer();    
}