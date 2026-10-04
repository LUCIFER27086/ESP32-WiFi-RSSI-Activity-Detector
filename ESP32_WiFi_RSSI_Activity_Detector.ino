#include <WiFi.h>

// Threshold for considering an RSSI change significant.
// RSSI is noisy, so this value should be tuned experimentally.
const int RSSI_CHANGE_THRESHOLD = 4;

// Time between activity checks.
const unsigned long CHECK_INTERVAL_MS = 2000;

// Time to wait after an activity event before reporting another one.
const unsigned long COOLDOWN_MS = 5000;

int previousRssi = 0;
unsigned long lastCheckTime = 0;
unsigned long lastActivityTime = 0;

bool havePreviousReading = false;

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println();
  Serial.println("ESP32 Wi-Fi RSSI Activity Detection Experiment");
  Serial.println("==============================================");
  Serial.println("This is an experiment using RSSI changes as");
  Serial.println("an indicator of nearby wireless activity.");
  Serial.println();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastCheckTime < CHECK_INTERVAL_MS) {
    return;
  }

  lastCheckTime = currentTime;

  int networkCount = WiFi.scanNetworks();

  if (networkCount <= 0) {
    Serial.println("No Wi-Fi networks detected.");
    WiFi.scanDelete();
    return;
  }

  // Find the strongest detected Wi-Fi signal.
  int strongestRssi = -1000;

  for (int i = 0; i < networkCount; i++) {
    int rssi = WiFi.RSSI(i);

    if (rssi > strongestRssi) {
      strongestRssi = rssi;
    }
  }

  Serial.print("Strongest RSSI: ");
  Serial.print(strongestRssi);
  Serial.println(" dBm");

  if (havePreviousReading) {
    int difference = abs(strongestRssi - previousRssi);

    Serial.print("RSSI change: ");
    Serial.print(difference);
    Serial.println(" dB");

    bool cooldownFinished =
        (currentTime - lastActivityTime >= COOLDOWN_MS);

    if (difference >= RSSI_CHANGE_THRESHOLD && cooldownFinished) {
      Serial.println("Activity change detected!");
      Serial.println();
      lastActivityTime = currentTime;
    }
  } else {
    havePreviousReading = true;
  }

  previousRssi = strongestRssi;

  WiFi.scanDelete();
}
