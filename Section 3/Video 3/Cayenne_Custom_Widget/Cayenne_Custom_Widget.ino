#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP32.h>

// WiFi network info.
char ssid[] = "makerdemy1";
char wifiPassword[] = "india123";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "d63c20e0-25f9-11e9-898f-c12a468aadce";
char password[] = "e8769bfb361d6ba8cca9eca39bb9984bcb7d0e50";
char clientID[] = "67091af0-6c0f-11e9-bdb6-1dfb99981a8c";
unsigned long lastMillis = 0;
int touch = 15;
int sense;
int state;

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
  sense = touchRead(touch);
  
  if(millis() - lastMillis > 1000) {
      lastMillis = millis();
      if(sense < 10)
      {
      state = 1;
      Serial.println(state);
      Cayenne.virtualWrite(0, state, "digital_sensor", "d");
      }
      else
     {
       state = 0;
       Serial.println(0);
       Cayenne.virtualWrite(0, state, "digital_sensor", "d");
     }
   }
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  //Cayenne.virtualWrite(0, millis());
  // Some examples of other functions you can use to send data.
  //Cayenne.celsiusWrite(1, 22.0);
  //Cayenne.luxWrite(2, 700);
  //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
