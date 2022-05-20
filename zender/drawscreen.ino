extern const char startup_bits[];
extern const char doorgaan_bits[];
extern const char scan_bits[];
extern const char verbind_bits[];
extern const char home_bits[];
extern const char hooglaagl_bits[];
extern const char hooglaagh_bits[];
extern const char absmidden_bits[];
extern const char kantelenl_bits[];
extern const char kantelenh_bits[];
extern const char verbinding_bits[];

void drawscreen(byte scherm) {
  u8g2.clearBuffer();
  switch (scherm) {
    case 1:
      u8g2.drawXBMP( 0, 0, 128, 64, startup_bits);
      break;

    case 2:
      if ((millis() / 4000) % 2) {
        u8g2.drawXBMP( 0, 0, 128, 64, doorgaan_bits);
      } else {
        u8g2.drawXBMP( 0, 0, 128, 64, scan_bits);
      }
      break;

    case 3:
      u8g2.drawXBMP( 0, 0, 128, 64, verbind_bits);
      break;

    case 4:
      u8g2.drawXBMP( 0, 0, 128, 64, home_bits);
      if (voertuig == false) {
        u8g2.drawStr(8, 28, "Vrachtwagen");
      } else {
        u8g2.drawStr(8, 28, "Bus");
      }
      if (modus == true) {
        u8g2.drawStr(8, 62, "Omhoog/Omlaag");
      } else {
        u8g2.drawStr(8, 62, "Kantelen");
      }
      break;

    case 5: //omhoog
      u8g2.drawStr(1, 10, "Omhoog");
      if (voertuig == false) {
        u8g2.drawStr(1, 20, "Vrachtwagen");
      } else {
        u8g2.drawStr(1, 20, "Bus");
      }

      switch ((millis() / 750) % 3) {
        case 0:
          u8g2.drawXBMP( 0, 0, 128, 64, hooglaagl_bits);
          break;

        case 1:
          u8g2.drawXBMP( 0, 0, 128, 64, absmidden_bits);
          break;

        case 2:
          u8g2.drawXBMP( 0, 0, 128, 64, hooglaagh_bits);
          break;
      }
      break;

    case 6: //omlaag
      u8g2.drawStr(1, 10, "Omlaag");
      if (voertuig == false) {
        u8g2.drawStr(1, 20, "Vrachtwagen");
      } else {
        u8g2.drawStr(1, 20, "Bus");
      }

      switch ((millis() / 750) % 3) {
        case 0:
          u8g2.drawXBMP( 0, 0, 128, 64, hooglaagh_bits);
          break;

        case 1:
          u8g2.drawXBMP( 0, 0, 128, 64, absmidden_bits);
          break;

        case 2:
          u8g2.drawXBMP( 0, 0, 128, 64, hooglaagl_bits);
          break;
      }
      break;

    case 7: //omhoog_k
      u8g2.drawStr(1, 10, "Omhoog kantelen");
      if (voertuig == false) {
        u8g2.drawStr(1, 20, "Vrachtwagen");
      } else {
        u8g2.drawStr(1, 20, "Bus");
      }

      switch ((millis() / 750) % 3) {
        case 0:
          u8g2.drawXBMP( 0, 0, 128, 64, kantelenl_bits);
          break;

        case 1:
          u8g2.drawXBMP( 0, 0, 128, 64, absmidden_bits);
          break;

        case 2:
          u8g2.drawXBMP( 0, 0, 128, 64, kantelenh_bits);
          break;
      }
      break;

    case 8: //omlaag_k
      u8g2.drawStr(1, 10, "Omlaag kantelen");
      if (voertuig == false) {
        u8g2.drawStr(1, 20, "Vrachtwagen");
      } else {
        u8g2.drawStr(1, 20, "Bus");
      }

      switch ((millis() / 750) % 3) {
        case 0:
          u8g2.drawXBMP( 0, 0, 128, 64, kantelenh_bits);
          break;

        case 1:
          u8g2.drawXBMP( 0, 0, 128, 64, absmidden_bits);
          break;

        case 2:
          u8g2.drawXBMP( 0, 0, 128, 64, kantelenl_bits);
          break;
      }
      break;

    case 9:
      if ((millis() / 2000) % 2) {
        u8g2.drawBox(0, 0, 128, 64);
      }

      String msg = "Nog: ";
      msg += 60 - ((millis() - lost) / 1000);
      msg += " Seconden";
      u8g2.setCursor(15, 30);
      u8g2.print(msg);
      u8g2.drawXBMP( 0, 0, 128, 64, verbinding_bits);
  }
  u8g2.sendBuffer();
}
