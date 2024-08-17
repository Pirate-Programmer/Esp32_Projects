#include <WiFi.h>
#include <IRremote.h>
#include "time.h"


const char* ssid = "pravin_home";
const char* password = "ashu29";
const char* ntpServer = "pool.ntp.org";


const int RECV_PIN = 14;
IRrecv irrecv(RECV_PIN);
decode_results results;

const unsigned long BUTTON_1 = 0xFF30CF;
const unsigned long BUTTON_2 = 0xFF18E7;
const unsigned long BUTTON_3 = 0xFF7A85;
const unsigned long BUTTON_4 = 0xFF10EF;
const unsigned long BUTTON_5 = 0xFF38C7;
const unsigned long BUTTON_6 = 0xFF5AA5;
const unsigned long BUTTON_7 = 0xFF42BD;
const unsigned long BUTTON_8 = 0xFF4AB5;
const unsigned long BUTTON_9 = 0xFF52AD;

void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(2000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    configTime(19800, 0, ntpServer);

    irrecv.enableIRIn();  
    delay(100);
    displayMenu();
}

void loop() {
    if (irrecv.decode(&results)) {
        handleRemoteInput(results.value);
        irrecv.resume();
    }
}

void displayMenu() {
    Serial.println("\n\nSelect a timer duration using the remote:");
    Serial.println("1. 1 min");
    Serial.println("2. 2 min");
    Serial.println("3. 3 min");
    Serial.println("4. 4 min");
    Serial.println("5. 5 min");
    Serial.println("6. 6 min");
    Serial.println("7. 7 min");
    Serial.println("8. 8 min");
    Serial.println("9. 9 min");
}

void handleRemoteInput(unsigned long code) {
    int duration = 0;

    switch (code) {
        case BUTTON_1:
            duration = 1;
            Serial.println("Timer set for 1 min");
            break;
        case BUTTON_2:
            duration = 2;
            Serial.println("Timer set for 2 min");
            break;
        case BUTTON_3:
            duration = 3;
            Serial.println("Timer set for 3 min");
            break;
        case BUTTON_4:
            duration = 4;
            Serial.println("Timer set for 4 min");
            break;
        case BUTTON_5:
            duration = 5;
            Serial.println("Timer set for 5 min");
            break;
        case BUTTON_6:
            duration = 6;
            Serial.println("Timer set for 6 min");
            break;
        case BUTTON_7:
            duration = 7;
            Serial.println("Timer set for 7 min");
            break;
        case BUTTON_8:
            duration = 8;
            Serial.println("Timer set for 8 min");
            break;
        case BUTTON_9:
            duration = 9;
            Serial.println("Timer set for 9 min");
            break;
        default:
            return;
    }

    startTimer(duration);
}

//googled

void startTimer(int minutes) {
    Serial.print("Starting timer at: ");
    Serial.println(getLocalTime());

    unsigned long startMillis = millis();
    unsigned long durationMillis = minutes * 60000;

    while (millis() - startMillis < durationMillis) {
        unsigned long elapsedMillis = millis() - startMillis;
        unsigned long remainingMillis = durationMillis - elapsedMillis;
        int remainingSeconds = remainingMillis / 1000;

        Serial.print("Time left: ");
        Serial.print(remainingSeconds / 60);
        Serial.print(" min ");
        Serial.print(remainingSeconds % 60);
        Serial.println(" sec");

        delay(1000);  
    }

    Serial.print("Timer ended at: ");
    Serial.println(getLocalTime());
}

String getLocalTime() {
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return "ERROR";
    }

    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
    return String(timeStr);
}

