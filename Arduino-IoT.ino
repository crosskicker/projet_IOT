#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <coap-simple.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "GY521.h"

// Connection du WiFi
const char* ssid = "iPhone de Raphael";
const char* password = "123soleil";

// Definition de CoAP
int localUdpPort = 5683;
WiFiUDP Udp;
Coap coap(Udp);

// Definition de MAX30105
MAX30105 particleSensor;
const byte RATE_SIZE = 6;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;

// Definition de GY521
GY521 gy521Sensor(0x68);

// Definition des seuils
const int HEART_RATE_THRESHOLD = 70; // BPM
const float FALL_THRESHOLD = 120.0;   // Angle de chute
bool MESSAGE_SEND_1 = true;
bool MESSAGE_SEND_2 = true;

void COAPResponse(CoapPacket &packet, IPAddress ip, int port) {
  Serial.println("Réponse reçue !");
  Serial.print("De : ");
  Serial.println(ip);
  Serial.print("Port : ");
  Serial.println(port);
  Serial.print("Contenu : ");
  Serial.write(packet.payload, packet.payloadlen);
  Serial.println();
  Serial.println(packet.code);
  Serial.println("------------------------------------------------------------");
}

void initializeMAX30105() {
  Serial.println("Initializing MAX30105...");
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 not found. Check wiring.");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

void initializeGY521() {
  Serial.println("Initializing GY521...");
  while (!gy521Sensor.wakeup()) {
    Serial.println("GY521 not connected. Check address.");
    delay(1000);
  }
  gy521Sensor.setAccelSensitivity(2);
  gy521Sensor.setGyroSensitivity(1);
  gy521Sensor.setThrottle();
}

void readHeartRate() {
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue)) {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  if (beatAvg < (HEART_RATE_THRESHOLD -10)) {
    MESSAGE_SEND_1 = true;
  }

  if (((beatAvg > HEART_RATE_THRESHOLD) || (HEART_RATE_THRESHOLD < 5 && irValue > 50000)) && MESSAGE_SEND_1) {
    Serial.println("Heart rate too high! Sending alert...");
    IPAddress serverIP(172, 20, 10, 4);
    coap.put(serverIP, 5683, "urgence", "High heart rate detected!");
    MESSAGE_SEND_1 = false;
  }
}

void readGY521() {
  gy521Sensor.read();
  float x = gy521Sensor.getAngleX();
  float y = gy521Sensor.getAngleY();
  float z = gy521Sensor.getAngleZ();

  float tiltMagnitude = sqrt(x * x + y * y + z * z);

  if (tiltMagnitude < (FALL_THRESHOLD -30)) {
    MESSAGE_SEND_2 = true;
  }

  if (tiltMagnitude > FALL_THRESHOLD && MESSAGE_SEND_2) {
    Serial.println("Fall detected! Sending alert...");
    IPAddress serverIP(172, 20, 10, 4);
    coap.put(serverIP, 5683, "urgence", "Fall detected!");
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);

  // Initialisation du WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialisation d'UDP et CoAP
  Udp.begin(localUdpPort);
  Serial.printf("UDP started on port %d\n", localUdpPort);
  coap.response(COAPResponse);
  coap.start();

  // Initialisation des sensors
  initializeMAX30105();
  initializeGY521();
  Serial.println("Sensors initialized.");
}

void loop() {
  Serial.println("\nReading sensors...");
  readHeartRate();
  readGY521();
  coap.loop();
}
