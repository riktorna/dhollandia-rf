#include "SPI.h"
#include "NRFLite.h"
#include <U8g2lib.h>
#include <Wire.h>

#define UP 5
#define DOWN 6
#define LATCH 2
#define BEEP 3
#define RADIO_ID  1
#define DESTINATION_RADIO_ID  0
#define PIN_RADIO_CE  9
#define PIN_RADIO_CSN  10

int CODE = 000;

struct zendblok1
{
  bool zoekzender;
  int omhoog;
  int omlaag;
  int omhoog_k;
  int omlaag_k;
};

zendblok1 codeping;
byte fails = 0;
long lost;
bool verbonden = false;
bool voertuig;
bool modus;

/*Radio    Arduino
  CE    -> 9
  CSN   -> 10 (Hardware SPI SS)
  MOSI  -> 11 (Hardware SPI MOSI)
  MISO  -> 12 (Hardware SPI MISO)
  SCK   -> 13 (Hardware SPI SCK)
  IRQ   -> No connection
  VCC   -> No more than 3.6 volts
  GND   -> GND
*/

NRFLite _radio;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 8, /* data=*/ 7, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LATCH, INPUT_PULLUP);
  pinMode(BEEP, OUTPUT);

  drawscreen(1);
  beep();

  do {                 // teken het handleidingsscherm
    drawscreen(2);
  } while (digitalRead(UP));

  zoekontvanger(125);
  beep();
}

void loop() {

  /*if (fails >= 100) {
    drawscreen(9);
       sendcode();

      if ((millis() - lost) >= 60000) {
        zoekontvanger(125);
      }
    } */
    
    if (!digitalRead(UP)) { //als er op de groene knop wordt gedrukt, ga dan omhoog (kantelen)
    if (modus == true) {
      CODE = codeping.omhoog;
      sendcode();
      drawscreen(5);
    } else {
      CODE = codeping.omhoog_k;
      sendcode();
      drawscreen(7);
    }
    sendcode();

  } else if (!digitalRead(DOWN)) {//als er op de rode knop wordt gedrukt, ga dan omlaag (kantelen)
    if (modus == true) {
      CODE = codeping.omlaag;
      sendcode();
      drawscreen(6);
    } else {
      CODE = codeping.omlaag_k;
      sendcode();
      drawscreen(8);
    }
    sendcode();

  } else {                        // als er niets gebeurd;
    modus = digitalRead(LATCH);   // zet dan de modus goed
    CODE = 000;                   // en stuur een lege code zodat de ontvanger weet dat je er nog bent
    sendcode();
    drawscreen(4);
  }
  delay(50);
  Serial.println(CODE);
}
