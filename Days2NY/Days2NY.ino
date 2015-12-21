#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 RTC;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  if (!RTC.isrunning())
  {
    Serial.println("Setting the time");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = RTC.now();
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    delay(3000);
}
