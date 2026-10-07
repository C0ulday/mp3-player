#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>


HardwareSerial MP3Serial(1);
DFRobotDFPlayerMini player;

// UART CONNECTIONS
const int RX_PIN = 21;
const int TX_PIN = 20;

// BUTTONS CONNECTIONS
const int PREV_PIN = 0; // left
const int PLAY_PIN = 1; // center 
const int NEXT_PIN = 2; // right

// INFOS VARIABLES
static uint8_t volume = 20; // 0 to 30
uint8_t folders = 3; // numbers of folders
uint8_t files = 20; // files per folders
uint32_t track = 1; // actual track

// BATTERY VARIABLES
unsigned long battery = 0;

unsigned long lastTime = 0;
const uint16_t  BOUNCED_LIMIT = 300;


void setup() {

  Serial.begin(115200);
  pinMode(PREV_PIN,INPUT_PULLUP);
  pinMode(PLAY_PIN,INPUT_PULLUP);
  pinMode(NEXT_PIN,INPUT_PULLUP);

  MP3Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("Initializing DFPlayer Mini...");
  delay(1000);
  if (!player.begin(MP3Serial,false,true)) { // to avoid error message because of 
    // not ACK from the DFplayer
    Serial.println("Unable to initialize DFPlayer Mini.");
    Serial.println("Check wiring, power and TF card.");
    while(1){
      delay(1000); // stay there until it's initialized
    }
  }

  Serial.println("DFPlayer Mini initialized.");
  
  player.volume(volume); // default volume
}

void loop() {



  if (digitalRead(PLAY_PIN) == LOW){
      player.play(1);
      Serial.println("PLAY\n");
  } 
  if (digitalRead(PREV_PIN) == LOW) {
      player.play(2);
      Serial.println("PREV\n");
  }
  if (digitalRead(NEXT_PIN) == LOW) {
      player.play(3);
      Serial.println("NEXT\n");
  }
 

}
