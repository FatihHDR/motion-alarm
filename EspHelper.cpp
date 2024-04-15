#include "Arduino.h"
#include "EspHelper.h"

EspHelper::EspHelper (int RX, int TX, String SSID, String PASSWORD, bool DEBUG) {
  espSerial = new SoftwareSerial(RX, TX);
  espSerial->begin(9600);
  _RX = RX;
  _TX = TX;
  _SSID = SSID;
  _PASSWORD = PASSWORD;
  _DEBUG = DEBUG;
}

void EspHelper::makeConnection() {
  String ipAddress = sendData("AT+CIFSR\r\n", 5000);
  if (ipAddress.indexOf("0.0.0.0") == -1) {
    serialPrint("ESP is already connected.");
    sendData("AT+CIFSR\r\n", 2000);
  }
  else {
    serialPrint("ESP is not connected; making connection.");
    sendData("AT+RST\r\n", 5000);
    sendData("AT+CWMODE=1\r\n", 2000);
    String creds = "AT+CWJAP=\"" +_SSID + "\",\"" + _PASSWORD + "\"\r\n";
    sendData(creds, 10000);
    sendData("AT+CIFSR\r\n", 2000);
  }
}

String EspHelper::sendData(String command, int timeout) {
  String response = "";
  espSerial->print(command);
  long int time = millis();
  while((time + timeout) > millis()) {
    while(espSerial->available()) {
      char c = espSerial->read();
      response += c;
    }  
  }
  serialPrint(response);
  return response;
}

void EspHelper::motionDetected() {
  sendData("AT+CIPSTART=\"TCP\",\"sjjapps.com\",80\r\n", 2000);
  String request = "GET http://www.sjjapps.com/house-control/path-checker\r\n";
  String cipSend = "AT+CIPSEND=";
  cipSend += request.length() - 1;
  sendData(cipSend += "\r\n", 2000);
  sendData(request, 5000);
}

void EspHelper::sendAtCommand(String command) {
  espSerial->println(command);
}

void EspHelper::logOutput() {
  if(_DEBUG && espSerial->available()) {
    while(espSerial->available()) {
      char c = espSerial->read();
      Serial.write(c);
    }  
  }
}

void EspHelper::serialPrint(String data) {
  if (_DEBUG) Serial.println(data);
}
