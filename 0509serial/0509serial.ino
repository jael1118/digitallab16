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

const int row[] = {
  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8
};
const int col[] = {
  COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8
};
int imgIndexNow = 0;
bool isPressing = false;
int H[8][8] = {{1,1,1,1,1,1,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,1,1,1,1,1,1}};

int A[8][8] = {{1,1,1,1,1,1,1,1},
		       {1,1,1,0,0,1,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,0,0,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,0,1,1,0,1,1},
		       {1,1,1,1,1,1,1,1}};

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


byte incomingByte = 0; // for incoming serial data

void setup() {
      Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
      for(byte i=0;i<=sizeof(row);i++){
        pinMode(row[i],OUTPUT);
      }
      for(byte i=0;i<=sizeof(col);i++){
        pinMode(col[i],OUTPUT);
      }
      pinMode(2,INPUT_PULLUP);
    }

void showPattern(int matrix[8][8]){
  for(byte i = 0; i < 8; i++){
  for(byte j = 0; j < 8; j++){
digitalWrite(row[j], 1 - scan[i][j]);
digitalWrite(col[j], 1 - matrix[i][j]);
}
for(byte j = 0; j < 8; j++){
digitalWrite(row[j], HIGH);
digitalWrite(col[j], LOW);
}
}}

    void loop() {
      // send data only when you receive data:
      if (Serial.available() > 0) {
        // read the incoming byte:
        incomingByte = Serial.read();
        Serial.println(incomingByte);
        delay(1);
      }
      if (incomingByte=='H') {
        showPattern(H);
      }
      else  {
        showPattern(A);
      }
        // say what you got:
       
      }
  


