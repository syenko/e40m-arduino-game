#include "character.hh"
#include <math.h>
#include <Arduino.h>

const char JOYSTICK_X_PIN = A5;
const char JOYSTICK_Y_PIN = A4;
const char MAX_DELTA_X = 2;
const int ANALOG_READ_MAX = 1023;
const float JUMP_THRESHOLD = 0.5;
const char JUMP_VALUE = 2;

Character::Character() {
  this->lives_ = 4;
}

Character::Character(char lives) {
  this->lives_ = lives;
}

float Character::get_x() const {
  return this->x_pos_;
}

float Character::get_y() const {
  return this->y_pos_;
}

int Character::get_x_rounded() const {
  return round(this->get_x());
}

int Character::get_y_rounded() const {
  return round(this->get_y());
}

float Character::get_delta_x() const {
  return this->delta_x_;
}

float Character::get_delta_y() const {
  return this->delta_y_;
}

void Character::get_input() {
  float x_fraction = analogRead(JOYSTICK_X_PIN) / ANALOG_READ_MAX;
  float y_fraction = analogRead(JOYSTICK_Y_PIN) / ANALOG_READ_MAX;
  this->delta_x_ = x_fraction * MAX_DELTA_X;
  if (delta_y_ > JUMP_THRESHOLD) {
    this->jump();
  }
}

void Character::decrease_life() {
  this->lives_--;
}

char Character::get_lives() const {
  return this->lives_;
}

bool Character::get_jumped() const {
  return jumped_;
}

void Character::jump() {
  if (!get_jumped()) {
    this->delta_y_ = JUMP_VALUE;
    this->jumped_ = true;
  }
}

void Character::set_x(float new_x) {
  this->x_pos_ = new_x;
}

void Character::set_y(float new_y) {
  this->y_pos_ = new_y;
}

void Character::set_x_vel(float new_x_vel) {
  this->delta_x_ = new_x_vel;
}

void Character::set_y_vel(float new_y_vel) {
  this->delta_y_ = new_y_vel;
}

void Character::set_jumped(bool jumped) {
  this->jumped_ = jumped;
}
