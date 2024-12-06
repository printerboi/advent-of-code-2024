#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <cmath>
#include <cassert>
#include "Character.h"
#include <utility>

#define FILENAME "input.txt"

std::vector<std::vector<char>> map;
Character guard({-1, -1}, DIRECTION::TOP);

void parseFile() {
  std::ifstream file(FILENAME);
  std::string   line;
  bool guardFound;
  
  int i = 0;
  while ( std::getline(file, line) ) {
      std::stringstream linestream(line);
      std::string word;
      std::vector<char> row;

      int j = 0;
      for ( char c : line ) {
          row.push_back(c);
          if ( !guardFound && ( c == (char) DIRECTION::TOP || c == (char)  DIRECTION::BOTTOM || c == (char)  DIRECTION::LEFT || c == (char)  DIRECTION::RIGHT ) ) {
            guard.pos = std::pair<int, int>(i, j);
            guard.dir = (DIRECTION) c;
          }

          j++;
      }

      map.push_back(row);
      i++;
  }
}

char getLookAhead() {
  if ( guard.dir == DIRECTION::TOP ) {
    return map[guard.pos.first-1][guard.pos.second];
  }

  if ( guard.dir == DIRECTION::RIGHT ) {
    return map[guard.pos.first][guard.pos.second+1];
  }

  if ( guard.dir == DIRECTION::LEFT ) {
    return map[guard.pos.first][guard.pos.second-1];
  }

  if ( guard.dir == DIRECTION::BOTTOM ) {
    return map[guard.pos.first+1][guard.pos.second];
  }
}

bool isOutOfBounds(std::pair<int, int> pos) {
  return pos.first < 0 ||
    pos.first > map.size()-1 ||
    pos.second < 0 ||
    pos.second > map.at(0).size()-1;
}

bool isAtBorder(std::pair<int, int> pos) {
  return pos.first == 0 ||
    pos.first == map.size()-1 ||
    pos.second == 0 ||
    pos.second == map.at(0).size()-1;
}

void guardRun() {
  while (!isAtBorder(guard.pos)) {
    while ( getLookAhead() != '#' ) {
      std::pair<int, int> update({0, 0});

      if ( guard.dir == DIRECTION::TOP ) {
        update = {guard.pos.first-1, guard.pos.second};
      } else if ( guard.dir == DIRECTION::RIGHT ) {
        update = {guard.pos.first, guard.pos.second+1};
      } else if ( guard.dir == DIRECTION::LEFT ) {
        update = {guard.pos.first, guard.pos.second-1};
      } else if ( guard.dir == DIRECTION::BOTTOM ) {
        update = {guard.pos.first+1, guard.pos.second};
      }

      std::cout << guard.pos.first << ", " << guard.pos.second << std::endl;
      std::cout << update.first << ", " << update.second << std::endl;
      std::cout << isAtBorder(guard.pos) << std::endl;
      std::cout << isAtBorder(update) << std::endl;

      /* if ( isOutOfBounds(update) ) {
        std::cout << update.first << ", " << update.second << std::endl;
        guard.pos = update;
        break;
      } */

     if(isAtBorder(update)) {
      std::swap(
        map[guard.pos.first][guard.pos.second],
        map[update.first][update.second]);
      map[guard.pos.first][guard.pos.second] = 'X';
      guard.pos = update;
      break;
     }

      std::swap(
        map[guard.pos.first][guard.pos.second],
        map[update.first][update.second]);
      map[guard.pos.first][guard.pos.second] = 'X';
      guard.pos = update;

      std::cout << "============== " << (char) guard.dir << " ==============" << std::endl;
      for(auto row : map) {
        for(auto c : row) {
          std::cout << c;
        }
        std::cout << std::endl;
      }
      std::cout << "===============================" << std::endl;
    }
    guard.turnRight();
  }
}

int main() {
  int xcount = 0;
  parseFile();
  guardRun();


  for(auto row : map) {
    for(auto c : row) {
      if(c == 'X') {
        xcount++;
      }
    }
  }

  std::cout << "X: " << xcount+1 << std::endl;



  return 0;
}
