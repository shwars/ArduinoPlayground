#include <RTClib.h>
#include <Wire.h>

DateTime NY(2016,12,31,23,59,59);

RTC_DS1307 RTC;

void EnsureRTCisSet()
{
  if (RTC.isrunning())
  {
    Serial.println("Setting the time");
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

int i=0,cnt=0,scrcnt=0,scrdir=1,screen=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  RTC.begin();
  EnsureRTCisSet();
  InitLEDMatrix();
  setupPics();
  SetCurrentBuffer(1);
  DrawXMas();
  SetCurrentBuffer(0);
  resetFW();
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
         DisplayDigit47(t%10,1+k*5,1);
         t/=10;
      }
}

void disp2(byte x, byte y, int t)
{
   DisplayDigit37(t/10,x,y);
   DisplayDigit37(t%10,x+4,y);
}

void dispm(byte x, byte y, int t)
{
   DisplayDigit35(t/10,x,y);
   DisplayDigit35(t%10,x+4,y);
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

TimeSpan ts;
bool show_fw=false;
void loop() {
  // put your main code here, to run repeatedly:
    DateTime now = RTC.now();
    LEDloop();
    loopPics();
    if(show_fw) loopFW();
    cnt=(cnt+1)%20;
    if (cnt==0)
    {
      i++;
      SetCurrentBuffer(0);
      if (NY.unixtime()>now.unixtime())
      {
         ts = NY-now;
         disp(ts.hours()+24*ts.days());
         DrawLeft();  
         show_fw=false; 
      }
      else
      {
         ts = now-NY;
         disp(ts.hours()+24*ts.days());
         show_fw=true;
      }
      if (!isScrolling())
      {
        int n = ts.minutes()*16/60;
        for (int i=0;i<16;i++) SetPixel(i,15,i<=n);
      }
      else
      {
        for (int i=0;i<16;i++) SetPixel(i,14,false);      
      }
      SetCurrentBuffer(2);
      disp2(0,1,now.hour());
      disp2(9,1,now.minute());
      SetPixel(7,2,i%2);
      SetPixel(8,2,i%2);
      SetPixel(7,3,i%2);
      SetPixel(8,3,i%2);
      SetPixel(7,5,i%2);
      SetPixel(8,5,i%2);
      SetPixel(7,6,i%2);
      SetPixel(8,6,i%2);
      dispm(0,10,now.day());
      dispm(9,10,now.month());
      SetPixel(8,14,true);
      SetPixel(9,14,true);      
      SetPixel(8,13,true);
      SetPixel(9,13,true);      
    }
    scrcnt=(scrcnt+1)%210;
    if (scrcnt==0)
    {
      StartScroll(scrdir);
      screen+=scrdir;
      if (screen==2) scrdir = -1;
      if (screen==0)
      {
        scrdir = 1;
        resetFW();
      }
    }
}


