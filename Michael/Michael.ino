#include <Adafruit_NeoPixel.h>       //Biblioteken einbinden 
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

int referenz[] = { 0, 1, 2, 3 };


#define PIN_0 19                     //Definieren des ausgabe Pins für Neopixel, Anzahl der Neopixel auf der PLatine
#define NUMPIXELS_0 18
Adafruit_NeoPixel pixels_0(NUMPIXELS_0, PIN_0, NEO_GRB + NEO_KHZ800);

int player_1_positions[] = { 0, 1, 2, 3 };              // Speichern der Posizionen, Standartfarbe, JoyStick und Platine von Spieler 1.
int player_1_boards[] = { 0, 0, 0, 0 };
int player_1_farbe[] = { 100, 0, 0 };
int player_1_joystick = 0;
int player_1_farbe_mit_cursor[] = { 100, 50, 50 };      // Farbe des Neopixel wenn Cursor auf Spieler ist


#define PIN_1 25                    //Definieren des ausgabe Pins für Neopixel, Anzahl der Neopixel auf der PLatine
#define NUMPIXELS_1 18
Adafruit_NeoPixel pixels_1(NUMPIXELS_1, PIN_1, NEO_GRB + NEO_KHZ800);

int player_2_positions[] = { 0, 1, 2, 3 };             // Speichern der Posizionen, Standartfarbe, JoyStick und Platine von Spieler 2.
int player_2_boards[] = { 1, 1, 1, 1 };
int player_2_farbe[] = { 100, 0, 0 };
int player_2_joystick = 18;
int player_2_farbe_mit_cursor[] = { 100, 50, 50 };     // Farbe des Neopixel wenn Cursor auf Spieler ist


#define PIN_2 27                    //Definieren des ausgabe Pins für Neopixel, Anzahl der Neopixel auf der PLatine
#define NUMPIXELS_2 18
Adafruit_NeoPixel pixels_2(NUMPIXELS_2, PIN_2, NEO_GRB + NEO_KHZ800);

int player_3_positions[] = { 0, 1, 2, 3 };             // Speichern der Posizionen, Standartfarbe, JoyStick und Platine von Spieler 3.
int player_3_boards[] = { 2, 2, 2, 2 };
int player_3_farbe[] = { 100, 0, 0 };
int player_3_joystick = 16;
int player_3_farbe_mit_cursor[] = { 100, 50, 50 };     // Farbe des Neopixel wenn Cursor auf Spieler ist


#define PIN_3 26                    //Definieren des ausgabe Pins für Neopixel, Anzahl der Neopixel auf der PLatine
#define NUMPIXELS_3 18
Adafruit_NeoPixel pixels_3(NUMPIXELS_3, PIN_3, NEO_GRB + NEO_KHZ800);

int player_4_positions[] = { 0, 1, 2, 3 };               // Speichern der Posizionen, Standartfarbe, JoyStick und Platine von Spieler 4.
int player_4_boards[] = { 3, 3, 3, 3 };
int player_4_farbe[] = { 100, 0, 0 };
int player_4_joystick = 17;
int player_4_farbe_mit_cursor[] = { 100, 50, 50 };       // Farbe des Neopixel wenn Cursor auf Spieler ist


#define TFT_RST 13  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 12
#define TFT_MOSI 21  // Data out
#define TFT_SCLK 22  // Clock out

