#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <esp_system.h>


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32   

HardwareSerial MP3Serial(1);
DFRobotDFPlayerMini player;


// I2C OLED ESP32-C3 Super Mini
const int SDA_PIN = 8;
const int SCL_PIN = 9;

// UART DFPlayer
const int RX_PIN = 21;
const int TX_PIN = 20;

// Boutons
const int PREV_PIN = 0;
const int PLAY_PIN = 1;
const int NEXT_PIN = 3;   

uint8_t volume = 20;

unsigned long lastPress = 0;
const unsigned long DEBOUNCE_MS = 300;

// -------- OLED setup --------
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);

// -------- Prototypes --------
void drawCatFrame(int hipOffset, bool noteUp);
void playCatIntro();
void drawStar(int cx, int cy, int size);
void drawNote(int x, int y);
void drawNotePair(int x, int y);
void displayMenu();
void displayVolume();

// -------- Setup --------
void setup() {

  Serial.begin(115200);
  delay(1000);
  Serial.printf("Reset reason: %d\n", (int)esp_reset_reason());

  pinMode(PREV_PIN, INPUT_PULLUP);
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(NEXT_PIN, INPUT_PULLUP);


  // DFPlayer
  MP3Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  delay(1000);

  Serial.println("Initializing DFPlayer Mini...");
  if (!player.begin(MP3Serial, false, true)) {
    Serial.println("Unable to initialize DFPlayer Mini.");
    while (true) { delay(1000); }
  }
  Serial.println("DFPlayer Mini initialized.");
  player.volume(volume);

  // Oled 
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x10_tf);
}




// -------- Loop --------
void loop() {
  unsigned long now = millis();

  if (digitalRead(PLAY_PIN) == LOW && now - lastPress > DEBOUNCE_MS) {
    lastPress = now;
    Serial.println("PLAY");
    player.play(1);
  }
  if (digitalRead(PREV_PIN) == LOW && now - lastPress > DEBOUNCE_MS) {
    lastPress = now;
    Serial.println("PREV");
    player.play(2);
  }
  if (digitalRead(NEXT_PIN) == LOW && now - lastPress > DEBOUNCE_MS) {
    lastPress = now;
    Serial.println("NEXT");
    player.play(3);
  }

  u8g2.clearBuffer();
  u8g2.setCursor(0, 12);
  u8g2.printf("t=%lu s", millis() / 1000);
  u8g2.setCursor(0, 26);
  u8g2.printf("reset=%d", (int)esp_reset_reason());
  u8g2.sendBuffer();
  delay(500);
}

// -------- Dessin adapté au 128x32 --------
void drawNote(int x, int y) {
  // Petite note de musique (taille réduite pour 32px de haut)
  oled.drawCircle(x, y + 3, 1, SSD1306_WHITE);
  oled.drawLine(x + 1, y + 3, x + 1, y, SSD1306_WHITE);
  oled.drawLine(x + 1, y, x + 3, y + 1, SSD1306_WHITE);
}

void drawNotePair(int x, int y) {
  drawNote(x, y);
  drawNote(x + 4, y + 1);
}

void drawStar(int cx, int cy, int size) {
  // Étoile compacte
  oled.drawLine(cx, cy - size, cx, cy + size, SSD1306_WHITE);
  oled.drawLine(cx - size, cy, cx + size, cy, SSD1306_WHITE);
  int diag = size / 2;
  oled.drawLine(cx - diag, cy - diag, cx + diag, cy + diag, SSD1306_WHITE);
  oled.drawLine(cx - diag, cy + diag, cx + diag, cy - diag, SSD1306_WHITE);
}

void drawCatFrame(int hipOffset, bool noteUp) {
  oled.clearDisplay();

  int cx = SCREEN_WIDTH / 2;   // 64
  int cy = 10;                 // ← tête placée plus haut (y=10 au lieu de 18)

  // Éléments décoratifs (notes + étoiles)
  int nOffset = noteUp ? 0 : 1;
  drawNote(cx - 45, 2 + nOffset);
  drawNotePair(cx + 25, 0 - nOffset);
  drawNote(cx + 45, 10 + nOffset);
  drawStar(6, 26, 3);
  drawStar(SCREEN_WIDTH - 8, 24, 2);

  // ----- Tête (réduite) -----
  oled.drawCircle(cx, cy, 7, SSD1306_WHITE);   // rayon 7 au lieu de 11

  // Oreilles
  oled.drawTriangle(cx - 6, cy - 5, cx - 8, cy - 12, cx - 2, cy - 7, SSD1306_WHITE);
  oled.drawTriangle(cx + 6, cy - 5, cx + 8, cy - 12, cx + 2, cy - 7, SSD1306_WHITE);

  // Yeux (très simples)
  oled.drawPixel(cx - 3, cy - 2, SSD1306_WHITE);
  oled.drawPixel(cx + 3, cy - 2, SSD1306_WHITE);

  // Nez
  oled.drawPixel(cx, cy + 1, SSD1306_WHITE);

  // Bouche
  oled.drawLine(cx - 2, cy + 3, cx, cy + 2, SSD1306_WHITE);
  oled.drawLine(cx, cy + 2, cx + 2, cy + 3, SSD1306_WHITE);

  // Moustaches
  oled.drawLine(cx - 7, cy + 1, cx - 12, cy, SSD1306_WHITE);
  oled.drawLine(cx - 7, cy + 2, cx - 12, cy + 3, SSD1306_WHITE);
  oled.drawLine(cx + 7, cy + 1, cx + 12, cy, SSD1306_WHITE);
  oled.drawLine(cx + 7, cy + 2, cx + 12, cy + 3, SSD1306_WHITE);

  // ----- Corps (simplifié) -----
  int bx = cx + hipOffset;
  int by = cy + 10;   // juste sous la tête

  oled.drawRoundRect(bx - 6, by, 12, 8, 3, SSD1306_WHITE);

  // Pattes
  oled.fillRoundRect(bx - 5, by + 7, 4, 5, 1, SSD1306_WHITE);
  oled.fillRoundRect(bx + 1, by + 7, 4, 5, 1, SSD1306_WHITE);

  oled.display();
}

void playCatIntro() {
  int offsets[] = {-2, 0, 2, 0};
  bool noteToggle = false;

  for (int cycle = 0; cycle < 3; cycle++) {
    for (int i = 0; i < 4; i++) {
      drawCatFrame(offsets[i], noteToggle);
      noteToggle = !noteToggle;
      delay(250);
    }
  }
  drawCatFrame(0, true);
  delay(500);

  oled.clearDisplay();
  oled.display();
  delay(200);
}

void displayMenu() {
  oled.clearDisplay();
  drawStar(6, 6, 3);
  drawStar(SCREEN_WIDTH - 8, 8, 3);

  oled.setTextSize(1);
  oled.setCursor(20, 4);
  oled.println("Volume");
  oled.setCursor(20, 18);
  oled.println("Play Music");
  oled.display();
}

void displayVolume() {
  oled.clearDisplay();
  oled.setTextSize(2);
  oled.setCursor(50, 8);
  oled.println(volume);
  oled.setTextSize(1);
  oled.setCursor(6, 12);
  oled.println("<");
  oled.display();
}