#include "SPI.h"
#include "NRFLite.h"

#define UP 7
#define DOWN 6
#define KUP 4
#define KDOWN 5
#define UPLED A1
#define DOWNLED A2
#define ERRLED A0
#define VOERTUIG 125
#define PIN_RADIO_CE  9
#define PIN_RADIO_CSN  10

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

NRFLite _radio;

void setup() {
  Serial.begin(9600);
  pinMode(UP, OUTPUT);
  digitalWrite(UP, HIGH);

  pinMode(KUP, OUTPUT);
  digitalWrite(KUP, HIGH);

  pinMode(DOWN, OUTPUT);
  digitalWrite(DOWN, HIGH);

  pinMode(KDOWN, OUTPUT);
  digitalWrite(KDOWN, HIGH);

  pinMode(UPLED, OUTPUT);
  pinMode(DOWNLED, OUTPUT);
  pinMode(ERRLED, OUTPUT);

  setinterrupt();

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
    vindconectie();
  }

  while (_radio.hasData()) {
    _radio.readData(&CODE);
  }

  if (CODE == codeping.omhoog && (BUSY == 0 || BUSY == 1)) { //kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    done();
    digitalWrite(UP, LOW);
    digitalWrite(UPLED, HIGH);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 1;
    CODE = 1;
  }
  else if (CODE == codeping.omlaag && (BUSY == 0 || BUSY == 2)) {//kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    done();
    digitalWrite(DOWN, LOW);
    digitalWrite(DOWNLED, HIGH);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 2;
    CODE = 1;
  }
  else if (CODE == codeping.omhoog_k && (BUSY == 0 || BUSY == 3)) {//kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    done();
    digitalWrite(KUP, LOW);
    digitalWrite(UPLED, HIGH);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 3;
    CODE = 1;
  }
  else if (CODE == codeping.omlaag_k && (BUSY == 0 || BUSY == 4)) {//kan alleen aan als er niets andes aanstaat en z'n code wordt verzonden
    done();
    digitalWrite(KDOWN, LOW);
    digitalWrite(DOWNLED, HIGH);
    RECIVETIME = millis();
    RECIVE = millis();
    BUSY = 4;
    CODE = 1;
  } else if (CODE == 000) {
    RECIVE = millis();
    CODE = 1;
  }

  if (CHECKTIME) {
    checktime();
  }
}
