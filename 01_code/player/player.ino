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