Adafruit_ST7789 tft = Adafruit_ST7789(32, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

int spieler = 1;                                         //Definition jeglicher Variabeln

int player_button = 15;

int saved_position;

int cursor = 2;
int cursor_b = 0;

int cursor_saved = cursor;
bool cursor_with_player_charakter = false;

int gewuerfelte_zahl = 0;
int marker = 0;
int marker_b = 5;

int r = 0;
int g = 0;
int b = 0;

int test_W = 0;
void setup() {

  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  pinMode(14, INPUT);

  pixels_0.begin();                         //Starten der Pixel 
  pixels_1.begin();
  pixels_2.begin();
  pixels_3.begin();

  pinMode(player_1_joystick, OUTPUT);       //Definition für ansteuern der JoyStick´s
  pinMode(player_2_joystick, OUTPUT);
  pinMode(player_3_joystick, OUTPUT);
  pinMode(player_4_joystick, OUTPUT);
  tft.init(240, 280);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextWrap(true);
  tft.setTextSize(3);
  tft.setCursor(20, 20);
  tft.println("Michael E.");
  tft.setCursor(20, 60);
  tft.println("Tristan B.");
  tft.setCursor(20, 100);
  tft.println("Schmidt+Bartl");
  tft.setTextSize(15);
  tft.setTextColor(ST77XX_BLACK);
  delay(1000);

  for (int i = 0; i < NUMPIXELS_0; i++) {
    pixels_0.setPixelColor(i, pixels_0.Color(0, 0, 0));
    pixels_0.show();
    pixels_1.setPixelColor(i, pixels_1.Color(0, 0, 0));
    pixels_1.show();
    pixels_2.setPixelColor(i, pixels_2.Color(0, 0, 0));
    pixels_2.show();
    pixels_3.setPixelColor(i, pixels_3.Color(0, 0, 0));
    pixels_3.show();
    delay(10);
  }

  Serial.begin(115200);
  Serial.print("hello");
  pinMode(player_button, INPUT);
  displays();
}

void wue() {                                //Funktion für zufällige Zahl Würfeln
  while (1) {
    if (digitalRead(14)) {
      gewuerfelte_zahl = random(1, 7);
      test_W = 1;
      while (digitalRead(14)) {
      }
      break;
      delay(50);
    }
  }
}
bool button(int button) {
  bool bt = 0;
  while (digitalRead(button)) {
    bt = true;
    delay(10);
  }
  return bt;
}

void curser() {                   

  if (spieler == 1) {                                           //Steuerung damit nur der Joystik des jeweiligen Spieler aktiv ist            
    digitalWrite(player_1_joystick, HIGH);
    digitalWrite(player_2_joystick, LOW);
    digitalWrite(player_3_joystick, LOW);
    digitalWrite(player_4_joystick, LOW);
  }
  if (spieler == 2) {
    digitalWrite(player_2_joystick, HIGH);
    digitalWrite(player_1_joystick, LOW);
    digitalWrite(player_3_joystick, LOW);
    digitalWrite(player_4_joystick, LOW);
  }
  if (spieler == 3) {
    digitalWrite(player_3_joystick, HIGH);
    digitalWrite(player_2_joystick, LOW);
    digitalWrite(player_1_joystick, LOW);
    digitalWrite(player_4_joystick, LOW);
  }
  if (spieler == 4) {
    digitalWrite(player_4_joystick, HIGH);
    digitalWrite(player_2_joystick, LOW);
    digitalWrite(player_3_joystick, LOW);
    digitalWrite(player_1_joystick, LOW);
  }
  int Joystick = analogRead(35);
  Serial.println(Joystick);
  //bewegen des cursers

  //bewegung hoch
  if (Joystick <= 800) {
    cursor = cursor - 1;
  }
  //bewegen runter
  else if (Joystick >= 3000) {
    cursor = cursor + 1;
  }

  if (cursor == 18) {                                            //Laufen des Cursors nach vorne und hinten mit PLatinen wechsel
    cursor = 0;
    cursor_b++;
    if (cursor_b == 4) {
      cursor_b = 0;
    }
  } else if (cursor == -1) {
    cursor = 17;
    cursor_b--;
    if (cursor_b == -1) {
      cursor_b = 3;
    }
  }
}

int eventhandler() {

  for (int j = 0; j <= 3; j++) {   //Wenn alle Figuren im Bahnhof des Spieler 1. sind, kann man nur mit einer 6 raus. Dies wird durch den Marker angezeigt 
    if (spieler == 1) {
      if (cursor == player_1_positions[j] && player_1_positions[j] <= 3 && cursor_b == player_1_boards[j] && gewuerfelte_zahl == 6) {  
        marker = 4;
        marker_b = cursor_b;
        for (int z = 0; z <= 3; z++) {
          if (player_1_boards[z] == marker_b) {
            if (player_1_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
      } else if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && cursor > 3) { //Anzeige des Marker wenn ein Spieler aus dem Bahnhof gelaufen ist (Spiler 1)
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor_b;
        if (marker >= 14 && marker_b != 3) {
          marker_b++;
          marker = marker - 10;
          if (marker_b == 4) {
            marker_b = 0;
          }
        } else {
        }
        for (int z = 0; z <= 3; z++) {
          if (player_1_boards[z] == marker_b) {
            if (player_1_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
        // hover
      } else if (cursor != player_1_positions[j] || cursor_b != player_1_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }

    else if (spieler == 2) {         //Wenn alle Figuren im Bahnhof des Spieler 2. sind, kann man nur mit einer 6 raus. Dies wird durch den Marker angezeigt 

      if (cursor == player_2_positions[j] && player_2_positions[j] <= 3 && cursor_b == player_2_boards[j] && gewuerfelte_zahl == 6) {
        marker = 4;
        marker_b = cursor_b;
        for (int z = 0; z <= 3; z++) {
          if (player_2_boards[z] == marker_b) {
            if (player_2_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
      } else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && cursor > 3) { //Anzeige des Marker wenn ein Spieler aus dem Bahnhof gelaufen ist (Spiler 2)
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor_b;
        if (marker >= 14 && marker_b != 0) {
          marker_b++;
          marker = marker - 10;
          if (marker_b == 4) {
            marker_b = 0;
          }
        } else {
        }
        if (player_2_boards[j] == marker_b) {
          if (player_2_positions[j] == marker) {
            return 0;
          }
        }
        for (int z = 0; z <= 3; z++) {
          if (player_2_boards[z] == marker_b) {
            if (player_2_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
        // hover
      } else if (cursor != player_2_positions[j] || cursor_b != player_2_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }

    // hover

    else if (spieler == 3) {          //Wenn alle Figuren im Bahnhof des Spieler 3. sind, kann man nur mit einer 6 raus. Dies wird durch den Marker angezeigt 
      
      if (cursor == player_3_positions[j] && player_3_positions[j] <= 3 && cursor_b == player_3_boards[j] && gewuerfelte_zahl == 6) {
        marker = 4;
        marker_b = cursor_b;
        for (int z = 0; z <= 3; z++) {
          if (player_3_boards[z] == marker_b) {
            if (player_3_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
      } else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && cursor > 3) { //Anzeige des Marker wenn ein Spieler aus dem Bahnhof gelaufen ist (Spiler 3)
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor_b;
        if (marker >= 14 && marker_b != 1) {
          marker_b++;
          marker = marker - 10;
          if (marker_b == 4) {
            marker_b = 0;
          }
        } else {
        }
        if (player_3_boards[j] == marker_b) {
          if (player_3_positions[j] == marker) {
            return 0;
          }
        }
        for (int z = 0; z <= 3; z++) {
          if (player_3_boards[z] == marker_b) {
            if (player_3_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
        // hover
      } else if (cursor != player_3_positions[j] || cursor_b != player_3_boards[j]) { 
        marker = 0;
        marker_b = 4;
      }
    }

    // hover


    else if (spieler == 4) {                    //Wenn alle Figuren im Bahnhof des Spieler 4. sind, kann man nur mit einer 6 raus. Dies wird durch den Marker angezeigt 
      
      if (cursor == player_4_positions[j] && player_4_positions[j] <= 3 && cursor_b == player_4_boards[j] && gewuerfelte_zahl == 6) {
        marker = 4;
        marker_b = cursor_b;
        for (int z = 0; z <= 3; z++) {
          if (player_4_boards[z] == marker_b) {
            if (player_4_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
      } else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && cursor > 3) { //Anzeige des Marker wenn ein Spieler aus dem Bahnhof gelaufen ist (Spiler 4)
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor_b;
        if (marker >= 14 && marker_b != 2) {
          marker_b++;
          marker = marker - 10;
          if (marker_b == 4) {
            marker_b = 0;
          }
        } else {
        }
        if (player_4_boards[j] == marker_b) {
          if (player_4_positions[j] == marker) {
            return 0;
          }
        }
        for (int z = 0; z <= 3; z++) {
          if (player_4_boards[z] == marker_b) {
            if (player_4_positions[z] == marker) {
              return 0;
            }
          }
        }
        break;
        // hover
      } else if (cursor != player_4_positions[j] || cursor_b != player_4_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }
  }
  for (int j = 0; j <= 3; j++) {          //Durch bestätigen des Tasters auf dem Joystick wird der ausgewälte Spiler auf die Posizion des Markers gefahren (Spieler 1.)
    if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && button(player_button) == true && spieler == 1) {
      Serial.println("worked");
      if (cursor == player_1_positions[j] && player_1_positions[j] <= 3 && 0 == player_1_boards[j] && gewuerfelte_zahl == 6) {
        player_1_positions[j] = 4;
      } else if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && player_1_positions[j] > 3) {
        player_1_positions[j] = cursor + gewuerfelte_zahl;
      }
      if (player_1_positions[j] >= 14 && player_1_boards[j] != 3) {   // Solange das eigene Ziel niche erreicht wird läuft die Figur normal weiter auf die nächste Platine  
        player_1_boards[j] = player_1_boards[j] + 1;
        if (player_1_boards[j] == 4) {
          player_1_boards[j] = 0;
        }
        player_1_positions[j] = player_1_positions[j] - 10;
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 2;
          cursor_b = 1;
          cursor = 0;
          displays();
        }
      } else if (player_1_positions[j] <= 17) {
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 2;
          cursor_b = 1;
          cursor = 0;
          displays();
        }
      } else {
        player_1_positions[j] = cursor;
        compare();
        spieler = 2;
        cursor_b = 1;
        cursor = 0;
        displays();
      }
      // //Durch bestätigen des Tasters auf dem Joystick wird der ausgewälte Spiler auf die Posizion des Markers gefahren (Spieler 2.)
    } else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && button(player_button) && spieler == 2 && cursor_with_player_charakter == false) {
      if (cursor == player_2_positions[j] && player_2_positions[j] <= 3 && 1 == player_2_boards[j] && gewuerfelte_zahl == 6) {
        player_2_positions[j] = 4;
      } else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && player_2_positions[j] > 3) {
        player_2_positions[j] = cursor + gewuerfelte_zahl;
      }
      if (player_2_positions[j] >= 14 && player_2_boards[j] != 0) {  // Solange das eigene Ziel niche erreicht wird läuft die Figur normal weiter auf die nächste Platine
        player_2_boards[j] = player_2_boards[j] + 1;
        if (player_2_boards[j] == 4) {
          player_2_boards[j] = 0;
        }
        player_2_positions[j] = player_2_positions[j] - 10;
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 3;
          cursor_b = 2;
          cursor = 0;
          displays();
        }

      } else if (player_2_positions[j] <= 17) {
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 3;
          cursor_b = 2;
          cursor = 0;
          displays();
        }
      } else {
        player_2_positions[j] = cursor;
        compare();
        spieler = 3;
        cursor_b = 2;
        cursor = 0;
        displays();
      }
      // //Durch bestätigen des Tasters auf dem Joystick wird der ausgewälte Spiler auf die Posizion des Markers gefahren (Spieler 3.)
    } else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && button(player_button) && spieler == 3 && cursor_with_player_charakter == false) {
      if (cursor == player_3_positions[j] && player_3_positions[j] <= 3 && 2 == player_3_boards[j] && gewuerfelte_zahl == 6) {
        player_3_positions[j] = 4;
      } else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && player_3_positions[j] > 3) {
        player_3_positions[j] = cursor + gewuerfelte_zahl;
      }
      if (player_3_positions[j] >= 14 && player_3_boards[j] != 1) {  // Solange das eigene Ziel niche erreicht wird läuft die Figur normal weiter auf die nächste Platine
        player_3_boards[j] = player_3_boards[j] + 1;
        if (player_3_boards[j] == 4) {
          player_3_boards[j] = 0;
        }
        player_3_positions[j] = player_3_positions[j] - 10;
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 4;
          cursor_b = 3;
          cursor = 0;
          displays();
        }

      } else if (player_3_positions[j] <= 17) {
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 4;
          cursor_b = 3;
          cursor = 0;
          displays();
        }
      } else {
        player_3_positions[j] = cursor;
        compare();
        spieler = 4;
        cursor_b = 3;
        cursor = 0;
        displays();
      }
      // Durch bestätigen des Tasters auf dem Joystick wird der ausgewälte Spiler auf die Posizion des Markers gefahren (Spieler 4.)
    } else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && button(player_button) && spieler == 4 && cursor_with_player_charakter == false) {
      if (cursor == player_4_positions[j] && player_4_positions[j] <= 3 && 3 == player_4_boards[j] && gewuerfelte_zahl == 6) {
        player_4_positions[j] = 4;
      } else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && player_4_positions[j] > 3) {
        player_4_positions[j] = cursor + gewuerfelte_zahl;
      }
      if (player_4_positions[j] >= 14 && player_4_boards[j] != 2) {  // Solange das eigene Ziel niche erreicht wird läuft die Figur normal weiter auf die nächste Platine
        player_4_boards[j] = player_4_boards[j] + 1;
        if (player_4_boards[j] == 4) {
          player_4_boards[j] = 0;
        }
        player_4_positions[j] = player_4_positions[j] - 10;
         if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        }
        else {
          compare();
          spieler = 1;
          cursor_b = 0;
          cursor = 0;
          displays();
        }
      } else if (player_4_positions[j] <= 17) {
        if (gewuerfelte_zahl == 6) {
          compare();
          displays();
        } else {
          compare();
          spieler = 1;
          cursor_b = 0;
          cursor = 0;
          displays();
        }
      } else {
        player_4_positions[j] = cursor;
        compare();
        spieler = 1;
        cursor_b = 0;
        cursor = 0;
        displays();
      }
      
    }
  }
  return 0;
}
void compare() {                              //Logig fürs Schmeißen eines Gegeners. Zurücksätzen auf Startposizion 
  if (spieler == 1) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_2_positions[j] && player_1_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = referenz[j];
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_3_positions[j] && player_1_boards[i] == player_3_boards[j]) {
          player_3_positions[j] = referenz[j];
          player_3_boards[j] = 2;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_4_positions[j] && player_1_boards[i] == player_4_boards[j]) {
          player_4_positions[j] = referenz[j];
          player_4_boards[j] = 3;
        }
      }
    }
  }
  if (spieler == 2) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_1_positions[j] && player_2_boards[i] == player_1_boards[j]) {
          player_1_positions[j] = referenz[j];
          player_1_boards[j] = 0;
        }
      }
    }
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_3_positions[j] && player_2_boards[i] == player_3_boards[j]) {
          player_3_positions[j] = referenz[j];
          player_3_boards[j] = 2;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_4_positions[j] && player_2_boards[i] == player_4_boards[j]) {
          player_4_positions[j] = referenz[j];
          player_4_boards[j] = 3;
        }
      }
    }
  }
  if (spieler == 3) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_1_positions[j] && player_3_boards[i] == player_1_boards[j]) {
          player_1_positions[j] = referenz[j];
          player_1_boards[j] = 0;
        }
      }
    }
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_2_positions[j] && player_3_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = referenz[j];
          player_2_boards[j] = 1;
        }
      }
    }
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_4_positions[j] && player_3_boards[i] == player_4_boards[j]) {
          player_4_positions[j] = referenz[j];
          player_4_boards[j] = 3;
        }
      }
    }
  }
  if (spieler == 4) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_4_positions[i] == player_1_positions[j] && player_4_boards[i] == player_1_boards[j]) {
          player_1_positions[j] = referenz[j];
          player_1_boards[j] = 0;
        }
      }
    }
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_4_positions[i] == player_2_positions[j] && player_4_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = referenz[j];
          player_2_boards[j] = 1;
        }
      }
    }
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_4_positions[i] == player_3_positions[j] && player_4_boards[i] == player_3_boards[j]) {
          player_3_positions[j] = referenz[j];
          player_3_boards[j] = 2;
        }
      }
    }
  }
}

