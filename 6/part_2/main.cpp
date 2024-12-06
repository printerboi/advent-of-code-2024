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

std::vector<std::vector<char>> globalmap;
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

            guard.initPos = guard.pos;
            guard.initDir = guard.dir;
          }

          j++;
      }

      globalmap.push_back(row);
      i++;
  }
}

char getLookAhead(std::vector<std::vector<char>> map) {
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

bool isOutOfBounds(std::pair<int, int> pos, std::vector<std::vector<char>> map) {
  return pos.first < 0 ||
    pos.first > map.size()-1 ||
    pos.second < 0 ||
    pos.second > map.at(0).size()-1;
}

bool isAtBorder(std::pair<int, int> pos, std::vector<std::vector<char>> map) {
  return pos.first == 0 ||
    pos.first == map.size()-1 ||
    pos.second == 0 ||
    pos.second == map.at(0).size()-1;
}

bool guardRun(std::vector<std::vector<char>> map) {
  int steps = 0;
  while (!isAtBorder(guard.pos, map) && steps <= 50000) {
    /* std::cout << guard.pos.first << ", " << guard.pos.second << std::endl;
    std::cout << (char) guard.dir << std::endl; */

    while ( getLookAhead(map) != '#' && getLookAhead(map) != 'O' && steps <= 50000) {
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

/*       std::cout << guard.pos.first << ", " << guard.pos.second << std::endl;
      std::cout << update.first << ", " << update.second << std::endl;
      std::cout << isAtBorder(guard.pos, map) << std::endl;
      std::cout << isAtBorder(update, map) << std::endl; */

      /* if ( isOutOfBounds(update) ) {
        std::cout << update.first << ", " << update.second << std::endl;
        guard.pos = update;
        break;
      } */

     if(isAtBorder(update, map)) {
      std::swap(
        map[guard.pos.first][guard.pos.second],
        map[update.first][update.second]);
      guard.pos = update;
      break;
     }

     /* std::cout << std::endl << "============== " << steps << " ==============" << std::endl;
        for(auto row : map) {
          for(auto c : row) {
            std::cout << c;
          }
          std::cout << std::endl;
        }
        std::cout << "=============================" << std::endl << std::endl;
 */
      std::swap(
        map[guard.pos.first][guard.pos.second],
        map[update.first][update.second]);
      guard.pos = update;
      steps++;
    }
    guard.turnRight();
  }

  return steps <= 50000;
}

int main() {
  int loopcount = 0;
  parseFile();

  for(int i = 0; i < globalmap.size(); i++) {
    std::cout << "Heartbeat(" << i << ")" << std::endl;
    for(int j = 0; j < globalmap.at(0).size(); j++) {
      std::vector<std::vector<char>> loopmap = globalmap;
      guard.reset();
      //std::cout << "Heartbeat(" << i << ", " << j << ")" << std::endl;
      if(globalmap[i][j] == '.') {
        loopmap[i][j] = 'O';

        bool foundNoLoop = guardRun(loopmap);
        if(!foundNoLoop) {
          loopcount++;
        }

        /* std::cout << std::endl << "============== " << "LOOPMAP" << " ==============" << std::endl;
        for(auto row : loopmap) {
          for(auto c : row) {
            std::cout << c;
          }
          std::cout << std::endl;
        }
        std::cout << "==============LOOP:" << foundNoLoop << "===============" << std::endl << std::endl; */
      }
    }
  }

  std::cout << "Loops: " << loopcount << std::endl;



  return 0;
}

