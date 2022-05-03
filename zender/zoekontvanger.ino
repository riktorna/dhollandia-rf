void zoekontvanger(byte voertuig) {

  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN, NRFLite::BITRATE2MBPS, voertuig))
  {
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
  Serial.println("start met zoeken");
  
  do {
    while (_radio.hasData()) {
      _radio.readData(&codeping);
    }
   Serial.println("zoeken");
   
    if (codeping.zoekzender == true) {
      _radio.send(DESTINATION_RADIO_ID, &codeping, sizeof(codeping));

      verbonden = true;
      Serial.println("gevonden");
    }
    delay(50);
  } while (!verbonden);
}
