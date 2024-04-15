#include <SoftwareSerial.h>

const int READY_LED = 5;
const int RX_PIR = 8;
const int RX_BLUE = 3;
const int TX_BLUE = 4;

boolean motionTransmitInProgress = false;
long motionTimeSent;
boolean isWaiting = false;
long waitingTime;

SoftwareSerial blSerial(RX_BLUE, TX_BLUE);

void setup() {
  Serial.begin(9600);

  pinMode(READY_LED, OUTPUT);
  pinMode(RX_PIR, INPUT);
  blSerial.begin(9600);

  digitalWrite(READY_LED, HIGH);
  Serial.print("calibrating PIR sensor");
  for (int i = 0; i < 15; i++) {
    Serial.print('.');
    delay(1000);
  }
  digitalWrite(READY_LED, LOW);
  Serial.println("\nPIR sensor ready");
  delay(50);
}


void loop() {
  if (!motionTransmitInProgress && !isWaiting && digitalRead(RX_PIR) == HIGH) {
    Serial.println("motion detected");
    motionTransmitInProgress = true;
    blSerial.print('m');
    motionTimeSent = millis();
    delay(50);
  }
  
  if (motionTransmitInProgress) {
    if (millis() - motionTimeSent >= 5000) {
      Serial.println("no response; resending data");
      blSerial.print('m');
      motionTimeSent = millis();
      delay(50);
    }
    else if (blSerial.available()) {
      if (blSerial.read() == 'm') {
        Serial.println("motion was received; continue normally");
        motionTransmitInProgress = false;
        delay(5000);
      }
      delay(50);
    }
  }
  
  if (!motionTransmitInProgress) {
    if (blSerial.available()) {
      if (blSerial.read() == 'w') {
        blSerial.print('w');
        isWaiting = true;
        waitingTime = millis();
        delay(50);
      }
    }
  }
  
  if (isWaiting && millis() - waitingTime >= 60000) {
    isWaiting = false;
  }
  
}
