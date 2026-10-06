#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

HardwareSerial MP3Serial(1);
DFRobotDFPlayerMini player;

const int RX_PIN = 21;
const int TX_PIN = 20;

const int PREV_PIN = 0;
const int PLAY_PIN = 1;
const int NEXT_PIN = 2;

bool isPlaying = false;
int lastButtonState = HIGH;


void setup() {

  Serial.begin(115200);
  pinMode(PREV_PIN,INPUT_PULLUP);
  pinMode(PLAY_PIN,INPUT_PULLUP);
  pinMode(NEXT_PIN,INPUT_PULLUP);

  MP3Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);

  Serial.println("Initializing DFPlayer Mini...");
  delay(1000);
  if (!player.begin(MP3Serial,false,true)) {
    Serial.println("Unable to initialize DFPlayer Mini.");
    Serial.println("Check wiring, power and TF card.");
    while(1){
      delay(1000); 
    }
  }

  Serial.println("DFPlayer Mini initialized.");
  
  player.volume(20);
}

void loop() {
  
  int currentButtonState = digitalRead(PREV_PIN);
  if (lastButtonState == HIGH && currentButtonState == LOW){
    if (!isPlaying) {
      player.play(1);
      Serial.print(currentButtonState);
      Serial.print(" ");
      Serial.println("PLAY\n");
      isPlaying = true; 
    } else {
      player.pause();
      Serial.println("PAUSE\n");
      isPlaying = false;
    }
  } 
  lastButtonState = currentButtonState;
  delay(50);
}
