extern const char vrachtwagen_bits[];
extern const char startup_bits[];
extern const char QR_bits[];

void drawscreen(byte scherm) {
  u8g2.firstPage();
  do {
    switch (scherm) {
      case 1:
        u8g2.drawXBMP( 0, 0, 128, 64, startup_bits);
        break;

      case 2:
        if ((millis() / 4000) % 2) {
          u8g2.drawStr(11, 13, "Druk op");
          u8g2.drawStr(0, 28, "groene knop");
          u8g2.drawStr(11, 43, "om door");
          u8g2.drawStr(11, 58, "te gaan");
        } else {
          u8g2.drawStr(5, 24, "Scan voor");
          u8g2.drawStr(0, 39, "handleiding");
        }
        u8g2.drawXBMP( 70, 0, 58, 58, QR_bits);
        break;

      case 3:
        u8g2.drawStr(9, 13, "Verbind zender met:");
        u8g2.drawBox(0, 0, 128, 17);
        u8g2.drawRFrame(5, 22, 120, 20, 7);
        u8g2.drawRFrame(5, 44, 120, 20, 7);
        u8g2.drawStr(11, 36, "Groen: Vrachtwagen");
        u8g2.drawStr(11, 58, "Rood:  Bus");
        break;

      case 4:
        u8g2.drawBox(0, 2, 100, 13);
        u8g2.drawStr(4, 13, "Verbonden met:");
        if (voertuig == true) {
          u8g2.drawStr(8, 28, "Vrachtwagen");
        } else {
          u8g2.drawStr(8, 28, "Bus");
        }

        u8g2.drawBox(0, 35, 100, 13);
        u8g2.drawStr(4, 46, "Zender modus:");
        if (modus == true) {
          u8g2.drawStr(8, 64, "Omhoog/Omlaag");
        } else {
          u8g2.drawStr(8, 62, "Kantelen");
        }

        u8g2.drawVLine(100, 2 , 62);
        u8g2.drawXBMP( 106, 0, 29, 64, vrachtwagen_bits);
        break;

      case 5: //omhoog
        kar();
        u8g2.drawStr(1, 10, "Omhoog");
        u8g2.drawBox(0, 0, 91, 23);
        if (voertuig == true) {
          u8g2.drawStr(1, 20, "Vrachtwagen");
        } else {
          u8g2.drawStr(1, 20, "Bus");
        }

        u8g2.drawXBMP( 99, 0, 29, 64, vrachtwagen_bits);

        switch ((millis() / 750) % 3) {
          case 0:
            u8g2.drawTriangle(45, 58, 84, 64, 90, 58);
            break;

          case 1:
            u8g2.drawTriangle(45, 43, 84, 51, 90, 43);
            break;

          case 2:
            u8g2.drawTriangle(45, 28, 84, 36, 90, 28);
            break;
        }
        break;

      case 6: //omlaag
        kar();
        u8g2.drawStr(1, 10, "Omlaag");
        u8g2.drawBox(0, 0, 91, 23);
        if (voertuig == true) {
          u8g2.drawStr(1, 20, "Vrachtwagen");
        } else {
          u8g2.drawStr(1, 20, "Bus");
        }

        u8g2.drawXBMP( 99, 0, 29, 64, vrachtwagen_bits);

        switch ((millis() / 750) % 3) {
          case 0:
            u8g2.drawTriangle(45, 28, 84, 36, 90, 28);
            break;

          case 1:
            u8g2.drawTriangle(45, 43, 84, 51, 90, 43);
            break;

          case 2:
            u8g2.drawTriangle(45, 58, 84, 64, 90, 58);
            break;
        }
        break;

      case 7: //omhoog_k
        kar();
        u8g2.drawStr(1, 10, "Omhoog kantelen");
        u8g2.drawBox(0, 0, 91, 23);
        if (voertuig == true) {
          u8g2.drawStr(1, 20, "Vrachtwagen");
        } else {
          u8g2.drawStr(1, 20, "Bus");
        }

        u8g2.drawXBMP( 99, 0, 29, 64, vrachtwagen_bits);

        switch ((millis() / 750) % 3) {
          case 0:
            u8g2.drawTriangle(50, 53, 81, 57, 90, 43);
            break;

          case 1:
            u8g2.drawTriangle(45, 43, 84, 54, 90, 43);
            break;

          case 2:
            u8g2.drawTriangle(50, 33, 77, 51, 90, 43);
            break;
        }
        break;

      case 8: //omlaag_k
        kar();
        u8g2.drawStr(1, 10, "Omlaag kantelen");
        u8g2.drawBox(0, 0, 91, 23);
        if (voertuig == true) {
          u8g2.drawStr(1, 20, "Vrachtwagen");
        } else {
          u8g2.drawStr(1, 20, "Bus");
        }

        u8g2.drawXBMP( 99, 0, 29, 64, vrachtwagen_bits);

        switch ((millis() / 750) % 3) {
          case 0:
            u8g2.drawTriangle(50, 33, 77, 51, 90, 43);
            break;

          case 1:
            u8g2.drawTriangle(45, 43, 84, 54, 90, 43);
            break;

          case 2:
            u8g2.drawTriangle(50, 53, 81, 57, 90, 43);
            break;
        }
        break;

      case 9:
        if ((millis() / 2000) % 2) {
          u8g2.drawBox(0, 0, 128, 64);
        }

        u8g2.drawBox(0, 0, 128, 15);
        u8g2.drawStr(15, 11, "Verbing verloren");
        String msg = "Nog: ";
        msg += 60 - ((millis() - lost) / 1000);
        msg += " Seconden";
        u8g2.setCursor(15, 30);
        u8g2.print(msg);
        u8g2.drawStr(17, 45, "tot automatisch");
        u8g2.drawStr(25, 60, "herverbinden");
    }
  } while ( u8g2.nextPage() );
}
