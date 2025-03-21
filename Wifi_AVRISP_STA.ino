#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266AVRISP.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#ifndef STASSID
#define STASSID 
#define STAPSK  
#endif

const char* host = "esp8266-avrisp";
const char* ssid = STASSID;
const char* pass = STAPSK;
const uint16_t port = 328;
const uint8_t reset_pin = 5;

ESP8266AVRISP avrprog(port, reset_pin);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Arduino AVR-ISP over TCP");
  avrprog.setReset(false); 

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    Serial.println("WiFi failed, retrying.");
  }

  MDNS.begin(host);
  MDNS.addService("avrisp", "tcp", port);

  IPAddress local_ip = WiFi.localIP();
  Serial.print("IP address: ");
  Serial.println(local_ip);
  Serial.println("Use your avrdude:");
  Serial.print("avrdude -c arduino -p <device> -P net:");
  Serial.print(local_ip);
  Serial.print(":");
  Serial.print(port);
  Serial.println(" -t # or -U ...");

  avrprog.begin();
}

void loop() {
  static AVRISPState_t last_state = AVRISP_STATE_IDLE;
  AVRISPState_t new_state = avrprog.update();
  if (last_state != new_state) {
    switch (new_state) {
      case AVRISP_STATE_IDLE: {
          Serial.printf("[AVRISP] now idle\r\n");
          break;
        }
      case AVRISP_STATE_PENDING: {
          Serial.printf("[AVRISP] connection pending\r\n");
          break;
        }
      case AVRISP_STATE_ACTIVE: {
          Serial.printf("[AVRISP] programming mode\r\n");
          break;
        }
    }
    last_state = new_state;
  }
  if (last_state != AVRISP_STATE_IDLE) {
    avrprog.serve();
  }

  if (WiFi.status() == WL_CONNECTED) {
    MDNS.update();
  }
}
