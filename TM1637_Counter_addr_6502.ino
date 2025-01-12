/*
  Address Counter for 6502 CPU's, read from A15 to A0 and display it in I2C with TM1637 driver on 7 segment display.
  Clock at 25MHz.
  To add on arduino boards.txt file to add more clocks speeds:

      menu.clock=Clock
      
      nano.menu.clock.external16=External 16 MHz
      nano.menu.clock.external16.bootloader.low_fuses=0xff
      nano.menu.clock.external16.bootloader.high_fuses=0xdb
      nano.menu.clock.external16.bootloader.extended_fuses=0xfd
      nano.menu.clock.external16.build.f_cpu=16000000L
      
      nano.menu.clock.external20=External 20 MHz
      nano.menu.clock.external20.bootloader.low_fuses=0xff
      nano.menu.clock.external20.bootloader.high_fuses=0xdb
      nano.menu.clock.external20.bootloader.extended_fuses=0xfd
      nano.menu.clock.external20.build.f_cpu=20000000L
      
      
      nano.menu.clock.external25=External 25 MHz
      nano.menu.clock.external25.bootloader.low_fuses=0xff
      nano.menu.clock.external25.bootloader.high_fuses=0xdb
      nano.menu.clock.external25.bootloader.extended_fuses=0xfd
      nano.menu.clock.external25.build.f_cpu=25000000L


  Note: Default bootloader will not work at 25mhz, you must change the cristal to flash or build a bootloader to support 25mhz.
  Vasco Santos 12/01/2025
  vascosantos81ATgmail.com
*/


#include <TM1637Display.h>
#include <digitalWriteFast.h>
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

uint32_t myresult = 0;
byte pinsIN [16] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A0, A1, A2, A3, A4, A5 }; //A15 to A0
int pinsRD[16];

void setup() {
  //delay(100);

  display.setBrightness(2);
  Serial.begin(115200);
  Serial.println("Starting 6502 address counter!\n");

  for (int i = 0; i < 16; i++)
  {
    // pinMode(pinsIN[i], INPUT_PULLUP);
    //pinMode(pinsIN[i], INPUT);
    pinModeFast(pinsIN[i], INPUT);
  }

}

void loop() {

  Serial.println("");
  myresult = 0;
  for (int i = 0; i < 16; i++)
  {
    // pinMode(pinsIN[i], INPUT);
    //int b = digitalRead(pinsIN[i]);
    int b = digitalReadFast(pinsIN[i]);
    Serial.print(b);
    //pinsRD[i] =  (char) b;

    myresult = myresult << 1;
    myresult = myresult | ( b & 1);

  }
  Serial.println("");

  //myresult = myresult+1;
  Serial.println(myresult);
  Serial.print("0x");
  Serial.println(myresult, HEX);

  display.showNumberHexEx(myresult, 0, true, 4, 0); // Display the number

  //delay(10);
}
