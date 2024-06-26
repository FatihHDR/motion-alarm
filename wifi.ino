#include <SoftwareSerial.h>
#include "EspHelper.h"

const boolean DEBUG = false;
const int READY_LED = 13;
const int RX_PIR = 8;

EspHelper esp (2, 3, "WIFI_USERNAME", "WIFI_PASSWORD", DEBUG);

void setup() {
  Serial.begin(9600);
  pinMode(RX_PIR, INPUT);
  pinMode(READY_LED, OUTPUT);
  digitalWrite(READY_LED, HIGH);
  esp.makeConnection();
  digitalWrite(READY_LED, LOW);
  serialPrint("Device ready.");
}

void loop() {
  if(DEBUG && Serial.available()) {
    delay(1000);
    String command="";
    while(Serial.available()) command += (char)Serial.read();
    esp.sendAtCommand(command);
  }
  esp.logOutput();

  if (digitalRead(RX_PIR) == HIGH) {
    serialPrint("Motion detected.");
    digitalWrite(READY_LED, HIGH);
    if (!DEBUG) esp.motionDetected();
    for (int i=0; i<5; i++) delay(1000);
    digitalWrite(READY_LED, LOW);
    serialPrint("Ready for next detection.");
  }  
}

void serialPrint(String data) {
  if (DEBUG) Serial.println(data);
}