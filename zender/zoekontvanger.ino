void zoekontvanger(byte voertuig) {

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE250KBPS, voertuig))
  {
    Serial.println(F("Cannot communicate with radio"));
    while (1); // Wait here forever.
  }
  Serial.println(F("start met zoeken"));
  
  do {                                // luister of er iemand ping's uitzend
    while (_radio.hasData()) {
      _radio.readData(&codeping);
    }
   Serial.println(F("zoeken"));
   
    if (codeping.zoekzender == true) {
      _radio.send(DESTINATION_RADIO_ID, &codeping, sizeof(codeping)); //stuur de ping terug om normale operatie te starten

      verbonden = true;  
      Serial.println(F("gevonden"));
    }
    delay(50);
  } while (!verbonden);
}
