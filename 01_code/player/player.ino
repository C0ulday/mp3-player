#include "SoftwareSerial.h"
#include "DFPlayer_MiniMMp3.h"

HardwareSerial mySerial(1);  // use UART1
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, 20, 21);  // RX = 20, TX = 21 on ESP 32 mini C3

  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("DFPlayer Mini not detected!");
    while(1);
  } else {

    Serial.println("DFPlayer Mini ready!");
    myDFPlayer.volume(25);  // Volume level (0-30)
    Serial.println("Playing File 001.mp3");
    myDFPlayer.play(1);  // Play first track (0001.mp3)

  }

}

void loop() {
  // Nothing in loop
}