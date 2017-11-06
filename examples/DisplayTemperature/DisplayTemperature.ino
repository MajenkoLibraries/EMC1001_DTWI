#include <DTWI.h>
#include <EMC1001_DTWI.h>

DTWI0 dtwi;
EMC1001 emc(dtwi);;

void setup() {
#ifdef PIN_SENSOR_POWER
  pinMode(PIN_SENSOR_POWER, OUTPUT);
  digitalWrite(PIN_SENSOR_POWER, HIGH);
#endif
  emc.begin();
  Serial.begin(115200);
}

void loop() {
  Serial.println(emc.getTemperature());
  delay(1000);
}

