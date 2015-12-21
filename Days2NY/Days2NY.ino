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

int i=0,cnt=0,scrcnt=0,scrdir=1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  EnsureRTCisSet();
  InitLEDMatrix();
  SetCurrentBuffer(0);
  for (int i=0;i<16;i++)
  {
    SetPixel(i,0,true); SetPixel(i,15,true);
  }
  for (int i=0;i<16;i++)
  {
    SetPixel(0,i,true); SetPixel(15,i,true);
  }
}

void disp(int t)
{
      for (int k=2;k>=0;k--)
      {
         DisplayDigit(t%10,1+k*5,3);
         t/=10;
      }
}

void testloop()
{
  LEDloop();
    cnt=(cnt+1)%50;
    if (cnt==0)
    {
      SetPixel(0,i,true);
      i++;
    }
}

void loop() {
  // put your main code here, to run repeatedly:
    DateTime now = RTC.now();
    LEDloop();
    cnt=(cnt+1)%50;
    if (cnt==0)
    {
      i++;
      SetCurrentBuffer(0);
      disp(i);
      SetCurrentBuffer(1);
      disp(1000-i);
    }
    scrcnt=(scrcnt+1)%500;
    if (scrcnt==0)
    {
      StartScroll(scrdir);
      scrdir*=-1;
    }
}


