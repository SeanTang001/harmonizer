#include <WiFi.h>

// const char* wifi_ssid = "IEEE";
// const char* wifi_password = "Ilovesolder";

const char* wifi_ssid = "Poopy";
const char* wifi_password = "123456789abcd";


void connectWiFi() {
  // Connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  Serial.println("WiFi: Begin Initialization");
  // Wait some time to connect to wifi
  int wifistatus = WiFi.waitForConnectResult();
  Serial.print("WiFi: State ");
  Serial.println(wifistatus);
  if(wifistatus == WL_CONNECTED) {
    Serial.println("WiFi: Connected!");
  } else {
    Serial.println("WiFi: Connection Attempt Failed, Rebooting in 3 seconds");
    WiFi.disconnect();
    delay(3000);
    ESP.restart();
  }
}

