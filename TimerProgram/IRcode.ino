#include <IRremote.h>

const int RECV_PIN = 14;  // GPIO pin connected to the IR receiver

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
    Serial.begin(9600);
    Serial.println("Initializing IR Receiver...");
    irrecv.enableIRIn();  // Start the IR receiver
    delay(100);  // Allow time for the IR receiver to stabilize
    Serial.println("IR Receiver Initialized");
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.print("IR Code: ");
        Serial.println(results.value, HEX);  // Print the received code in hexadecimal format
        irrecv.resume();  // Receive the next value
    } else {
        //Serial.println("Waiting for IR signal...");
    }
    delay(100);  // Small delay to prevent continuous polling
}
