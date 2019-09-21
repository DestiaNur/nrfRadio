#include <SPI.h>
#include "RF24.h"
#include <ESP8266WiFi.h>

RF24 myRadio(2, 15);
const char* ssid = "ASUS_DESTIA";
const char* password = "14121998";
struct package
{
    int id = 0;
    float longitude = 0.0;
    float latitude = 0.0;
    char text[100] = "empty";
};

byte addresses[][6] = {"0"};
typedef struct package Package;
Package data;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    WiFi.begin(ssid, password);

    Serial.println();
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
     delay(500);
     Serial.print(".");
    }
    Serial.println("success!");
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openReadingPipe(1, addresses[0]);
    myRadio.startListening();
}

void loop()
{
    if (myRadio.available())
    {
        while (myRadio.available())
        {
            myRadio.read(&data, sizeof(data));
        }
        Serial.print("\nPackage:");
        Serial.print(data.id);
        Serial.print("\n");
        Serial.println(data.longitude);
        Serial.println(data.latitude);
        Serial.println(data.text);
    }
}
