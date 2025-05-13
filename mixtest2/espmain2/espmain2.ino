#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include <ldr.h>
#include <servoldr.h>

// Ganti dengan WiFi kamu
const char* ssid = "NEAREST";
const char* password = "43211234";

// Ganti dengan info HiveMQ Cloud kamu
const char* mqtt_server = "9047b9234db74c92a7ee4d80b630fe62.s1.eu.hivemq.cloud"; // HOST dari HiveMQ Cloud
const int mqtt_port = 8883; // Port TLS
const char* mqtt_user = "Zero0"; // dari Access Management
const char* mqtt_pass = "OneOne11";

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

  wifiClient.setInsecure(); // NON-production use! Untuk menghindari sertifikat SSL
  client.setServer(mqtt_server, mqtt_port);
  setupLDR();
  setupServo();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  /*/ Kirim data counter setiap 5 detik
  String data = String(counter++);
  client.publish("esp32/uji", data.c_str());
  Serial.print("Dikirim: ");
  Serial.println(data);

  delay(5000); // delay 5 detik
  */

  int ldr = readLDR();
  kontrolServo(ldr);
  int PercLDR = round(100.0 - ((ldr / 1023.0) * 100.0));
  String payload = String(PercLDR) + " %";
  client.publish("esp32/ldr", payload.c_str());

  Serial.print("LDR: ");
  Serial.println(payload);


  delay(5000);
}