void anzeigen(int k, int c, int g, int b, int r) {      //Ausgabe der Farben der Neopixel 
  if (k == 0) {
    pixels_0.setPixelColor(c, pixels_0.Color(g, b, r));
    pixels_0.show();
    delay(1);
  }
  if (k == 1) {
    pixels_1.setPixelColor(c, pixels_1.Color(g, b, r));
    pixels_1.show();
    delay(1);
  }
  if (k == 2) {
    pixels_2.setPixelColor(c, pixels_2.Color(g, b, r));
    pixels_2.show();
    delay(1);
  }
  if (k == 3) {
    pixels_3.setPixelColor(c, pixels_3.Color(g, b, r));
    pixels_3.show();
    delay(1);
  }
}

void programm() {                                 //Aktualiesierung der Farben der Neopixel
  for (int k = 0; k <= 3; k++) {
    for (int c = 0; c <= 18; c++) {
      int test = 0;
      if (c == cursor && k == cursor_b) {
        r = 100;
        g = 100;
        b = 100;
        anzeigen(k, c, g, b, r);
        test = 1;
      }
      if (c == marker && k == marker_b) {
        r = 100;
        g = 100;
        b = 0;
        anzeigen(k, c, g, b, r);
        test = 1;
      }
      for (int t = 0; t <= 3; t++) {
        if (c == player_1_positions[t] && k == player_1_boards[t]) {
          if (cursor == player_1_positions[t] && cursor_b == player_1_boards[t]) {
            r = 50;
            g = 50;
            b = 100;
          } else if (marker == player_1_positions[t] && marker_b == player_1_boards[t]) {
            r = 50;
            g = 0;
            b = 100;
          } else {
            r = 0;
            g = 0;
            b = 100;
          }
          anzeigen(k, c, r, g, b);
          test = 1;
        }
      }
      for (int t = 0; t <= 3; t++) {
        if (c == player_2_positions[t] && k == player_2_boards[t]) {
          if (cursor == player_2_positions[t] && cursor_b == player_2_boards[t]) {
            r = 50;
            g = 100;
            b = 50;
          } else if (marker == player_2_positions[t] && marker_b == player_2_boards[t]) {
            r = 50;
            g = 100;
            b = 50;
          } else {
            r = 0;
            g = 100;
            b = 0;
          }
          anzeigen(k, c, r, g, b);
          test = 1;
        }
      }

      for (int t = 0; t <= 3; t++) {
        if (c == player_3_positions[t] && k == player_3_boards[t]) {
          if (cursor == player_3_positions[t] && cursor_b == player_3_boards[t]) {
            r = 100;
            g = 100;
            b = 50;
          } else if (marker == player_3_positions[t] && marker_b == player_3_boards[t]) {
            r = 100;
            g = 100;
            b = 75;
          } else {
            r = 100;
            g = 100;
            b = 0;
          }
          anzeigen(k, c, r, g, b);
          test = 1;
        }
      }
      for (int t = 0; t <= 3; t++) {
        if (c == player_4_positions[t] && k == player_4_boards[t]) {
          if (cursor == player_4_positions[t] && cursor_b == player_4_boards[t]) {
            r = 100;
            g = 50;
            b = 50;
          } else if (marker == player_4_positions[t] && marker_b == player_4_boards[t]) {
            r = 100;
            g = 0;
            b = 50;
          } else {
            r = 100;
            g = 0;
            b = 0;
          }
          anzeigen(k, c, r, g, b);
          test = 1;
        }
      }
      if (test == 0) {
        r = 0;
        g = 0;
        b = 0;
        anzeigen(k, c, r, g, b);
      }
    }
  }
}

