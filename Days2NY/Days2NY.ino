#include <RTClib.h>
#include <Wire.h>

RTC_DS1307 RTC;

void EnsureRTCisSet()
{
  if (!RTC.isrunning())
  {
    Serial.println("Setting the time");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

int i=0,cnt=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  EnsureRTCisSet();
  InitLEDMatrix();
  SetPixel(0,0,true);
  for (int i=0;i<16;i++) SetPixel(i,i,true);
}

void loop() {
  // put your main code here, to run repeatedly:
    DateTime now = RTC.now();
    Refresh();
    cnt=(cnt+1)%100;
}


