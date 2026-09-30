#include <Arduino.h>
#include <WiFi.h>

extern "C" {
  #include "esp_wifi.h"
}

// Alpha Skibidi Names Here Only!!!1
String ssidList[] = {
  "FREE ROBUX TRUST!!!", // 1
  "Nyahhhh", // 2
  "bark bark", // 3
  "grrrrr", // 4
  "meow"  // 5
};
int ssidCount = 5; //-- how many ssid you have yk shit on the top skibidi toilet sigma 100%

int currentChannel = 1;
unsigned long lastPacketTime = 0;
unsigned long lastHopTime = 0;
int currentSsidIdx = 0;
uint8_t myMac[6];

void makeRandomMac() {
  myMac[0] = 0x00;
  for(int i = 1; i < 6; i++) {
    myMac[i] = random(0, 256);
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  
  esp_wifi_set_channel(currentChannel, WIFI_SECOND_CHAN_NONE);
  Serial.println("Nyahhh i am working papi~");
}

void loop() {
  unsigned long now = millis();

  if(now - lastHopTime > 80) {
    lastHopTime = now;
    currentChannel++;
    if(currentChannel > 13) currentChannel = 1;
    esp_wifi_set_channel(currentChannel, WIFI_SECOND_CHAN_NONE);
  }

  if(now - lastPacketTime > 2) {
    lastPacketTime = now;
    
    String targetSsid = ssidList[currentSsidIdx];
    currentSsidIdx = (currentSsidIdx + 1) % ssidCount;

    makeRandomMac();

    uint8_t packet[128];
    int pSize = 0;

    packet[0] = 0x80;
    packet[1] = 0x00;
    packet[2] = 0x00; 
    packet[3] = 0x00;

    for(int i = 0; i < 6; i++) packet[4 + i] = 0xFF;

    for(int i = 0; i < 6; i++) {
      packet[10 + i] = myMac[i];
      packet[16 + i] = myMac[i];
    }

    packet[22] = 0x00; 
    packet[23] = 0x00;

    for(int i = 0; i < 8; i++) packet[24 + i] = 0x00;
    packet[32] = 0x64; 
    packet[33] = 0x00;
    packet[34] = 0x01; 
    packet[35] = 0x00;

    pSize = 36;

    packet[pSize++] = 0x00;
    packet[pSize++] = targetSsid.length();
    for(int i = 0; i < targetSsid.length(); i++) {
      packet[pSize++] = targetSsid[i];
    }

    uint8_t rates[] = {0x01, 0x08, 0x82, 0x84, 0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c};
    for(int i = 0; i < 10; i++) {
      packet[pSize++] = rates[i];
    }

    packet[pSize++] = 0x03;
    packet[pSize++] = 0x01;
    packet[pSize++] = currentChannel;

    esp_wifi_80211_tx(WIFI_IF_STA, packet, pSize, false);
  }
}
