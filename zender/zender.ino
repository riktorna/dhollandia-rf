#include "SPI.h"
#include "NRFLite.h"
#include <U8g2lib.h>
#include <Wire.h>

#define UP 5
#define DOWN 6
#define LATCH 2
#define BEEP 3

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

const static uint8_t RADIO_ID = 1;
const static uint8_t DESTINATION_RADIO_ID = 0;

const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;
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
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 8, /* data=*/ 7, /* reset=*/ 2);

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  pinMode(UP, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LATCH, INPUT_PULLUP);

  drawscreen(1);
  tone(BEEP, 500, 250);
  delay(500);
  tone(BEEP, 500, 250);
  delay(500);

  do {
    drawscreen(2);
  } while (digitalRead(UP));

  zoekontvanger(125);
  tone(BEEP, 500, 250);
  delay(500);
  tone(BEEP, 500, 250);
}

void loop() {

  /*if (fails >= 10) {
    
      drawscreen(9);
       sendcode();
      if ((millis() - lost) >= 60000) {
        zoekontvanger(125);
      }
  } else */if (!digitalRead(UP)) {
    if (modus == true) {
      CODE = codeping.omhoog;
      drawscreen(5);
    } else {
      CODE = codeping.omhoog_k;
      drawscreen(7);
    }
    sendcode();

  } else if (!digitalRead(DOWN)) {
    if (modus == true) {
      CODE = codeping.omlaag;
      drawscreen(6);
    } else {
      CODE = codeping.omlaag_k;
      drawscreen(8);
    }
    sendcode();

  } else {
    modus = digitalRead(LATCH);
    CODE = 000;
    sendcode();
    drawscreen(4);
  }
  delay(50);
  Serial.println(CODE);
}

void sendcode() {
  if (_radio.send(DESTINATION_RADIO_ID, &CODE, sizeof(CODE))) // 'send' puts the radio into Tx mode.
  {
    Serial.println("...Success");
   /* if (fails >= 0) {
      fails = fails--;
    }*/
  }
  else
  {
    Serial.println("...Failed");
   /* fails = fails++;
    lost = millis();*/
  }
  Serial.println(CODE);
}
