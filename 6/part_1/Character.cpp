#include "Character.h"

Character::Character(std::pair<int, int> pos, DIRECTION dir) {
  this->pos = pos;
  this->dir = dir;
}

void Character::turnRight() {
  if ( dir == DIRECTION::TOP ) {
    this->dir = DIRECTION::RIGHT;
    return;
  }

  if ( dir == DIRECTION::RIGHT ) {
    this->dir = DIRECTION::BOTTOM;
    return;
  }

  if ( dir == DIRECTION::BOTTOM ) {
    this->dir = DIRECTION::LEFT;
    return;
  }

  if ( dir == DIRECTION::LEFT ) {
    this->dir = DIRECTION::TOP;
    return;
  }
}
