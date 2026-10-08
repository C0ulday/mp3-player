#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <esp_system.h>

HardwareSerial MP3Serial(1);
DFRobotDFPlayerMini player;

const int SDA_PIN = 4;
const int SCL_PIN = 5;
const int RX_PIN = 21;   
const int TX_PIN = 20;   

const int PREV_PIN = 0;
const int PLAY_PIN = 1;
const int NEXT_PIN = 3;

uint8_t volume = 20;
unsigned long lastPress = 0;
const unsigned long DEBOUNCE_MS = 300;

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE, SCL_PIN, SDA_PIN);



void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.printf("Reset reason: %d\n", (int)esp_reset_reason());

  pinMode(PREV_PIN, INPUT_PULLUP);
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(NEXT_PIN, INPUT_PULLUP);

  // OLED init
  u8g2.begin();
  showMessage("Demarrage...");

  // DFPLAYER init
  delay(1500);   // time for the dfplayer to start
  MP3Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  bool ok = false;
  for (int i = 0; i < 3 && !ok; i++) {
    ok = player.begin(MP3Serial, false, true);
    if (!ok) delay(500);
  }

  if (ok) {
    player.volume(volume);
    showMessage("DFPlayer OK");
  } else {
    showMessage("DFPlayer ERREUR");
  }
  delay(1500);
  splashScreen();

}

void loop() {


  showMenu();



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
  delay(50);


}