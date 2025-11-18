#include "board.hh"
#include "math.h"
#include "Arduino.h"

// Pattern to display when the player wins.
// It is a :) face
const byte win[BOARD_SIZE][BOARD_SIZE] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,16,0,0,16,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,16,0,0,16,0,0},
  {0,0,0,16,16,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};

// Pattern to display when the player loses.
// It is a :( face
const byte lose[BOARD_SIZE][BOARD_SIZE] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,16,0,0,16,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,16,16,0,0,0},
  {0,0,16,0,0,16,0,0},
  {0,0,0,0,0,0,0,0}
};

// Initializes the character along with board and display buffers.
Board::Board() {
  this->state = State::playing;
  this->boardHeight = 25;
  this->boardWidth = 20;

  this->character = new Character(0, this->boardHeight- CHARACTER_SIZE - 1);
  
  // Level array
  const char level_array[this->boardHeight][this->boardWidth] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,WIN_VAL,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,WIN_VAL,WIN_VAL,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,WIN_VAL,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };

  // init board
  this->board = new char*[this->boardHeight];
  for (int i = 0; i < this->boardHeight; i++) {
    this->board[i] = new char[this->boardWidth];
    for (int j = 0; j < this->boardWidth; j++) {
      board[i][j] = level_array[i][j];
    }
  }

  // init display
  this->display = new char*[BOARD_SIZE];
  for (int i = 0; i < BOARD_SIZE; i++) {
    this->display[i] = new char[BOARD_SIZE]; 
  }
}

// Cleans up allocated character and display buffers.
Board::~Board() {
  delete this->character;

  for (int i = 0; i < BOARD_SIZE; i++) {
    delete[] this->display[i];
  }
  delete[] this->display;
}

// Checks for collisions between the character footprint and the board.
int Board::isColliding(int x, int y) {
  int maxCollision = 0;
  for (int i = 0; i < CHARACTER_SIZE; i++) {
    for (int j = 0; j < CHARACTER_SIZE; j++) {
      maxCollision = max(maxCollision, this->get(x + i, y + j));
    }
  }
  return maxCollision;
}

// Advances the game state by applying input, physics, and collisions.
void Board::updateBoardState() {
  int const MINIMUM_Y = 5;

  switch (this->state) {
    case State::playing: {
      if (isColliding(this->character->get_x_rounded(), this->character->get_y_rounded()) == WIN_VAL) {
        this->state = State::won;
        break;
      }

      this->character->get_input();
      // apply gravity
      if (this->character->get_jumped()) { 
        this->character->set_y_vel(this->character->get_delta_y() + GRAVITY * TIME_CONST);
      }

      // update based on velocities
      float newX = this->character->get_x() + this->character->get_delta_x() * TIME_CONST;
      float newY = this->character->get_y() + this->character->get_delta_y() * TIME_CONST;

      // check collisions
      // x is not blocked
      int x_collision = isColliding(round(newX), this->character->get_y_rounded());
      if (x_collision == 0 || x_collision == WIN_VAL) {
        this->character->set_x(newX);
      }
      // y is not blocked
      int y_collision = isColliding(this->character->get_x_rounded(), round(newY));
      if (y_collision == 0 || y_collision == WIN_VAL) {
        this->character->set_y(newY);
      }
      // has hit ground
      int ground_collision = isColliding(this->character->get_x_rounded(), this->character->get_y_rounded() + 1);
      if (!(ground_collision == 0 || ground_collision == WIN_VAL)) {
        if (this->character->get_delta_y() > 0) {
          this->character->set_jumped(false);
          this->character->set_y_vel(0);
        }
      }
      else {
        this->character->set_jumped(true);
      }

      // fell off screen
      if (this->character->get_y_rounded() > this->boardHeight + MINIMUM_Y) {
        if (this->character->get_lives() > 1) {
          this->character->respawn(true);
        } else {
          this->state = State::lost;
        }
      }
      break;
    }
    case State::won:
    case State::lost: {
      // move character to start
      if (this->character->get_respawn_input()) {
        this->state = State::playing;
        this->reset();
      }
      break; 
    }
  }

}

// Returns the tile at the requested coordinate, or zero if out of bounds.
char Board::get(int x, int y) {
  if (x < 0 || x >= this->boardHeight || y < 0 || y >= this->boardHeight) {
    return 0;
  }
  return this->board[y][x];
}

// Rebuilds the visible window centered on the character.
void Board::updateDisplay() {
  switch (this->state) {
    case State::playing: {
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
      this->display[start_x][start_y] = MAX_BRIGHTNESS;
      this->display[start_x + 1][start_y] = MAX_BRIGHTNESS;
      this->display[start_x][start_y + 1] = MAX_BRIGHTNESS;
      this->display[start_x + 1][start_y + 1] = MAX_BRIGHTNESS;

      // Draw lives
      for (int i = 0; i < MAX_LIVES; i++) {
        if (i < this->character->get_lives()) {
          this->display[BOARD_SIZE - 1][i] = MAX_BRIGHTNESS;
        }
        else {
          this->display[BOARD_SIZE - 1][i] = 0;
        }
      }
      break;
    }
    case State::lost: {
      for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
          this->display[row][col] = lose[row][col];
        }
      }
      break;
    }
    case State::won: {
      for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
          this->display[row][col] = win[row][col];
        }
      }
      break;
    }
  }

}

// Provides access to the current display buffer.
char** Board::getDisplay() { 
  return this->display;
}

// Reset the character to starting position and lives
void Board::reset() {
  this->character->respawn(false);
}