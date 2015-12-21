#include <Arduino.h>

// Connections    
#define LEDARRAY_D 2
#define LEDARRAY_C 3
#define LEDARRAY_B 4
#define LEDARRAY_A 5
#define LEDARRAY_G 6
#define LEDARRAY_DI 7
#define LEDARRAY_CLK 8
#define LEDARRAY_LAT 9

unsigned char DisplayBuffer[32];

unsigned char *GetBuffer()
{
  return DisplayBuffer;
}

void InitLEDMatrix()
{
  pinMode(LEDARRAY_D, OUTPUT); 
  pinMode(LEDARRAY_C, OUTPUT);
  pinMode(LEDARRAY_B, OUTPUT);
  pinMode(LEDARRAY_A, OUTPUT);
  pinMode(LEDARRAY_G, OUTPUT);
  pinMode(LEDARRAY_DI, OUTPUT);
  pinMode(LEDARRAY_CLK, OUTPUT);
  pinMode(LEDARRAY_LAT, OUTPUT);
  for(int i=0;i<32;i++) DisplayBuffer[i] = 0;  
}

void SetPixel(byte x, byte y, bool onoff)
{
  byte no = x+16*(y/8);
  byte m = getMask(y%8);
  if (onoff) DisplayBuffer[no] |= m;
  else DisplayBuffer[no] &= ~m;
}

void Fill(byte x, byte y, byte w, byte h, bool onoff)
{
  for (byte i=0; i<w; i++)
     for (byte j=0;j<h; j++)
        SetPixel(x+i,y+j,onoff);
}

void ByteLine(byte x, byte y, int w, byte l)
{
   for (byte i=w;i>0;i--)
   {
      SetPixel(x+i-1,y,l%2);
      l>>=1;
   }
}

void DisplaySprite(int x, int y, int w, int h, byte[] buf)
{
  for (byte i=0;i<h;i++)
  {
     ByteLine(x,y+i,w,buf[i]);
  }
}

byte getMask(byte n)
{
  byte res = 1;
  for (byte i=0;i<n;i++) res = res << 1;
  return res;
}

void Refresh()         
{
  unsigned char i;
  unsigned char db0, db1;
  for( i = 0 ; i < 16 ; i++ )
  {
    digitalWrite(LEDARRAY_G, HIGH);
    db0 = ~DisplayBuffer[i];    
    db1 = ~DisplayBuffer[i+16];
    Send(db0);
    Send(db1);
    digitalWrite(LEDARRAY_LAT, HIGH);   
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_LAT, LOW);
    delayMicroseconds(1);
    Scan_Line(i);
    digitalWrite(LEDARRAY_G, LOW);
    delayMicroseconds(200);;
  } 
}

void Scan_Line( unsigned char m)
{ 
  switch(m)
  {
    case 0:     
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);          
      break;
    case 1:         
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);     
      break;
    case 2:         
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);     
      break;
    case 3:         
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);    
      break;
    case 4:
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);     
      break;
    case 5:
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);    
      break;
    case 6:
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);    
      break;
    case 7:
      digitalWrite(LEDARRAY_D, LOW);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);     
      break;
    case 8:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);     
      break;
    case 9:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);    
      break;  
    case 10:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);    
      break;
    case 11:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, LOW);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);     
      break;
    case 12:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, LOW);    
      break;
    case 13:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, LOW);digitalWrite(LEDARRAY_A, HIGH);     
      break;
    case 14:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, LOW);     
      break;
    case 15:
      digitalWrite(LEDARRAY_D, HIGH);digitalWrite(LEDARRAY_C, HIGH);digitalWrite(LEDARRAY_B, HIGH);digitalWrite(LEDARRAY_A, HIGH);    
      break;
    default : break;  
  }
}

void Send(unsigned char dat)
{
  unsigned char i;
  digitalWrite(LEDARRAY_CLK, LOW);
  delayMicroseconds(1);;  
  digitalWrite(LEDARRAY_LAT, LOW);
  delayMicroseconds(1);;
  for( i = 0 ; i < 8 ; i++ )
  {
    if( dat&0x01 )
    {
      digitalWrite(LEDARRAY_DI, HIGH);  
    }
    else
    {
      digitalWrite(LEDARRAY_DI, LOW);
    }
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, HIGH);
    delayMicroseconds(1);
    digitalWrite(LEDARRAY_CLK, LOW);
    delayMicroseconds(1);   
    dat >>= 1;  
  }     
}

