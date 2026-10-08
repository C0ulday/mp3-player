#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <esp_system.h>

// ==================== PROTOTYPES ====================
void splashScreen();
void showMusicBits();
void showBLEBits();
void showVolumeBits();
void showRectSelectMenu(int x, int y);
void showText(const char* fmt, ...);
void leftArrow(void);
void rightArrow(void);
void showVolumeMenu();
void showTrackMenu();
void showBLEMenu();
void showMenu();
void updateSelection();
void updateScreen();

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
uint8_t tracks = 0;

bool inMenu =  true;
bool update = false;
int selection = 2;

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
  showText("Demarrage...");

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
    showText("DFPlayer OK");
  } else {
    showText("DFPlayer ERREUR");
  }
  delay(1500);
  splashScreen();

}

void loop() {

  showMenu();
  updateSelection();

  delay(50);


}