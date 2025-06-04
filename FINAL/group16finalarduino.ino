#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

const int row[] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = {COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};

byte matrix[8][8] = {0};

int moleRow = -1;
int moleCol = -1;

unsigned long lastMoleTime = 0;
unsigned long moleDuration = 3000;
unsigned long moleInterval = 2500;

int score = 0;

void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(row[i], OUTPUT);
    pinMode(col[i], OUTPUT);
  }

  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop() {
  unsigned long now = millis();

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int commaIndex = input.indexOf(',');
    if (commaIndex != -1) {
      int c = input.substring(0, commaIndex).toInt();  // col
      int r = input.substring(commaIndex + 1).toInt(); // row

    
      r = 7 - r;
      c = 7 - c;

      Serial.print("Clicked: ");
      Serial.print(r);
      Serial.print(",");
      Serial.println(c);

      if (r == moleRow && c == moleCol) {
        score++;
        Serial.print("Score: ");
        Serial.println(score);  
        matrix[moleRow][moleCol] = 0;
        moleRow = -1;
        moleCol = -1;
      } else {
        Serial.println("Miss");
      }
    }
  }


  if ((moleRow == -1 && now - lastMoleTime >= moleInterval) ||
      (moleRow != -1 && now - lastMoleTime >= moleDuration)) {
    if (moleRow != -1) matrix[moleRow][moleCol] = 0;

    moleRow = random(8);
    moleCol = random(8);
    matrix[moleRow][moleCol] = 1;

    lastMoleTime = now;

    Serial.print("New mole at: ");
    Serial.print(moleRow);
    Serial.print(",");
    Serial.println(moleCol);
  }

  showPattern(matrix);
}

void showPattern(byte m[8][8]) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(row[i], LOW);
    for (int j = 0; j < 8; j++) {
      int displayRow = 7 - i;
      int displayCol = 7 - j;
      digitalWrite(col[j], m[displayRow][displayCol] ? HIGH : LOW);
    }
    delay(2);
    digitalWrite(row[i], HIGH);
  }
}
