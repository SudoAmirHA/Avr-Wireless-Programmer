#include <SPI.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <ESP8266AVRISP.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* host = "esp8266-avrisp";
const char* ssid = "Esp-Prog";
const char* password = "amir";
const uint16_t port = 328;
const uint8_t reset_pin = 5;

ESP8266AVRISP avrprog(port, reset_pin);

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("");
  Serial.println("Arduino AVR-ISP over TCP");
  avrprog.setReset(false); 

  MDNS.begin(host);
  MDNS.addService("avrisp", "tcp", port);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  Serial.println(WiFi.localIP());
  Serial.println("Use your avrdude:");
  Serial.print("avrdude -c arduino -p <device> -P net:");
  Serial.print(IP);
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
