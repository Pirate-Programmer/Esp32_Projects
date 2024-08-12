#include <WiFi.h>
#include "time.h"

//network details
char* ssid = "Skeletron:D";
char* password = "87654321";
const char* ntpServer = "pool.ntp.org";

void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN,LOW);

  Serial.begin(115200);
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(2000);
    Serial.println("\nConnecting to Wifi...");
  }

  Serial.println("Connected To Wifi");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  configTime(19800, 0, ntpServer);
}


void loop() {
  //user input
  //int timer_value = //ir remote

  // get current time c
  //do action : printlocaltime() + timer_value == current_time send by ntp
   //
   //
}

int printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return 404;
  }
  return tm_hour*60*60 + tm_min*60m + tm_sec; 
}

