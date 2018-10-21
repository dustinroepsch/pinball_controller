#include <Arduino.h>
#include <HardwareSerial.h>
// #include "../shared/CommunicationsConstants.h"

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

        Serial.write(bt == 0 ? 8 : bt == 1 ? 34 : 10);
    }
    // i++;
}