void sendcode() {
  if (_radio.send(DESTINATION_RADIO_ID, &CODE, sizeof(CODE))) // 'send' puts the radio into Tx mode and sends the code
  {
    Serial.println(F("...Success"));
    if (fails > 0) {
      fails = fails--;
    }
  } else {
    Serial.println(F("...Failed"));
    fails = fails + 1;
  }
  Serial.println(fails);
}

void beep() {     // laat de buzzer horen zonder timer te gebruiken
  for (byte boop = 0; boop < 2; boop++) {
    for (int beep = 0; beep < 250; beep++) {
      digitalWrite(BEEP, HIGH);
      delay(1);
      digitalWrite(BEEP, LOW);
      delay(1);
    }
    delay(500);
  }
}
