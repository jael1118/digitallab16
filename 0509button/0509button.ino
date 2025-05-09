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

#define BUTTON 2

const int row[] = {ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = {COL1,COL2, COL3, COL4, COL5, COL6, COL7, COL8};

int imgIndexNow = 0;
bool isPressing = false;

byte scan[8][8] = {
  { 1, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 1, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 1 }
};

byte circle[8][8] = {
  { 1, 1, 0, 0, 0, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 0, 1 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 1, 1, 1, 1, 0 },
  { 1, 0, 1, 1, 1, 1, 0, 1 },
  { 1, 1, 0, 0, 0, 0, 1, 1 }
};



void setup()
{
  Serial.begin(9600);
  
  for (int i = 3; i <= 13; i++) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  
  digitalWrite(A0, LOW);
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
  digitalWrite(A4, LOW);
  
  pinMode(2, INPUT_PULLUP);
}

void loop()
{
  if(digitalRead(2) == LOW && !isPressing)
  {
    digitalWrite(13, HIGH);
    isPressing = true;
    imgIndexNow += 1;
    if(imgIndexNow > 1) imgIndexNow = 0;
  }
  else if(digitalRead(2) == HIGH && isPressing) {
    isPressing = false;
    digitalWrite(13, LOW);
  }
  
  //在每次loop中呼叫lightup畫出目前的圖形
  if(imgIndexNow == 0) lightup(scan);
  else if(imgIndexNow == 1) lightup(circle);
  
    
}

void lightup(byte matrix[8][8]){
  for (int i=0; i<8; i++){
    digitalWrite(col[i], HIGH);
    for (int j = 0; j < 8; j++){
      digitalWrite(row[j], 1-matrix[j][i]);
      delay(0);
    }
    for (int j = 0; j < 8; j++){
      digitalWrite(row[j], HIGH);
      //delay(1);
    }
    digitalWrite(col[i], LOW);
  }
}