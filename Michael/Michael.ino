#include <Adafruit_NeoPixel.h>


int referenz[] = { 0, 1, 2, 3 };


#define PIN_0 19
#define NUMPIXELS_0 18
Adafruit_NeoPixel pixels_0(NUMPIXELS_0, PIN_0, NEO_GRB + NEO_KHZ800);

int player_1_positions[] = { 0, 1, 2, 3 };
int player_1_boards[] = { 0, 0, 0, 0 };
int player_1_farbe[] = { 100, 0, 0 };
int player_1_joystick = 25;
int player_1_farbe_mit_cursor[] = { 100, 50, 50 };


#define PIN_1 25
#define NUMPIXELS_1 18
Adafruit_NeoPixel pixels_1(NUMPIXELS_1, PIN_1, NEO_GRB + NEO_KHZ800);

int player_2_positions[] = { 0, 1, 2, 3 };
int player_2_boards[] = { 1, 1, 1, 1 };
int player_2_farbe[] = { 100, 0, 0 };
int player_2_joystick = 25;
int player_2_farbe_mit_cursor[] = { 100, 50, 50 };


#define PIN_2 27
#define NUMPIXELS_2 18
Adafruit_NeoPixel pixels_2(NUMPIXELS_2, PIN_2, NEO_GRB + NEO_KHZ800);

int player_3_positions[] = { 0, 1, 2, 3 };
int player_3_boards[] = { 2, 2, 2, 2 };
int player_3_farbe[] = { 100, 0, 0 };
int player_3_joystick = 25;
int player_3_farbe_mit_cursor[] = { 100, 50, 50 };


#define PIN_3 26
#define NUMPIXELS_3 18
Adafruit_NeoPixel pixels_3(NUMPIXELS_3, PIN_3, NEO_GRB + NEO_KHZ800);

int player_4_positions[] = { 0, 1, 2, 3 };
int player_4_boards[] = { 3, 3, 3, 3 };
int player_4_farbe[] = { 100, 0, 0 };
int player_4_joystick = 25;
int player_4_farbe_mit_cursor[] = { 100, 50, 50 };


int spieler = 1;

int player_button = 15;

int saved_position;

int cursor = 2;
int cursor_b = 0;

int cursor_saved = cursor;
bool cursor_with_player_charakter = false;

int gewuerfelte_zahl = 6;
int marker = 0;
int marker_b = 5;

int r = 0;
int g = 0;
int b = 0;

void setup() {




  pinMode(17, OUTPUT);
  digitalWrite(17, HIGH);

  pinMode(14,INPUT);

  pixels_0.begin();
  pixels_1.begin();
  pixels_2.begin();
  pixels_3.begin();
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
  wue();
}

