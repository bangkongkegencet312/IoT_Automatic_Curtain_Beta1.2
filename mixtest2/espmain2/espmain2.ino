#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ldr.h>
#include <servoldr.h>
#include <Arduino.h>
#include "ldr.h"
#include "dht11.h"
#include "servoldr.h"



// Ganti dengan WiFi kamu
const char* ssid = "NEAREST";
const char* password = "43211234";

// Ganti dengan info HiveMQ Cloud kamu
const char* mqtt_server = "9575f087603642b38802e20db41742bf.s1.eu.hivemq.cloud"; // HOST dari HiveMQ Cloud
const int mqtt_port = 8883; // Port TLS
const char* mqtt_user = "Jawa_negri31"; // dari Access Management
const char* mqtt_pass = "Aduhaijomok1";
const char* mqtt_topic = "Tirai_PID_IOT"

WiFiClientSecure wifiClient;
PubSubClient client(wifiClient);

long counter = 0;

void setup_wifi() {
  delay(10);
  Serial.println("Menghubungkan ke WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi terhubung!");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_pass)) {
      Serial.println("Terhubung!");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();

  wifiClient.setInsecure();
  client.setServer(mqtt_server, mqtt_port);
  setupLDR();
  setupDHT();
  setupServo();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  int ldr = readLDR();
  float suhu = readTemperature();

  if (suhu == -999.0) {
    Serial.println("Gagal membaca suhu dari DHT11.");
    delay(2000);
    return;
  }

  int intensitas = round(100.0 - ((ldr / 4095.0) * 100.0)); // 12-bit ADC ESP32

  Serial.print("Suhu: ");
  Serial.print(suhu);
  Serial.print(" °C | Intensitas Cahaya: ");
  Serial.print(intensitas);
  Serial.println(" %");

  kontrolServo(suhu, intensitas);

  String payload = "Suhu: " + String(suhu) + " °C, Intensitas: " + String(intensitas) + " %";
  client.publish("esp32/data", payload.c_str());

  delay(2000);
}