void displays() {             //Ansteuerung der Displays 
  programm();
  if (spieler == 1) {
    int i = 0;
    tft.setCursor(100, 60);
    for (int t = 0; t <= 3; t++) {
      if (player_1_positions[t] < 4 && player_1_boards[t] == 0) {
        i++;
      }
    }
    if (i == 4) {
      for (int t = 0; t < 3; t++) {
        tft.fillScreen(ST77XX_BLUE);
        wue();
        tft.setCursor(100, 60);
        tft.println(gewuerfelte_zahl);
        if (gewuerfelte_zahl == 6) {
          break;
        }
      }
    } else {
      tft.fillScreen(ST77XX_BLUE);
      wue();
      tft.setCursor(100, 60);
      tft.println(gewuerfelte_zahl);
    }
  }
  if (spieler == 2) {
    int i = 0;
    tft.setCursor(100, 60);
    for (int t = 0; t <= 3; t++) {
      if (player_2_positions[t] < 4 && player_2_boards[t] == 1) {
        i++;
      }
    }
    if (i == 4) {
      for (int t = 0; t < 3; t++) {
        tft.fillScreen(0x0580);
        wue();
        tft.setCursor(100, 60);
        tft.println(gewuerfelte_zahl);
        if (gewuerfelte_zahl == 6) {
          break;
        }
      }
    } else {
      tft.fillScreen(0x0580);
      wue();
      tft.setCursor(100, 60);
      tft.println(gewuerfelte_zahl);
    }
  }
  if (spieler == 3) {
    int i = 0;
    tft.setCursor(100, 60);
    for (int t = 0; t <= 3; t++) {
      if (player_3_positions[t] < 4 && player_3_boards[t] == 2) {
        i++;
      }
    }
    if (i == 4) {
      for (int t = 0; t < 3; t++) {
        tft.fillScreen(ST77XX_YELLOW);
        wue();
        tft.setCursor(100, 60);
        tft.println(gewuerfelte_zahl);
        if (gewuerfelte_zahl == 6) {
          break;
        }
      }
    } else {
      tft.fillScreen(ST77XX_YELLOW);
      wue();
      tft.setCursor(100, 60);
      tft.println(gewuerfelte_zahl);
    }
  }
  if (spieler == 4) {
    int i = 0;
    tft.setCursor(100, 60);
    for (int t = 0; t <= 3; t++) {
      if (player_4_positions[t] < 4 && player_4_boards[t] == 3) {
        i++;
      }
    }
    if (i == 4) {
      for (int t = 0; t < 3; t++) {
        tft.fillScreen(ST77XX_RED);
        wue();
        tft.setCursor(100, 60);
        tft.println(gewuerfelte_zahl);
        if (gewuerfelte_zahl == 6) {
          break;
        }
      }
    } else {
      tft.fillScreen(ST77XX_RED);
      wue();
      tft.setCursor(100, 60);
      tft.println(gewuerfelte_zahl);
    }
  }
}
void loop() {

  curser();
  eventhandler();
  programm();
}
