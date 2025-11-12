#include "board.hh"
#include "math.h"

#define GRAVITY 9.8
#define BOARD_SIZE 8
#define TIME_CONST 0.01

Board::Board() {
  this->character = new Character();

  // init display
  this->display = new char*[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    this->display[i] = new char[BOARD_SIZE];
    for (int j = 0; j < BOARD_SIZE; j++) {
      if (i > 5) {
        this->display[i][j] = 16;
      } else {
        this->display[i][j] = 0;
      }
      
    }
  }
}

Board::~Board() {
  delete this->character;

  for (int i = 0; i < BOARD_SIZE; i++) {
    delete[] this->display[i];
  }
  delete[] this->display;
}

void Board::updateBoardState() {
  // apply gravity
  if (this->character->get_jumped()) {
    this->character->set_y_vel(this->character->get_delta_y() - GRAVITY * TIME_CONST);
  }

  // update based on velocities
  float newX = this->character->get_x() + this->character->get_delta_x();
  float newY = this->character->get_y() + this->character->get_delta_y();

  // check collisions
  // x is not blocked
  if (this->get(round(newX), this->character->get_y_rounded()) == 0) {
    this->character->set_x(newX);
  }
  // y is not blocked
  if (this->get(this->character->get_x_rounded(), round(newY)) == 0) {
    this->character->set_y(newY);

    // has hit ground
    if (this->character->get_jumped() && this->get(this->character->get_x_rounded(), round(newY) + 1)) {
      this->character->set_jumped(false);
      this->character->set_y_vel(0);
    }
  }
 

}

char Board::get(int x, int y) {
  if (x < 0 || x > this->boardHeight || y < 0 || y > this->boardHeight) {
    return 0;
  }
  return board[x][y];
}

void Board::updateDisplay() {
  this->character->get_input();
  int x = this->character->get_x_rounded();
  int y = this->character->get_y_rounded();

  for (int row = 0; row < BOARD_SIZE; row++) {
    this->display[row] = new char[BOARD_SIZE];

    for (int col = 0; col < BOARD_SIZE; col++) {
      this->display[row][col] = this->get(row + x - (int)((BOARD_SIZE - 1) / 2), col + y - (int)((BOARD_SIZE - 1) / 2));
    }
  }

  // draw character
  int start_x = (BOARD_SIZE - 1) / 2;
  int start_y = (BOARD_SIZE - 1) / 2;
  this->display[start_x][start_y] = 15;
  this->display[start_x + 1][start_y] = 15;
  this->display[start_x][start_y + 1] = 15;
  this->display[start_x + 1][start_y + 1] = 15;

}

char** Board::getDisplay() { 
  return this->display;
}