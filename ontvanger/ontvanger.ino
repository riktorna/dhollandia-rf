#include "SPI.h"
#include "NRFLite.h"

#define UP 7
#define DOWN 6
#define UPLED A1
#define DOWNLED A2
#define ERRLED A0
#define VOERTUIG 125

const static int RADIO_ID = 0;
const static int DESTINATION_RADIO_ID = 1;

struct zendblok1
{
  bool zoekzender;
  int omhoog;
  int omlaag;
  int omhoog_k;
  int omlaag_k;
};

zendblok1 codeping;
bool verbonden = false;
volatile bool CHECKTIME;
byte BUSY = 0;
long RECIVETIME = 0;
long RECIVE = 0;
int CODE = 0;

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
  pinMode(UP, OUTPUT);
  pinMode(DOWN, OUTPUT);
  pinMode(UPLED, OUTPUT);
  pinMode(DOWNLED, OUTPUT);
  pinMode(ERRLED, OUTPUT);
  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0
  TCCR1B = 0;                 // Reset entire TCCR1B to 0

  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */
  TCCR1B |= B00000100;

  /*3. We enable compare match mode on register A*/
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A

  /*4. Set the value of register A to 31250*/
  OCR1A = 62500;             //Finally we set compare register A to this value
  sei();                     //Enable back the interrupts

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, 125))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
  digitalWrite(ERRLED, HIGH);
  vindconectie();
}

ISR(TIMER1_COMPA_vect) {
  TCNT1  = 0;                  //First, set the timer back to 0 so it resets for next interrupt
  CHECKTIME = true;
}

void loop() {
  if (!verbonden) {
    digitalWrite(ERRLED, HIGH); // als de vebinding is verloren gaar de gele led aan en probert hij te herverbinden
    /* vindconectie();*/
  }

  while (_radio.hasData()) {
    _radio.readData(&CODE);
  }

  if (CODE == codeping.omhoog && (BUSY == 0 || BUSY == 1)) { //kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    digitalWrite(UP, HIGH);
    digitalWrite(UPLED, HIGH);
    digitalWrite(DOWN, LOW);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 1;
    CODE = 1;
  }
  else if (CODE == codeping.omlaag && (BUSY == 0 || BUSY == 2)) {//kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    digitalWrite(DOWN, HIGH);
    digitalWrite(DOWNLED, HIGH);
    digitalWrite(UP, LOW);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 2;
    CODE = 1;
  } else if (CODE == 000) {
    RECIVE = millis();
    CODE = 1;
  }

  if (CHECKTIME) {
    if (BUSY != 0 && (millis() - RECIVETIME) >= 300) { //elke halve seconde wordt alles uitgezet als er ondertussen niet is ontvangen.
      done();
      Serial.print("done");
    }

    /* if ((millis() - RECIVE) >= 60000) {
       verbonden = false;
      }*/

    CHECKTIME = false;
    Serial.print("RECIVETIME: ");
    Serial.println(RECIVETIME);
    Serial.print("millis: ");
    Serial.println(millis());
  }
}
