    void done() {         //alles uit
      digitalWrite(UP, HIGH);
      digitalWrite(DOWN, HIGH);
      digitalWrite(UPLED, LOW);
      digitalWrite(DOWNLED, LOW);
      CODE = 000;
      BUSY = 0;
    }

void checktime(){
  if (BUSY != 0 && (millis() - RECIVETIME) > 520) { //elke halve seconde wordt alles uitgezet als er ondertussen niet is ontvangen.
      done();
      Serial.print("done");
    }

    /* if ((millis() - RECIVE) >= 60000) {
       verbonden = false;
      }*/

    CHECKTIME = false;
    digitalWrite(ERRLED, HIGH);    // geef de status door aan de seriele poort en laat het lampje knipperen zodat je weet dat het aanstaat.
    Serial.print("RECIVETIME: ");
    Serial.println(RECIVETIME);
    Serial.print("millis: ");
    Serial.println(millis());
    digitalWrite(ERRLED, LOW);
}
