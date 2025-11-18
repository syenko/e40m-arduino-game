#include "character.hh"
#include <math.h>
#include <Arduino.h>

const char JOYSTICK_X_PIN = A5;
const char JOYSTICK_Y_PIN = A4;
const char MAX_DELTA_X = 2;
const int ANALOG_READ_MAX = 1023;
const float JUMP_THRESHOLD = 0.2;
const char JUMP_VALUE = -2;
const float START_THRESHOLD = -0.45;

// Builds a default character using the zero position constructor.
Character::Character() : Character(0, 0) {}

// Builds a character starting at a supplied position.
Character::Character(int x, int y) {
  this->start_x_ = x;
  this->start_y_ = y;
  this->lives_ = 4;
  this->x_pos_ = x;
  this->y_pos_ = y;
  this->delta_x_ = 0;
  this->delta_y_ = 0;
  this->jumped_ = false;
}

// Builds a character with a specific life total.
Character::Character(char lives) {
  this->lives_ = lives;
}

// Returns the precise x-position.
float Character::get_x() const {
  return this->x_pos_;
}

// Returns the precise y-position.
float Character::get_y() const {
  return this->y_pos_;
}

// Returns the rounded grid x-position.
int Character::get_x_rounded() const {
  return round(this->get_x());
}

// Returns the rounded grid y-position.
int Character::get_y_rounded() const {
  return round(this->get_y());
}

// Returns the x-axis velocity component.
float Character::get_delta_x() const {
  return this->delta_x_;
}

// Returns the y-axis velocity component.
float Character::get_delta_y() const {
  return this->delta_y_;
}

// Polls the joystick and updates motion intents.
void Character::get_input() {
  float x_fraction = 0.5 - float(analogRead(JOYSTICK_X_PIN)) / ANALOG_READ_MAX;
  float y_fraction = 0.5 - float(analogRead(JOYSTICK_Y_PIN)) / ANALOG_READ_MAX;

  if (abs(x_fraction) < 0.1) {
    x_fraction = 0;
  }
  if (abs(y_fraction) < 0.1) {
    y_fraction = 0;
  }

  this->delta_x_ = x_fraction * MAX_DELTA_X;
  if (y_fraction > JUMP_THRESHOLD) {
    this->jump();
  }
}

// Deducts a life from the player.
void Character::decrease_life() {
  this->lives_--;
}

// Returns the lives remaining.
char Character::get_lives() const {
  return this->lives_;
}

// Returns whether the character is already airborne.
bool Character::get_jumped() const {
  return jumped_;
}

// Initiates a jump by applying vertical velocity once until landing.
void Character::jump() {
  if (!get_jumped()) {
    this->delta_y_ = JUMP_VALUE;
    this->jumped_ = true;
  }
}

// Directly sets the x-position.
void Character::set_x(float new_x) {
  this->x_pos_ = new_x;
}

// Directly sets the y-position.
void Character::set_y(float new_y) {
  this->y_pos_ = new_y;
}

// Directly sets the x-velocity.
void Character::set_x_vel(float new_x_vel) {
  this->delta_x_ = new_x_vel;
}

// Directly sets the y-velocity.
void Character::set_y_vel(float new_y_vel) {
  this->delta_y_ = new_y_vel;
}

// Updates the anti double-jump latch.
void Character::set_jumped(bool jumped) {
  this->jumped_ = jumped;
}

// Resets state to the spawn position and decreases a life.
void Character::respawn(bool decrease) {
  this->x_pos_ = this->start_x_;
  this->y_pos_ = this->start_y_;
  this->delta_x_ = 0;
  this->delta_y_ = 0;
  this->jumped_ = false;

  if (decrease) {
    this->decrease_life();
  }
  else {
    this->lives_ = MAX_LIVES;
  }
}

bool Character::get_respawn_input() const {
  float y_fraction = 0.5 - float(analogRead(JOYSTICK_Y_PIN)) / ANALOG_READ_MAX;

  return y_fraction <= START_THRESHOLD;
}
