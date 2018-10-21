#include <Arduino.h>
#include <HardwareSerial.h>
// #include "../shared/CommunicationsConstants.h"]


void setup()
{
    Serial.begin(9600);
}
// int i = 0;
void loop()
{
    if (Serial.available() > 0)
    {
        int bt = Serial.read();

        if (bt == 10) {
            Serial.write(1);
        } else {
            Serial.write(0);
        }
    }
    // i++;
}