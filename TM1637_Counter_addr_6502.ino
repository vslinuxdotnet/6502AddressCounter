/*
 Address Counter for 6502 CPU's, read from A15 to A0 and display it by I2C with TM1637 driver on 7 segment display.
 Clock at 16MHz.
 Vasco Santos 12/01/2025
 */
#include <TM1637Display.h>
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);
  
uint32_t myresult = 0; 
byte pinsIN [16] = { 4,5,6,7,8,9,10,11,12,13,A0,A1,A2,A3,A4,A5};//A15 to A0
int pinsRD[16];
  
void setup() {

 display.setBrightness(2);
 Serial.begin(9600);
  Serial.println("Starting 6502 address counter!\n");
  for (int i=0;i< 16;i++)
  {
   pinMode(pinsIN[i], INPUT_PULLUP);
  }

}

void loop() {

 //Serial.println("");
  for (int i=0;i< 16;i++)
  {
    // pinMode(pinsIN[i], INPUT);
     int b = digitalRead(pinsIN[i]);
    //Serial.print(b);
    pinsRD[i] =  (char) b;
  
    myresult = myresult << 1;
    myresult = myresult | ( b & 1);
    
  }
  //Serial.println("");

  myresult = myresult+1;
  //Serial.println(myresult);
  
   display.showNumberHexEx(myresult,0,true,4,0); // Display the number
   
  //delay(100);
}                
