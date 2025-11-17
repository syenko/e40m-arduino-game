#include "board.hh"
#include "math.h"
#include "Arduino.h"

Board::Board() {
  this->character = new Character();

  this->boardHeight = 15;
  this->boardWidth = 15;
  int t[this->boardHeight][this->boardWidth] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0},
    {0,0,0,0,0,0,0,0,0,1,1,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  // init board
  this->board = new char*[this->boardHeight];
  for (int i = 0; i < this->boardHeight; i++) {
    this->board[i] = new char[this->boardWidth];
    for (int j = 0; j < this->boardWidth; j++) {
      board[i][j] = t[i][j];
      // if (i > 4 && i < 7) {
      //   this->board[i][j] = 16;
      // } else {
      //   this->board[i][j] = 0;
      // }
      
    }
  }


  // init display
  this->display = new char*[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    this->display[i] = new char[BOARD_SIZE]; 
  }
}

Board::~Board() {
  delete this->character;

  for (int i = 0; i < BOARD_SIZE; i++) {
    delete[] this->display[i];
  }
  delete[] this->display;
}

bool Board::isColliding(int x, int y) {
  for (int i = 0; i < CHARACTER_SIZE; i++) {
    for (int j = 0; j < CHARACTER_SIZE; j++) {
      if (this->get(x + i, y + j) != 0) {
        return true;
      } 
    }
  }
  return false;
}

void Board::updateBoardState() {
  int const MINIMUM_Y = 5;

  this->character->get_input();
  // apply gravity
  this->character->set_y_vel(this->character->get_delta_y() + GRAVITY * TIME_CONST);

  // Serial.println("------");
  // Serial.println(this->character->get_x());
  // Serial.println(this->character->get_y());


  // update based on velocities
  float newX = this->character->get_x() + this->character->get_delta_x() * TIME_CONST;
  float newY = this->character->get_y() + this->character->get_delta_y() * TIME_CONST;

  // check collisions
  // x is not blocked
  if (!isColliding(round(newX), this->character->get_y_rounded())) {
    this->character->set_x(newX);
  }
  // y is not blocked
  if (!isColliding(this->character->get_x_rounded(), round(newY))) {
    this->character->set_y(newY);
  }
  // has hit ground
  if (this->get(this->character->get_x_rounded(), this->character->get_y_rounded() + CHARACTER_SIZE) && this->character->get_delta_y() > 0) {
    this->character->set_jumped(false);
    this->character->set_y_vel(0);
  }

  if (this->character->get_y_rounded() > this->boardHeight + MINIMUM_Y) {
    if (this->character->get_lives() > 0) {
      this->character->respawn();
    } else {
      // TODO: Game over?
    }
  }

}

char Board::get(int x, int y) {
  if (x < 0 || x >= this->boardHeight || y < 0 || y >= this->boardHeight) {
    return 0;
  }
  return this->board[y][x];
}

void Board::updateDisplay() {
  this->character->get_input();
  int x = this->character->get_x_rounded();
  int y = this->character->get_y_rounded();

  for (int row = 0; row < BOARD_SIZE; row++) {
    for (int col = 0; col < BOARD_SIZE; col++) {
      this->display[row][col] = this->get(col + x - 3, row + y - 3);
    }
  }

  // draw character
  int start_x = (BOARD_SIZE - 1) / 2;
  int start_y = (BOARD_SIZE - 1) / 2;
  this->display[start_x][start_y] = 15;
  this->display[start_x + 1][start_y] = 15;
  this->display[start_x][start_y + 1] = 15;
  this->display[start_x + 1][start_y + 1] = 15;

  // Draw lives
  for (int i = 0; i < MAX_LIVES; i++) {
    if (i < this->character->get_lives()) {
      this->display[BOARD_SIZE - 1][i] = 15;
    }
    else {
      this->display[BOARD_SIZE - 1][i] = 0;
    }
  }

}

char** Board::getDisplay() { 
  return this->display;
}


void Board::generateFirstOrLastSection(const char size) {
    // First or last section must be ground
    for (int r = 0; r < BOARD_SIZE; r++) {
        for (int c = 0; c < size; c++) {
            
        }
    }
}

void Board::generateMiddleSection(const char size) {
    
}

void generateChunk() {
    char remaining_size = BOARD_SIZE;
    char section_size = random(1, remaining_size - 1);
    remaining_size -= section_size;
    generateFirstOrLastSection(board, section_size);
    section_size = random(1, remaining_size);
    remaining_size -= section_size;
    while (remaining_size > 0) {
        generateSection(board, section_size);
        section_size = random(1, remaining_size);
        remaining_size -= section_size;
    }
    generateFirstOrLastSection(board, remaining_size);
}