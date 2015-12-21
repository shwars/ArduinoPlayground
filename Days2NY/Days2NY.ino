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
}

void loop() {
  // put your main code here, to run repeatedly:
    DateTime now = RTC.now();
    Refresh();
    cnt=(cnt+1)%50;
    if (cnt==0)
    {
      i++;
      int t = i;
      for (int k=2;k>=0;k--)
      {
         DisplayDigit(t%10,1+k*5,3);
         t/=10;
      }
    }
}