void wue(){
  while (1){
    if (digitalRead(14) == HIGH){
      gewuerfelte_zahl = random(1, 6);
      break;
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

void curser(int player_Joystick) {

  //bewegen des cursers
  int Joystick = analogRead(player_Joystick);
  //bewegung hoch
  if (Joystick <= 800) {
    cursor = cursor + 1;
    while (Joystick <= 700) {
      Joystick = analogRead(player_Joystick);  //Achten das Joystick seine Grundposition erreicht hat
    }
  }
  //bewegen runter
  else if (Joystick >= 1400) {
    cursor = cursor - 1;
    while (Joystick >= 1500) {
      Joystick = analogRead(player_Joystick);
    }
  }

  if (cursor == 18) {
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

void eventhandler() {

  for (int j = 0; j <= 3; j++) {
    if (spieler == 1) {
      if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j]) {
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor_b;
        if (marker >= 15) {
          marker_b++;
          marker = marker - 15;
        }
        break;
        // hover
      } else if (cursor != player_1_positions[j] || cursor_b != player_1_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }

    else if (spieler == 2) {

      if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j]) {
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor;
        if (marker >= 15) {
          marker_b++;
          marker = marker - 15;
        }
        break;
      }

      else if (cursor != player_2_positions[j] || cursor_b != player_2_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }

    // hover

    else if (spieler == 3) {
      if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j]) {
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor;
        if (marker >= 15) {
          marker_b++;
          marker = marker - 15;
        }
        break;
      } else if (cursor != player_3_positions[j] || cursor_b != player_3_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }

    // hover


    else if (spieler == 4) {
      if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j]) {
        marker = cursor + gewuerfelte_zahl;
        marker_b = cursor;
        if (marker >= 15) {
          marker_b++;
          marker = marker - 15;
        }
        break;
        // hover
      }

      else if (cursor != player_4_positions[j] || cursor_b != player_4_boards[j]) {
        marker = 0;
        marker_b = 4;
      }
    }
  }
  for (int j = 0; j <= 3; j++) {
    if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && button(player_button) == true && spieler == 1) {
      Serial.println("worked");
      player_1_positions[j] = cursor + gewuerfelte_zahl;
      if (player_1_positions[j] >= 15 && player_1_boards[j] != 3) {
        player_1_boards[j] = player_1_boards[j] + 1;
        player_1_positions[j] = player_1_positions[j] - 15;
        spieler = 2;
        wue();
      } else if (player_1_positions[j] <= 18) {
        spieler = 2;
        wue();
      } else {
        Serial.println("not possible");
      }
      // play animation that the charakter walks to the next destination
    } else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && button(player_button) && spieler == 2 && cursor_with_player_charakter == false) {
      player_2_positions[j] = cursor + gewuerfelte_zahl;
      if (player_2_positions[j] >= 15 && player_2_boards[j] != 0) {
        player_2_boards[j] = player_2_boards[j] + 1;
        player_2_positions[j] = player_2_positions[j] - 15;
        spieler = 3;
        wue();
      } else if (player_1_positions[j] <= 18) {
        spieler = 3;
        wue();
      } else {
        Serial.println("not possible");
      }
      // play animation that the charakter walks to the next destination
    } else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && button(player_button) && spieler == 3 && cursor_with_player_charakter == false) {
      player_3_positions[j] = cursor + gewuerfelte_zahl;
      if (player_3_positions[j] >= 15 && player_3_boards[j] != 1) {
        player_3_boards[j] = player_3_boards[j] + 1;
        player_3_positions[j] = player_3_positions[j] - 15;
        spieler = 4;
        wue();
      } else if (player_1_positions[j] <= 18) {
        spieler = 4;
        wue();
      } else {
        Serial.println("not possible");
      }
      // play animation that the charakter walks to the next destination
    } else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && button(player_button) && spieler == 4 && cursor_with_player_charakter == false) {
      player_4_positions[j] = cursor + gewuerfelte_zahl;
      if (player_4_positions[j] >= 15 && player_1_boards[j] != 2) {
        player_4_boards[j] = player_4_boards[j] + 1;
        player_4_positions[j] = player_4_positions[j] - 15;
        spieler = 1;
        wue();
      } else if (player_1_positions[j] <= 18) {
        spieler = 1;
        wue();
      } else {
        Serial.println("not possible");
      }
      // play animation that the charakter walks to the next destination
    }
  }


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
          Serial.print(i);
          player_2_positions[j] = 0;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_4_positions[j] && player_1_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_3_positions[j] && player_2_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_3_positions[j] = 0;
          player_3_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_4_positions[j] && player_2_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }

    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_4_positions[j] && player_3_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }
  }

  if (spieler == 2) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_2_positions[j] && player_1_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = 3;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_3_positions[j] && player_1_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_2_positions[j] = 0;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_4_positions[j] && player_1_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_3_positions[j] && player_2_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_3_positions[j] = 0;
          player_3_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_4_positions[j] && player_2_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }

    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_4_positions[j] && player_3_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }
  }
  if (spieler == 3) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_2_positions[j] && player_1_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = 3;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_3_positions[j] && player_1_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_2_positions[j] = 0;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_4_positions[j] && player_1_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_3_positions[j] && player_2_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_3_positions[j] = 0;
          player_3_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_4_positions[j] && player_2_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }

    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_4_positions[j] && player_3_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }
  }
  if (spieler == 4) {
    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_2_positions[j] && player_1_boards[i] == player_2_boards[j]) {
          player_2_positions[j] = 3;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_3_positions[j] && player_1_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_2_positions[j] = 0;
          player_2_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_1_positions[i] == player_4_positions[j] && player_1_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_3_positions[j] && player_2_boards[i] == player_3_boards[j]) {
          Serial.print(i);
          player_3_positions[j] = 0;
          player_3_boards[j] = 1;
        }
      }
    }


    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_2_positions[i] == player_4_positions[j] && player_2_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }

    for (int i = 0; i <= 3; i++) {
      for (int j = 0; j <= 3; j++) {
        if (player_3_positions[i] == player_4_positions[j] && player_3_boards[i] == player_4_boards[j]) {
          Serial.print(i);
          player_4_positions[j] = 0;
          player_4_boards[j] = 1;
        }
      }
    }
  }
}

void anzeigen(int k, int c, int g, int b, int r) {
  if (k == 0) {
    pixels_0.setPixelColor(c, pixels_0.Color(g, b, r));
    pixels_0.show();
    delay(10);
  }
  if (k == 1) {
    pixels_1.setPixelColor(c, pixels_1.Color(g, b, r));
    pixels_1.show();
    delay(10);
  }
  if (k == 2) {
    pixels_2.setPixelColor(c, pixels_2.Color(g, b, r));
    pixels_2.show();
    delay(10);
  }
  if (k == 3) {
    pixels_3.setPixelColor(c, pixels_3.Color(g, b, r));
    pixels_3.show();
    delay(10);
  }
}

void programm() {
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


void loop() {

  curser(35);
  eventhandler();
  programm();
}
