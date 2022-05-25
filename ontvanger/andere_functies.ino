void done() {         //alles uit
  digitalWrite(UP, HIGH);
  digitalWrite(DOWN, HIGH);
  digitalWrite(KUP, HIGH);
  digitalWrite(KDOWN, HIGH);
  digitalWrite(UPLED, LOW);
  digitalWrite(DOWNLED, LOW);
  CODE = 000;
  BUSY = 0;
}

void checktime() {
  if (BUSY != 0 && (millis() - RECIVETIME) > 600) { //elke halve seconde wordt alles uitgezet als er ondertussen niet is ontvangen.
    done();
    Serial.print("done");
  }

  if ((millis() - RECIVE) >= 60000) { //automatisch herverbinden
    verbonden = false;
  }

  if ((millis() - RECIVE) >= 2000) {
    digitalWrite(UPLED, HIGH);
    digitalWrite(ERRLED, HIGH);
    digitalWrite(DOWNLED, HIGH);
  }else if ((millis() - RECIVETIME) > 600){
    digitalWrite(UPLED, LOW);
    digitalWrite(DOWNLED, LOW);
  }

  CHECKTIME = false;
  digitalWrite(ERRLED, HIGH);    // geef de status door aan de seriele poort en laat het lampje knipperen zodat je weet dat het aanstaat.
  Serial.print("RECIVETIME: ");
  Serial.println(RECIVETIME);
  Serial.print("millis: ");
  Serial.println(millis());
  digitalWrite(ERRLED, LOW);
}

void setinterrupt(){
  cli();                      //stop interrupts for till we make the settings
  /*1. First we reset the control register to amke sure we start with everything disabled.*/
  TCCR1A = 0;                 // Reset entire TCCR1A to 0
  TCCR1B = 0;                 // Reset entire TCCR1B to 0

  /*2. We set the prescalar to the desired value by changing the CS10 CS12 and CS12 bits. */
  TCCR1B |= B00000100;

  /*3. We enable compare match mode on register A*/
  TIMSK1 |= B00000010;        //Set OCIE1A to 1 so we enable compare match A

  /*4. Set the value of register A to 31250*/
  OCR1A = 35000;             //Finally we set compare register A to this value
  sei();                     //Enable back the interrupts
}
