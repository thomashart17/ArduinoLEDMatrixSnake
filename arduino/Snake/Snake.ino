//
// LED Matrix Snake Game 
// Author: Thomas Hart
//

/**
 * Directions the snake can move.
 */
enum Direction {
  UP = 1,
  LEFT = 2,
  DOWN = 3,
  RIGHT = 4
};

/**
 * Represents one segment of the snake used for the game.
 */
struct SnakeSegment {
  SnakeSegment *next;
  SnakeSegment *previous;
  int x;
  int y;
  int dir;
};

SnakeSegment *head;
SnakeSegment *tail;

const int rows[8] = {2,3,4,5,17,16,15,14};
const int cols[8] = {6,7,8,9,10,11,12,13};

bool board[8][8] = {{0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0},
                    {0,0,0,0,0,0,0,0}};

const bool digits[10][5][3] = {{{1,1,1},
                         {1,0,1},
                         {1,0,1},
                         {1,0,1},
                         {1,1,1}},
                        {{0,0,1},
                         {0,0,1},
                         {0,0,1},
                         {0,0,1},
                         {0,0,1}},
                        {{1,1,1},
                         {0,0,1},
                         {1,1,1},
                         {1,0,0},
                         {1,1,1}},
                        {{1,1,1},
                         {0,0,1},
                         {1,1,1},
                         {0,0,1},
                         {1,1,1}},
                        {{1,0,1},
                         {1,0,1},
                         {1,1,1},
                         {0,0,1},
                         {0,0,1}},
                        {{1,1,1},
                         {1,0,0},
                         {1,1,1},
                         {0,0,1},
                         {1,1,1}},
                        {{1,1,1},
                         {1,0,0},
                         {1,1,1},
                         {1,0,1},
                         {1,1,1}},
                        {{1,1,1},
                         {0,0,1},
                         {0,0,1},
                         {0,0,1},
                         {0,0,1}},
                        {{1,1,1},
                         {1,0,1},
                         {1,1,1},
                         {1,0,1},
                         {1,1,1}},
                        {{1,1,1},
                         {1,0,1},
                         {1,1,1},
                         {0,0,1},
                         {1,1,1}}};

bool playing = 0;
bool food_status = 0;
bool show_food = 1;

int dir = RIGHT;
int score = 0;
int food_x;
int food_y;

/**
 * Resets board to initial state to allow the game to be played multiple times.
 */
void resetBoard() {
  while (head) {
    SnakeSegment *temp = head;
    head = head->next;
    free(temp);
  }
  tail = NULL;
  dir = RIGHT;
  head = malloc(sizeof(SnakeSegment));
  head->next = NULL;
  head->previous = NULL;
  head->x = 2;
  head->y = 2;
  head->dir = RIGHT;
  tail = head;
  addSegment();
  addFood();
  updateDisplay();
  drawDisplay();
}

/**
 * Adds a segment to the current snake.
 */
void addSegment() {
  SnakeSegment *temp = tail;
  tail = malloc(sizeof(SnakeSegment));
  tail->next = NULL;
  tail->previous = temp;
  temp->next = tail;
  switch (temp->dir) {
    case UP:
      tail->x = temp->x;
      tail->y = temp->y + 1;
      break;
    case LEFT:
      tail->x = temp->x + 1;
      tail->y = temp->y;
      break;
    case DOWN:
      tail->x = temp->x;
      tail->y = temp->y - 1;
      break;
    case RIGHT:
      tail->x = temp->x - 1;
      tail->y = temp->y;
      break;
  }
  tail->dir = temp->dir;
}

/**
 * Adds a new food item to the board.
 */
void addFood() {
  do {
    food_x = random(0, 8);
    food_y = random(0, 8);
  } while (board[food_y][food_x] == 1);
  food_status = 1;
}

/**
 * Updates the board to show the current output
 */
void updateDisplay() {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      board[i][j] = 0;
    }
  }
  if (playing) {
    SnakeSegment *current = head;
    while (current) {
      board[current->y][current->x] = 1;
      current = current->next;
    }
    if (!food_status) addFood();
  } else {
    int ones = score%10;
    int tens = score/10;
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 3; ++j) {
        board[i + 1][j] = digits[tens][i][j];
      }
    }
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 3; ++j) {
        board[i + 1][j + 4] = digits[ones][i][j];
      }
    }
  }
}

/**
 * Draws the current board on the LED Matrix
 */
void drawDisplay() {
  if (playing) board[food_y][food_x] = show_food ? 1 : 0;
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) digitalWrite(cols[j], HIGH);
    digitalWrite(rows[i], HIGH);
    for (int j = 0; j < 8; ++j) digitalWrite(cols[j], board[i][j] ? LOW: HIGH);
    delay(1);
    digitalWrite(rows[i], LOW);    
  }
}

/*
 * Moves the snake one space forward
 */
void moveSnake() {
  SnakeSegment *temp = tail;
  tail = tail->previous;
  tail->next = NULL;
  switch (dir) {
    case UP:
      temp->x = head->x;
      temp->y = head->y - 1;
      break;
    case LEFT:
      temp->x = head->x - 1;
      temp->y = head->y;
      break;
    case DOWN:
      temp->x = head->x;
      temp->y = head->y + 1;
      break;
    case RIGHT:
      temp->x = head->x + 1;
      temp->y = head->y;
      break;
  }
  if (temp->x > 7) temp->x = 0;
  else if (temp->x < 0) temp->x = 7;
  else if (temp->y > 7) temp->y = 0;
  else if (temp->y < 0) temp->y = 7;
  temp->next = head;
  temp->previous = NULL;
  temp->dir = dir;
  head->previous = temp;
  head = temp;
  if ((head->x == food_x) && (head->y == food_y)) {
    addSegment();
    ++score;
    if (score == 62) {
      playing = 0;
      resetBoard();
    }
    food_status = 0;
  } else if (board[head->y][head->x] == 1) {
    playing = 0;
    resetBoard();
  }
}

/*
 * Setup for the game.
 */
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for (int i = 2; i < 18; ++i) pinMode(i, OUTPUT);
  head = malloc(sizeof(SnakeSegment));
  head->next = NULL;
  head->previous = NULL;
  head->x = 2;
  head->y = 2;
  head->dir = 4;
  tail = head;
  addSegment();
  addFood();
  updateDisplay();
  drawDisplay();
}

/*
 * Main loop for the game.
 */
void loop() {
  if (playing) moveSnake();
  updateDisplay();
  for (int i = 0; i < 36; ++i) {
    if (i%12 == 0) show_food = !show_food;
    drawDisplay();
  }
}

/*
 * Handles serial input to move the snake.
 */
void serialEvent() {
  int original = dir;
  while (Serial.available() && dir == original) {
    char c = Serial.read();
    switch (c) {
      case '0':
        playing = 1;
        updateDisplay();
        score = 0;
        break;
      case '1':
        if (dir != DOWN) dir = UP;
        break;
      case '2':
        if (dir != RIGHT) dir = LEFT;
        break;
      case '3':
        if (dir != UP) dir = DOWN;
        break;
      case '4':
        if (dir != LEFT) dir = RIGHT;
        break;
      default:
        break;
    }
  }
}
