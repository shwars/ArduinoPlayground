#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(36, PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  strip.begin();
  strip.show();
}

// Light hour LED #n with intensity x
void hr_led(int n, int x)
{
   strip.setPixelColor(n%12,strip.Color(x,0,0) | strip.getPixelColor(n%12));
}

void mn_led(int n, int x)
{
   strip.setPixelColor(n%24+12,strip.Color(0,0,x) | strip.getPixelColor(n%24+12));
}

void sc_led(int n, int x)
{
   strip.setPixelColor(n%24+12,strip.Color(0,x,0) | strip.getPixelColor(n%24+12));
}


#define GRAD 7
#define GRAD1 8
int intensity[GRAD1] = { 0,1,2,4,16,32,64,128 };

void hr_disp(int hr, int mn, int sc)
{
   float mi = (float)mn+(float)sc/60.0;
   int x = (int)(pow(128,mi/24.0));
   int y = (int)(pow(128,(24.0-mi)/24.0));
   hr_led(hr,y);
   hr_led(hr+1,x);
}

void mn_disp(int mn, int sc)
{
   int x = (int)(pow(128,sc/24.0));
   int y = (int)(pow(128,(24.0-sc)/24.0));
   mn_led(mn,y);
   mn_led(mn+1,x);
}

void sc_disp(int sc, int scx)
{
   int x = (int)(pow(30,(float)scx/10.0));
   int y = (int)(pow(30,(10.0-(float)scx)/10.0));
   sc_led(sc,y);
   sc_led(sc+1,x);
}

void clear()
{
  for (int i=0;i<36;i++) strip.setPixelColor(i,0);
}

int hr = 0;
int mn = 0;
int sc = 0;
int n = 0;
int scx = 0;

void loop() 
{
    clear();
    // sc_led((int)((float)sc*24.0/60.0),10);
    sc_disp(sc,scx);
    hr_disp(hr,mn,sc);
    mn_disp(mn,sc);
    scx++; 
    if (scx==10) { scx=0; sc++; }
    if (sc==24) { sc=0; scx=0; mn++; }
    strip.show();
    if (mn==24)
    {
      hr++;
      if (hr>=12) hr=0;
      mn=0;
    }  
    delay(50);
}


