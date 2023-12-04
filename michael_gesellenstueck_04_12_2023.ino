#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS 10
#define TFT_RST 9  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 8

#define TFT_MOSI 11  // Data out
#define TFT_SCLK 13  // Clock out

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


#define PIN_NEO_PIXEL 7  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 20    // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);


                                                                               //Spieler
                                                                              //Spieler 1
int player = 1;
int player_1_positions[] = { 0, 1, 2, 3 };
int player_1_boards[] = { 0, 0, 0, 0 };
int player_1_positions_old[] = { 0, 1, 2, 3 };
int player_1_boards_old[] = { 0, 0, 0, 0 };
int player_1_farbe[] = { 100, 0, 0 };
int player_1_joystick = A3;
int player_1_farbe_mit_cursor[] = { 100, 0, 0 };
                                                                              //cursor
int cursor = 10;
int cursor_with_player_charakter = 0;
int t;

void setup() {
  pinMode(A0, INPUT);
  pinMode(6, INPUT);
  NeoPixel.begin();
  tft.init(240, 280);                                                         //Display mit pixel maße initialisieren
  tft.fillScreen(ST77XX_BLACK);                                               //Hintergrundfarbe einstellen
  tft.setCursor(0, 0);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);                                             //Text Farbe einstellen
  tft.print("Lass uns beginnen");                                             //Text ausgeben
  Serial.begin(9600);
  delay(1000);
}

int anzeigen(int pixel, int tier, int dir) {                                   //Funktion für das Anzeigen verschiedener Situationen
  int r;
  int g;
  int b;
  if (tier == 0 && dir == 1) {
    r = 10;
    g = 10;
    b = 10;
    NeoPixel.setPixelColor(pixel - 1, NeoPixel.Color(0, 0, 0));
    NeoPixel.show();
  }
  if (tier == 0 && dir == 0) {
    r = 10;
    g = 10;
    b = 10;
    NeoPixel.setPixelColor(pixel + 1, NeoPixel.Color(0, 0, 0));
    NeoPixel.show();
  }
  if (tier == 1) {                                                              //Spieler 1 Charakter anzeigen
    r = player_1_farbe[0];
    g = player_1_farbe[1];
    b = player_1_farbe[2];
  }
  if (tier == 2) {                                                              //Cursor anzeigen mit Spieler 1 Charakter
    r = player_1_farbe_mit_cursor[0];
    g = player_1_farbe_mit_cursor[1];
    b = player_1_farbe_mit_cursor[2];
  }
  if (tier == 5) {
    r = 0;
    g = 0;
    b = 10;
  }
  if (tier == 6) {
    r = 0;
    g = 10;
    b = 0;
  }
  if (tier == 10) {
    r = 0;
    g = 10;
    b = 0;
  }

  NeoPixel.setPixelColor(pixel, NeoPixel.Color(r, g, b));
  NeoPixel.show();
}
int wuerfel() {
  int wuerfel_nummer = random(1, 6);
  tft.setCursor(0, 0);
  tft.setTextColor("ST77XX_WHITE");
  tft.setTextWrap(true);
  tft.print(wuerfel_nummer);
  return NULL;
}


int curser(cursor_with_player_charakter, player_Joystick, curser_mit_spieler) {
                                                                                        //bewegen des cursers
  int Joystick = analogRead(player_Joystick);
                                                                                        //bewegung hoch
  if (Joystick >= 800) {
    cursor = cursor + 1;
    if (cursor_with_player_charakter == 0) {
      anzeigen(cursor, 0, 1);                                                           //0 bedeutet richtung hoch, das ist die Variable Dir in der Funktion Anzeigen
    }
    else if (cursor_with_player_charakter == 1) {
      anzeigen(cursor, curser_mit_spieler, 1);                                          //0 bedeutet richtung hoch, das ist die Variable Dir in der Funktion Anzeigen
    }
    while (Joystick >= 700) {
      Joystick = analogRead(player_Joystick);                                           //Achten das Joystick seine Grundposition erreicht hat
    }
  }
                                                                                        //bewegen runter
  else if (Joystick <= 300) {
    cursor = cursor - 1;
    if (cursor_with_player_charakter == 0) {
      anzeigen(cursor, 0, 0);                                                           //0 bedeutet richtung runter, das ist die Variable Dir in der Funktion Anzeigen
    }
    else if (cursor_with_player_charakter == 1) {
      anzeigen(cursor, curser_mit_spieler, 0);                                          //0 bedeutet richtung runter, das ist die Variable Dir in der Funktion Anzeigen
    }
    while (Joystick <= 400) {
      Joystick = analogRead(player_Joystick);
    }
  }
}

int player_driver(int player) {
  for (int i = 0; i <= 3; i++) {
                                                                                         // anzeigen anderer farbe wenn cursor über spieler
    if (cursor == player_positions[i]) {
      anzeigen(cursor, 5, 2);
    } else {
      //anzeigen der Spieler
      anzeigen(player_positions[i], player, NULL);
    }
  }

  int oldmyTime = millis();
  while (digitalRead(6) == HIGH) {
    int myTime = millis() - oldmyTime;
    if (myTime >= 100) {
                                                                                           //Charakter aufnahme
      for (int i = 0; i <= 3; i++) {
        if (cursor == player_positions[i] && cursor_with_player_charakter == 0) {
          t = i;
          anzeigen(player_positions[i], 10, NULL);
          cursor_with_player_charakter = 1;
          break;
        }
                                                                                            //Setzten des Charakters
        else if (cursor != player_positions[i] && cursor_with_player_charakter == 1) {
          player_positions[t] = cursor;
          cursor_with_player_charakter = 0;
          player = player + 1;
          break;
        }
      }
      while (digitalRead(6) == HIGH) {                                                      //Sodass es nicht dauernd, solange der Taster gedrückt ist, ausgeführt wird
      }
      break;
    }
  }
}

int nachfrage_und_update(int player) {
  if (player = 1) {                                                                                     // Wenn Spieler 1 an der Reihe ist
    for (int i = 0; i <= 3; i++) {
      player_positions[i] = player_1_positions_old[i];                                                  //Relevante Positionen werden aufgerufen
    }
    while (player = 1) {
      curser(cursor_with_player_charakter, player_1_joystick, 2[]);                                     
      player_driver(player);
    }
  }
}

void loop() {
  wuerfel();
  nachfrage_und_update(player);
}
