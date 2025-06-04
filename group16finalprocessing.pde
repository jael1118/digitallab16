import processing.serial.*;

Serial myPort;

int cols = 8;
int rows = 8;
int cellSize = 60;

int score = 0;
int[][] ledState = new int[8][8];

void setup() {
  surface.setSize(cols * cellSize, rows * cellSize + 40);
  myPort = new Serial(this, "COM5", 9600);
}

void draw() {
  background(255);
  drawGrid();
  fill(0);
  textSize(20);
  text("Score: " + score, 10, height - 10);
}

void drawGrid() {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int x = j * cellSize;
      int y = i * cellSize;
      stroke(0);
      fill(ledState[i][j] == 1 ? color(255, 0, 0) : 200);
      rect(x, y, cellSize, cellSize);
    }
  }
}

void mousePressed() {
  int col = mouseX / cellSize;
  int row = mouseY / cellSize;

  if (col >= 0 && col < cols && row >= 0 && row < rows) {
    row = 7 - row;
    col = 7 - col;

    String hitCommand = row + "," + col + "\n";

    myPort.write(hitCommand);
    println("Send: " + hitCommand);
  }
}

void serialEvent(Serial myPort) {
  String inString = myPort.readStringUntil('\n');
  if (inString != null) {
    inString = trim(inString);
    println("Receive: " + inString);  
    if (inString.startsWith("Score: ")) {
      score = int(inString.substring(7));
    }
  }
}
