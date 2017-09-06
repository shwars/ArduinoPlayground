// Rotating Clock

#include <Adafruit_NeoPixel.h>
#include <Time.h>
#include <TimeLib.h>
#include <Adafruit_TiCoServo.h>
#include <known_16bit_timers.h>

#define Servo_PIN 9
#define LED_PIN 8

#define NUMPIXELS 12 // No of pixels on the hand

Adafruit_TiCoServo hand;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  Serial.print("Start");
  setTime(23,10,00,13,12,2017);
  pixels.begin();
  hand.attach(Servo_PIN);
  hand.write(0);
  for (int j=30;j>=0;j--)
  {
    for (int i=0;i<NUMPIXELS;i++)
    {
      pixels.setPixelColor(i,pixels.Color(j,j,0));
    }
    pixels.show();
    delay(10);
  }
}

int cnt=0;

int ang=0;

bool show_mins = false;

void loop() {
    unsigned int color = show_mins ? pixels.Color(40,0,0) : pixels.Color(0,0,40);
    if ((cnt/1000)%2==0)
    {
        pixels.setPixelColor(5, color);
        pixels.setPixelColor(6, color);
    }
    else
    {
        pixels.setPixelColor(5, pixels.Color(0,0,0));
        pixels.setPixelColor(6, pixels.Color(0,0,0));
    }
    pixels.show();
    if (cnt%3000==0)
    {
      Serial.print(ang);
      for (int i=0;i<10;i++)
      {
          hand.write(ang);
          ang++;
          delay(15);
      }
      if (ang>180) ang = 0;
    }
    cnt++;

}

