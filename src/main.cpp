#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

void initWiFi();

// NTP Variables
WiFiUDP ntpUDP;
// DST
//NTPClient timeClient(ntpUDP, "xxx.xxx.xxx.xxx", 37800, 60000);
// Non-DST
NTPClient timeClient(ntpUDP, "xxx.xxx.xxx.xxx", 34200, 60000);

// WiFi Creds
const char* ssid = "*******";
const char* password = "********";

// Static IP address

// Onboard LED
int onboardLED = 2;

// Time Strings
String timeString = "";
String currentMinutesStr = "";
String checkTime = "";

void setup() {
  pinMode (onboardLED, OUTPUT);
  digitalWrite(onboardLED, LOW);
  Serial.begin(9600, SERIAL_8N1, -1, 17);
  // Serial.begin(9600);
  initWiFi();
}

void loop() {
  // Update the Time Client
  timeClient.update();
  // Get current hours and Minutes.
  timeString = timeClient.getFormattedTimeNoSec();
  
  // Delay the sending of data for 1 minute, will only send at the start of every minute
  if (checkTime != timeString){
    Serial.println(timeString);
    checkTime = timeString;
  }
}


void initWiFi() {
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  String hostname = "ESP_DMD_Clock";
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname.c_str());
  WiFi.begin(ssid, password);
  // Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    // Serial.print('.');
    delay(1000);
  }
  // Serial.println(WiFi.localIP());
  timeClient.begin();
  digitalWrite(onboardLED, HIGH);
}