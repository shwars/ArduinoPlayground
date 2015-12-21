#include <RTClib.h>
#include <Wire.h>

DateTime NY(2015,12,31,23,59,59);

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
  /* draw frame ---
  for (int i=0;i<16;i++)
  {
    SetPixel(i,0,true); SetPixel(i,15,true);
  }
  for (int i=0;i<16;i++)
  {
    SetPixel(0,i,true); SetPixel(15,i,true);
  }
  */
}

void disp(int t)
{
      for (int k=2;k>=0;k--)
      {
         DisplayDigit47(t%10,1+k*5,3);
         t/=10;
      }
}

void disp2(byte x, byte y, int t)
{
   DisplayDigit37(t/10,x,y);
   DisplayDigit37(t%10,x+4,y);
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
    cnt=(cnt+1)%20;
    if (cnt==0)
    {
      i++;
      SetCurrentBuffer(0);
      TimeSpan ts = NY-now;
      disp(ts.hours()+24*ts.days());
      if (!isScrolling())
      {
        int n = ts.minutes()*16/60;
        for (int i=0;i<16;i++) SetPixel(i,14,i<=n);
      }
      else
      {
        for (int i=0;i<16;i++) SetPixel(i,14,false);      
      }
      SetCurrentBuffer(1);
      disp2(0,2,now.hour());
      disp2(9,2,now.minute());
      SetPixel(7,3,i%2);
      SetPixel(8,3,i%2);
      SetPixel(7,4,i%2);
      SetPixel(8,4,i%2);
      SetPixel(7,6,i%2);
      SetPixel(8,6,i%2);
      SetPixel(7,7,i%2);
      SetPixel(8,7,i%2);
    }
    scrcnt=(scrcnt+1)%500;
    if (scrcnt==0)
    {
      StartScroll(scrdir);
      scrdir*=-1;
    }
}


