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

struct zendblok1
{
  bool zoekzender;
  int omhoog;
  int omlaag;
  int omhoog_k;
  int omlaag_k;
};

zendblok1 codeping;
int CODE = 000;
byte fails = 0;
byte screentodraw;
long lost;
bool verbonden = false;
bool voertuig;
bool modus;
byte keuze = 0;

NRFLite _radio;
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 8, /* data=*/ 7, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_6x13_tf);
  u8g2.setFontMode(1);
  u8g2.setDrawColor(2);
  u8g2.setBitmapMode(1);
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LATCH, INPUT_PULLUP);
  pinMode(BEEP, OUTPUT);

  drawscreen(1);
  beep();

  do {                 // teken het handleidingsscherm
    drawscreen(2);
  } while (digitalRead(UP));

  drawscreen(3);
  delay(500);

  while (keuze == 0) {               // teken het keuzescherm
    if (!digitalRead(DOWN)) {
      keuze = 123;
    } else if (!digitalRead(UP)) {
      keuze = 125;
    }
  }
  zoekontvanger(keuze);
  beep();
}

void loop() {
  if (fails >= 9) {
    screentodraw = 9;
    sendcode();
    CODE = 000;

    if (fails < 12) {
      lost = millis();
      beep();
    }

    if ((millis() - lost) >= 58000) {
      verbonden = false;
      fails = 1;
      zoekontvanger(keuze);
    }
  } else if (!digitalRead(UP)) { //als er op de groene knop wordt gedrukt, ga dan omhoog (kantelen)
    if (modus == true) {
      CODE = codeping.omhoog;
      sendcode();
      screentodraw = 5;
    } else {
      CODE = codeping.omhoog_k;
      sendcode();
      screentodraw = 7;
    }
    sendcode();

  } else if (!digitalRead(DOWN)) {//als er op de rode knop wordt gedrukt, ga dan omlaag (kantelen)
    if (modus == true) {
      CODE = codeping.omlaag;
      screentodraw = 6;
    } else {
      CODE = codeping.omlaag_k;
      screentodraw = 8;
    }
    sendcode();

  } else {                        // als er niets gebeurd;
    if(modus != digitalRead(LATCH)){ // zet dan de modus goed
     modus =  digitalRead(LATCH);
     beep();                         // beep als de modus wisselt
    }
    CODE = 000;                   // en stuur een lege code zodat de ontvanger weet dat je er nog bent
    sendcode();
    screentodraw = 4;
  }
  sendcode();
  drawscreen(screentodraw);
  sendcode();
  //Serial.println(CODE);
}
