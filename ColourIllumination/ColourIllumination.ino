
int rgb[] ={9,10,11};

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  for (int i=0;i<3;i++) pinMode(rgb[i],OUTPUT);
  pinMode(13, OUTPUT);
}


int n=0;
int c=0;

// the loop function runs over and over again forever
void loop() {
  switch(c)
  {
    case 0: wr(n,0,0); break;
    case 1: wr(30-n,n,0); break;
    case 2: wr(0,30-n,n); break;
    case 3: wr(n,0,30-n); break;
    case 4: wr(30-n,n,n); break;
    case 5: wr(n,30-n,30-n); break;
    case 6: wr(30-n,0,0); break;
  }
  delay(100);
  n=(n+1)%30;
  if (n==0) c =(c+1)%7;
}

void wr(int r, int g, int b)
{
  analogWrite(rgb[0],r);
  analogWrite(rgb[1],g);
  analogWrite(rgb[2],b);
}

