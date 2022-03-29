#include "SPI.h"
#include "NRFLite.h"

#define UP 7
#define DOWN 6

int CODE = 000;

struct zendblok
{
  bool zoekzender;
  int omhoog;
  int omlaag;
  int omhoog_l;
  int omlaag_l;
};

zendblok codeping;
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

void setup() {
  Serial.begin(9600);
  
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
    
    pinMode(UP, INPUT_PULLUP);
    pinMode(DOWN, INPUT_PULLUP);
  }

  void loop() {

    if (!digitalRead(UP)) {
      CODE = 211;
      sendcode();
    } else if (!digitalRead(DOWN)) {
      CODE = 112;
      sendcode();
    } else{
      CODE = 000;
      sendcode();
    }
  //  delay(50);
    Serial.println(CODE);
  }

  void sendcode() {
    if (_radio.send(DESTINATION_RADIO_ID, &CODE, sizeof(CODE))) // 'send' puts the radio into Tx mode.
    {
        Serial.println("...Success");
    }
    else
    {
        Serial.println("...Failed");
    }
    Serial.println(CODE);
    CODE = 000;
  }
