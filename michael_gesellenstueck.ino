#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
#include <SPI.h>

#define TFT_CS 10
#define TFT_RST 9  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC  8

#define TFT_MOSI 11  // Data out
#define TFT_SCLK 13  // Clock out

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);


#define PIN_NEO_PIXEL 7  // Arduino pin that connects to NeoPixel
#define NUM_PIXELS 20    // The number of LEDs (pixels) on NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

//Spieler
int player = 1;
int player_1_positions[] = { 0, 1, 2, 3 };
int player_1_boards[] = { 0, 0, 0, 0 };
int player_1_positions_old[] = { 0, 1, 2, 3 };
int player_1_boards_old[] = { 0, 0, 0, 0 };
int player_1_farbe[] = { 100, 0, 0 };

//cursor
int cursor = 10;
int cursor_with_player_charakter;
int t;

void setup() {
  pinMode(A0, INPUT);
  pinMode(6, INPUT);
  NeoPixel.begin();
  tft.init(240, 280);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextWrap(true);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.print("Lass uns beginnen");
  Serial.begin(9600);
  delay(1000);
}

int anzeigen(int pixel, int player, int dir) {
  int r;
  int g;
  int b;
  if (player == 0 && dir == 1) {
    r = 10;
    g = 10;
    b = 10;
    NeoPixel.setPixelColor(pixel - 1, NeoPixel.Color(0, 0, 0));
    NeoPixel.show();
  }
  if (player == 0 && dir == 0) {
    r = 10;
    g = 10;
    b = 10;
    NeoPixel.setPixelColor(pixel + 1, NeoPixel.Color(0, 0, 0));
    NeoPixel.show();
  }
  if (player == 1) {
    r = player_1_farbe[0];
    g = player_1_farbe[1];
    b = player_1_farbe[2];
  }
  if (player == 5) {
    r = 0;
    g = 10;
    b = 0;
  }
  if (player == 6) {
    r = 0;
    g = 0;
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
int curser(int player) {
  while (1) {
    if (player = 1) {
      //bewegen des cursers
      int Joystick = analogRead(A0);
      Serial.println(analogRead(A0));
      //bewegung hoch
      if (Joystick >= 800) {
        cursor = cursor + 1;
        anzeigen(cursor, 0, 1);
        while (Joystick >= 700) {
          Joystick = analogRead(A0);
        }
      }
      //bewegen runter
      else if (Joystick <= 300) {
        cursor = cursor - 1;
        anzeigen(cursor, 0, 0);
        while (Joystick <= 400) {
          Joystick = analogRead(A0);
        }
      }
      //anzeigen der Spieler
      for (int i = 0; i <= 3; i++) {
        int d = player_1_positions_old[i];
        Serial.println(d);
        anzeigen(d, player, NULL);
      }
      // anzeigen anderer farbe wenn cursor über spieler
      for (int i = 0; i <= 3; i++) {
        if (cursor == player_1_positions_old[i]) {
          anzeigen(cursor, 5, 2);
        }
      }

      Serial.println(digitalRead(6));
      if (digitalRead(6) == HIGH) {
        //Charakter aufnahme
        for (int i = 0; i <= 3; i++) {
          if (cursor == player_1_positions_old[i] && cursor_with_player_charakter == 0) {
            t = i;
            cursor_with_player_charakter = 1;
            break;
          } else if (cursor != player_1_positions_old[i] && cursor_with_player_charakter == 1) {
            player_1_positions_old[t] = cursor;
            cursor_with_player_charakter = 0;
            break;
          }
          //was wenn cursor nicht auf feld
          else if (cursor != player_1_positions_old[i] && cursor_with_player_charakter == 0) {
            anzeigen(cursor, 5, 2);
            cursor_with_player_charakter = 0;
          }
          //Spieler setzten
        }
        while (digitalRead(6) != HIGH) {
        }
      }
    }
  }
}


void nachfrage_und_update(int player) {
  if (player == 1) {
    curser(player);
  }
}

void loop() {
  wuerfel();
  nachfrage_und_update(player);
}
