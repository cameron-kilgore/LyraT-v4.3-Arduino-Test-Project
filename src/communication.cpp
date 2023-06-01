#include "config.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include "config.h"

HTTPClient http;   
WiFiClient client;

void wifiConnection() {
    Serial.begin(115200);
    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    // Print local IP address and start web server
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}