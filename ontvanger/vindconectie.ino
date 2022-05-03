void vindconectie() {
  randomSeed(analogRead(A7));

  codeping.omhoog = random(2, 32767);  // 4 verschillende codes

  do {
    codeping.omlaag = random(2, 32767);
  } while (codeping.omlaag == codeping.omhoog);

  do {
    codeping.omhoog_k = random(2, 32767);
  } while (codeping.omhoog_k == codeping.omhoog || codeping.omhoog_k == codeping.omlaag );

  do {
    codeping.omlaag_k = random(2, 32767);
  } while (codeping.omlaag_k == codeping.omhoog || codeping.omlaag_k == codeping.omlaag || codeping.omlaag_k == codeping.omhoog_k);

  codeping.zoekzender = true;  
  Serial.println(codeping.omhoog);
  Serial.println("op zoek");

  long zendtijd = 0;
  verbonden = false;
  while (!verbonden) {
    if (millis() - zendtijd > 500) {
      zendtijd = millis();
      _radio.send(DESTINATION_RADIO_ID, &codeping, sizeof(codeping));
      Serial.println("ping");
    }

    zendblok1 reactie;
    while (_radio.hasData()) {
      _radio.readData(&reactie);
    }

    if ( codeping.omhoog == reactie.omhoog && codeping.omlaag == reactie.omlaag ) {
      verbonden = true;
      RECIVE = millis();
      Serial.println("verbonden");
      digitalWrite(ERRLED, LOW);
    }
  }
}
