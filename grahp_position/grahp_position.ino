#include <LedControl.h> //connect 3.3v to AREF

int  x = 0;
int  y = 0;
int gx = 0;
int gy = 0;

int mode =  0;
int xPin = A1; 
int yPin = A2; 

int DIN = 12;
int CS =  11;
int CLK = 10;

byte  px[]=  {0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01}; 
byte  p[8]=  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}; 
//animation
byte a1[8]=  {0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte a2[8]=  {0x08,0x08,0x00,0x00,0x00,0x00,0x00,0x00};
byte a3[8]=  {0x08,0x08,0x08,0x00,0x00,0x00,0x00,0x00};
byte a4[8]=  {0x00,0x08,0x08,0x08,0x00,0x00,0x00,0x00};
byte a5[8]=  {0x00,0x00,0x08,0x08,0x08,0x00,0x00,0x00};
byte a6[8]=  {0x00,0x00,0x00,0x08,0x08,0x08,0x00,0x00};
byte a7[8]=  {0x00,0x00,0x00,0x18,0x18,0x08,0x00,0x00};
byte a8[8]=  {0x00,0x00,0x00,0x38,0x18,0x08,0x00,0x00};

LedControl lc=LedControl (DIN,CLK,CS,0);

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 5);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
}

void loop() {
  x = analogRead(xPin) - 501;  //Lee el eje x
  y = analogRead(yPin) - 510;  //Lee el eje y
  Serial.print(analogRead(xPin)- 499);
  Serial.print("\t");
  Serial.print(analogRead(yPin)- 509);
  Serial.println("\t");

  if(mode == 0){
    printByte(a1);delay(90);
    printByte(a2);delay(90);
    printByte(a3);delay(90);
    printByte(a4);delay(90);
    printByte(a5);delay(90);
    printByte(a6);delay(300);
    printByte(a7);delay(100);
    printByte(a8);delay(1000);
    mode = mode + 1;
  }
   
  if(mode == 1) {
    if(x >= -40 && x <= -31) {gx = 0;}
    if(x >= -30 && x <= -21) {gx = 1;}
    if(x >= -20 && x <= -11) {gx = 2;}
    if(x >= -10 && x <= 0)   {gx = 3;}
    if(x >= 1  &&  x <= 10)  {gx = 4;}
    if(x >= 11 &&  x <= 20)  {gx = 5;}
    if(x >= 21 &&  x <= 30)  {gx = 6;}
    if(x >= 31 &&  x <= 40)  {gx = 7;}
    if(y >= -40 && y <= -31) {gy = 0;}
    if(y >= -30 && y <= -21) {gy = 1;}
    if(y >= -20 && y <= -11) {gy = 2;}
    if(y >= -10 && y <= 0)   {gy = 3;}
    if(y >= 1  &&  y <= 10)  {gy = 4;}
    if(y >= 11 &&  y <= 20)  {gy = 5;}
    if(y >= 21 &&  y <= 30)  {gy = 6;}
    if(y >= 31 &&  y <= 40)  {gy = 7;}
  printEduc8s();
  }
}

void printEduc8s() {
  if(gy == 0){ p[0] = px[gx]; printByte(p);} 
    else{p[0]={0x00};}
  if(gy == 1){ p[1] = px[gx]; printByte(p);} 
    else{p[1]={0x00};}
  if(gy == 2){ p[2] = px[gx]; printByte(p);} 
    else{p[2]={0x00};}
  if(gy == 3){ p[3] = px[gx]; printByte(p);} 
    else{p[3]={0x00};}
  if(gy == 4){ p[4] = px[gx]; printByte(p);} 
    else{p[4]={0x00};} 
  if(gy == 5){ p[5] = px[gx]; printByte(p);} 
    else{p[5]={0x00};} 
  if(gy == 6){ p[6] = px[gx]; printByte(p);} 
    else{p[6]={0x00};} 
  if(gy == 7){ p[7] = px[gx]; printByte(p);} 
    else{p[7]={0x00};}
}

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
