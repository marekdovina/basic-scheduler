#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdlib.h>

// Cron Handler variables
// if true tasks can be executed
// false when tasks already executed
bool cronHandler5m = true;
bool cronHandler15m = true;
bool cronHandler30m = true;
bool cronHandler0h = true;

// WiFi parameters to connect
const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";

// NTPClient constants
#define NTP_OFFSET   60 * 60    // In seconds
#define NTP_INTERVAL 60 * 1000 // In miliseconds
#define NTP_ADDRESS  "europe.pool.ntp.org"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, NTP_OFFSET, NTP_INTERVAL);

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(100);

  // connect to WiFi
  connectWifi();

  // Get time from internet
  timeClient.begin();
}

void loop() {
  // NTPClient - getting time from Internet
  String formattedTime = timeClient.getFormattedTime();
  int currentHour = timeClient.getHours();
  int currentMinutes = timeClient.getMinutes();
  Serial.print("Getting time from internet: ");
  Serial.println(formattedTime);
  
  // EXECUTE Tasks at exact time based on NTPClient time
  // cronTabHandler - set schedlures to be executable
  // cronTabExecution - execute schedulers
  cronTabHandler(currentHour, currentMinutes);
  cronTabExecution(currentHour, currentMinutes);

  delay(1000);
  
}

// -------------------------------
// Set schedulers to be executable
// -------------------------------
void cronTabHandler(int cHour, int cMinutes) {
  if(cronHandler5m == false && cMinutes % 5 > 0) {
    cronHandler5m = true;
  }
  if(cronHandler15m == false && cMinutes % 15 > 0) {
    cronHandler15m = true;
  }
  if(cronHandler30m == false && cMinutes % 30 > 0) {
    cronHandler30m = true;
  }
  if(cronHandler0h == false && cHour > 0) {
    cronHandler0h = true;
  }

  Serial.print("cronHandler5m = ");
  Serial.println(cronHandler5m);
  Serial.print("cronHandler15m = ");
  Serial.println(cronHandler15m);
  Serial.print("cronHandler30m = ");
  Serial.println(cronHandler30m);
  Serial.print("cronHandler0h = ");
  Serial.println(cronHandler0h);
  
}
// -------------------------------
// Execute tasks only on specified
// time
// -------------------------------
void cronTabExecution(int cHour, int cMinutes) {
  unsigned long cronDuration;
  cronDuration = millis();
  
  // TASKS every 5mins
  if(cMinutes % 5 == 0 && cronHandler5m == true) {
    Serial.println("========================================");
    Serial.println("Cron tasks activated!");
    Serial.println("----------------------------------------");
    Serial.print(cHour);
    Serial.print(":");
    Serial.println(cMinutes);
    Serial.println("Running tasks planned for every 5mins");
    Serial.println("========================================");

    // set scheduler to be not executable
    cronHandler5m = false;
    delay(1000);
  }
  // TASKS every 15mins
  if(cMinutes % 15 == 0 && cronHandler15m == true) {
    Serial.println("========================================");
    Serial.println("Cron tasks activated!");
    Serial.println("----------------------------------------");
    Serial.print(cHour);
    Serial.print(":");
    Serial.println(cMinutes);
    Serial.println("Running tasks planned for every 15mins");
    Serial.println("========================================");

    // set scheduler to be not executable
    cronHandler15m = false;
    delay(1000);
  }
  // TASKS every 30mins
  if(cMinutes % 30 == 0 && cronHandler30m == true) {
    Serial.println("========================================");
    Serial.println("Cron tasks activated!");
    Serial.println("----------------------------------------");
    Serial.print(cHour);
    Serial.print(":");
    Serial.println(cMinutes);
    Serial.println("Running tasks planned for every 30mins");
    Serial.println("========================================");
    
    // update NTPClient timeClient from internet
    timeClient.update();

    // set scheduler to be not executable
    cronHandler30m = false;
    delay(1000);
  }
  // TASKS on midnight
  if(cHour == 0 && cronHandler0h == true) {
    Serial.println("========================================");
    Serial.println("Cron tasks activated!");
    Serial.println("----------------------------------------");
    Serial.print(cHour);
    Serial.print(":");
    Serial.println(cMinutes);
    Serial.println("Running tasks planned for every midnight");
    Serial.println("========================================");

    // set scheduler to be not executable
    cronHandler0h = false;
    delay(1000);
  }

  cronDuration = (millis() - cronDuration) / 1000;
  Serial.print("Duration of cron execution was ");
  Serial.print(cronDuration);
  Serial.println("s!\n");
}

// -------------------------------
// Connect to WiFi
// -------------------------------
void connectWifi() {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  int dots = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    dots++;
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
}

