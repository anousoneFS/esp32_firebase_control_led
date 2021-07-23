// Error compiling for board ESP32 Dev Module. mac do not subport

#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

#define LED_PIN 8

#define FIREBASE_HOST "<Something>.firebaseio.com"
#define FIREBASE_AUTH "<Token or Secret>"
#define WIFI_SSID "<YOU WIFI NAME>"
#define WIFI_PASSWORD "<YOU WIFI PASSWORD>"

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  Serial.begin(115200);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  Serial.println("Start stream led control");
  Firebase.stream("/arduino_streaming", [](FirebaseStream stream) {
    Serial.println("Evant: " + stream.getEvent());
    Serial.println("Path: " + stream.getPath());
    Serial.println("Data: " + stream.getDataString());
    if (stream.getEvent() == "put") {
      if (stream.getPath() == "/") {
        digitalWrite(LED_PIN, stream.getDataInt());
      }
    }
  });
}

void loop() {
  // put your main code here, to run repeatedly:

}
