int referenz[] = { 0, 1, 2, 3 };
int player_1_positions[] = { 0, 1, 7, 3 };
int player_1_boards[] = { 0, 0, 1, 0 };
int player_1_farbe[] = { 100, 0, 0 };
int player_1_joystick = A3;
int player_1_farbe_mit_cursor[] = { 100, 50, 50 };

int player_2_positions[] = { 0, 1, 2, 7 };
int player_2_boards[] = { 1, 1, 1, 1 };
int player_2_farbe[] = { 100, 0, 0 };
int player_2_joystick = A3;
int player_2_farbe_mit_cursor[] = { 100, 50, 50 };

int player_3_positions[] = { 0, 1, 2, 3 };
int player_3_boards[] = { 2, 2, 2, 2 };
int player_3_farbe[] = { 100, 0, 0 };
int player_3_joystick = A3;
int player_3_farbe_mit_cursor[] = { 100, 50, 50 };

int player_4_positions[] = { 0, 1, 2, 3 };
int player_4_boards[] = { 3, 3, 3, 3 };
int player_4_farbe[] = { 100, 0, 0 };
int player_4_joystick = A3;
int player_4_farbe_mit_cursor[] = { 100, 50, 50 };

int spieler = 1;

int player_button = 5;

int saved_position;

int cursor = 10;
int cursor_b = 0;

int cursor_saved = cursor;
bool cursor_with_player_charakter = false;

int gewuerfelte_zahl = 0;
int marker = 0;
int marker_b = 4;
void setup() {
  Serial.begin(9600);
  pinMode(player_button, INPUT);
}

bool button(int button) {
  while (digitalRead(button)) {
    delay(10);
  }
  return digitalRead(button);
}

int curser(int player_Joystick) {

  //bewegen des cursers
  int Joystick = analogRead(player_Joystick);
  //bewegung hoch
  if (Joystick >= 800) {
    cursor = cursor + 1;
    while (Joystick >= 700) {
      Joystick = analogRead(player_Joystick);  //Achten das Joystick seine Grundposition erreicht hat
    }
  }
  //bewegen runter
  else if (Joystick <= 300) {
    cursor = cursor - 1;
    while (Joystick <= 400) {
      Joystick = analogRead(player_Joystick);
    }
  }

  if (cursor == 16) {
    cursor = 0;
    cursor_b++;
    if (cursor_b == 5) {
      cursor_b = 0;
    }
  } else if (cursor == -1) {
    cursor = 15;
    cursor_b--;
    if (cursor_b == 0) {
      cursor_b = 4;
    }
  }
}

void eventhandler() {

  for (int j = 0; j <= 3; j++) {
    if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && spieler == 1) {
      marker = cursor + gewuerfelte_zahl;
      marker_b = cursor;
      if (marker >= 15) {
        marker_b ++;
        marker = marker - 15;
      }
      // hover
    }
    else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && spieler == 2) {
      marker = cursor + gewuerfelte_zahl;
      marker_b = cursor;
      if (marker >= 15) {
        marker_b ++;
        marker = marker - 15;
      }
      // hover
    }
    else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && spieler == 3) {
      marker = cursor + gewuerfelte_zahl;
      marker_b = cursor;
      if (marker >= 15) {
        marker_b ++;
        marker = marker - 15;
      }
      // hover
    }
    else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && spieler == 4) {
      marker = cursor + gewuerfelte_zahl;
      marker_b = cursor;
      if (marker >= 15) {
        marker_b ++;
        marker = marker - 15;
      }
      // hover
    }
    else{
      marker = 0;
      marker_b = 4;
    }
  }
  for (int j = 0; j <= 3; j++) {
    if (cursor == player_1_positions[j] && cursor_b == player_1_boards[j] && button(player_button) && spieler == 1) {
      player_1_positions[j] = cursor + gewuerfelte_zahl;
      if (player_1_positions[j] >= 15 && player_1_boards[j] != 3) {
        player_1_boards[j] = player_1_boards[j] + 1;
        player_1_positions[j] = player_1_positions[j] - 15;
      }
      else if (player_1_positions[j] <= 18 ){
        
      }
      else {
        Serial.println("not possible")
      }
      // play animation that the charakter walks to the next destination
    }
    else if (cursor == player_2_positions[j] && cursor_b == player_2_boards[j] && button(player_button) && spieler == 2 && cursor_with_player_charakter == false) {
      player_2_positions[j] = cursor + gewuerfelte_zahl;
      if (player_2_positions[j] >= 15 && player_2_boards[j] != 0) {
        player_2_boards[j] = player_2_boards[j] + 1;
        player_2_positions[j] = player_2_positions[j] - 15;
      }
      else if (player_1_positions[j] <= 18 ){
        
      }
      else {
        Serial.println("not possible")
      }
      // play animation that the charakter walks to the next destination
    }
    else if (cursor == player_3_positions[j] && cursor_b == player_3_boards[j] && button(player_button) && spieler == 3 && cursor_with_player_charakter == false) {
      player_3_positions[j] = cursor + gewuerfelte_zahl;
      if (player_3_positions[j] >= 15 && player_3_boards[j] != 1) {
        player_3_boards[j] = player_3_boards[j] + 1;
        player_3_positions[j] = player_3_positions[j] - 15;
      }
      else if (player_1_positions[j] <= 18 ){
        
      }
      else {
        Serial.println("not possible")
      }
      // play animation that the charakter walks to the next destination
    }
    else if (cursor == player_4_positions[j] && cursor_b == player_4_boards[j] && button(player_button) && spieler == 4 && cursor_with_player_charakter == false) {
      player_4_positions[j] = cursor + gewuerfelte_zahl;
      if (player_4_positions[j] >= 15 && player_1_boards[j] != 2) {
        player_4_boards[j] = player_4_boards[j] + 1;
        player_4_positions[j] = player_4_positions[j] - 15;
      }
      else if (player_1_positions[j] <= 18 ){
        
      }
      else {
        Serial.println("not possible")
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

void anzeigen() {
  for (int k = 0; k <= 3; k++) {
    for (int c = 0; c <= 14; c++) {
      int test = 0;
      if (c == cursor && k == cursor_b) {
        Serial.print(k);
        Serial.print(c);
        Serial.println("  white");
      }
      if (c == marker && k == marker_b) {
        Serial.print(k);
        Serial.print(c);
        Serial.println("  orange");
      }
      for (int b = 0; b <= 3; b++) {
        if (c == player_1_positions[b] && k == player_1_boards[b]) {
          Serial.print(k);
          Serial.print(c);
          Serial.println("  blau");
          test = 1;
        }
      }
      for (int b = 0; b <= 3; b++) {
        if (c == player_2_positions[b] && k == player_2_boards[b]) {
          Serial.print(k);
          Serial.print(c);
          Serial.println("  grün");
          test = 1;
        }
      }

      for (int b = 0; b <= 3; b++) {
        if (c == player_3_positions[b] && k == player_3_boards[b]) {
          Serial.print(k);
          Serial.print(c);
          Serial.println("  gelb");
          test = 1;
        }
      }
      for (int b = 0; b <= 3; b++) {
        if (c == player_4_positions[b] && k == player_4_boards[b]) {
          Serial.print(k);
          Serial.print(c);
          Serial.println("  rot");
          test = 1;
        }
      }
      if (test == 0) {
        Serial.print(k);
        Serial.print(c);
        Serial.println("  nichts");
      }
    }
  }
}


void loop() {

  curser(A3);
  eventhandler();
  anzeigen();
  while (1)
    ;
}
