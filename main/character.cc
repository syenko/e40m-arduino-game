#include "character.hh"
#include <math.h>

Character::Character() {
  this->lives = 4;
}

Character::Character(char lives) {
  this->lives = lives;
}

float Character::get_x() const {
  return this->x_pos;
}

float Character::get_y() const {
  return this->y_pos;
}

int Character::get_x_rounded() const {
  return round(this->get_x());
}

int Character::get_y_rounded() const {
  return round(this->get_y());
}

void Character::get_input() {
}

void Character::decrease_life() {
  this->lives--;
}

char Character::get_lives() const {
  return this->lives;
}