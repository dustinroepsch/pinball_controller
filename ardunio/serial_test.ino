#include <Arduino.h>
#include <HardwareSerial.h>
#include "../shared/CommunicationsConstants.h"

void setup() {
    Serial.begin(9600);
}
// int i = 0;
void loop() {
    if (Serial.available() > 0) {
        char bt = Serial.read();
        Serial.write(bt + 1);
    }
    // i++;
}