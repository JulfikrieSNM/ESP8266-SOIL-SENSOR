#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram Bot credentials
const char* botToken = "YOUR_TELEGRAM_BOT_TOKEN";
const int chat_id = "YOUR_CHAT_ID";   // Example: 123456789

WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

int sensorPin = A0;  // Soil sensor AO connected to A0
int sensorValue = 0;
int dryThreshold = 700;  // Adjust this after calibration

unsigned long lastCheck = 0;
const long interval = 10000; // check every 10 seconds

void setup() {
  Serial.begin(115200);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  
  client.setInsecure(); // For Telegram SSL
}

void loop() {
  unsigned long now = millis();
  if (now - lastCheck > interval) {
    lastCheck = now;

    sensorValue = analogRead(sensorPin);
    Serial.print("Soil Moisture Value: ");
    Serial.println(sensorValue);

    if(sensorValue > dryThreshold) {
      Serial.println("Soil is Dry → Sending Alert...");
      bot.sendMessage(String(chat_id), "⚠️ Soil is too dry! Please water the plant 🌱", "");
    } else {
      Serial.println("Soil moisture is OK");
    }
  }
}
