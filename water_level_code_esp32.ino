#define BLYNK_TEMPLATE_ID "TMPL3NIBbzjK3"
#define BLYNK_TEMPLATE_NAME "Water level Detection"
#define BLYNK_AUTH_TOKEN "2zZvVBAa92v5EnqkZYLaW_vKShqQXQap"
#define BLYNK_PRINT Serial // Enables serial print for monitoring
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Blynk authentication token, replace with your own
char auth[] = BLYNK_AUTH_TOKEN;  // Use the authentication token from your Blynk project
 

// Your Wi-Fi credentials, replace with your network credentials
char ssid[] = "your_wifi_name";
char pass[] = "your_hotspot_password";

// Pin where the soil moisture sensor is connected
int sensorPin = 34;  // Analog pin on ESP32

// Define variables
int sensorValue = 0;  // Variable to store the sensor reading
int moisturePercent = 0;  // Variable to store the moisture level as a percentage

// Threshold to trigger the notification (adjust according to your needs)
int dryThreshold = 30;  // Example: if moisture falls below 30%, send a notification
int wetThreshold = 70;  // Example: if moisture exceeds 70%, send a notification

// Variable to keep track of whether notification was sent to avoid spam
bool notificationSent = false;

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Optionally, you can wait until connected to Blynk before starting
  while (Blynk.connect() == false) {
    // Wait until connected
  }

  // Print message when connected
  Serial.println("Connected to Blynk Server");
}

void loop() {
  // Read the raw analog value from the soil moisture sensor
  sensorValue = analogRead(sensorPin);

  // Map the sensor value to a percentage (0% = dry, 100% = wet)
  moisturePercent = map(sensorValue, 4095, 0, 0, 100);  // Adjust as per calibration

  // Print the raw sensor value and percentage for debugging
  Serial.print("Raw Sensor Value: ");
  Serial.println(sensorValue);
  Serial.print("Moisture Percentage: ");
  Serial.print(moisturePercent);
  Serial.println("%");

  // Send the moisture percentage to the Blynk app (e.g., Virtual Pin V0)
  Blynk.virtualWrite(V0, moisturePercent);

 

  // Handle Blynk communication
  Blynk.run();
}