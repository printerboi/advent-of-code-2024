#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <cmath>
#include <cassert>
#include <bits/stdc++.h>
#include <bitset>
#include <limits.h>

#define FILENAME "example.txt"

std::vector<std::vector<char>> map;
std::pair<int, int> start;
std::pair<int, int> end;

enum class DIRECTION {
    LEFT, RIGHT, UP, DOWN
};


void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;
    std::vector<char> row;

    int j = 0;
    while (getline(file, line)) {
        if (line == "") {
            break;
        }

        for (int i = 0; i < line.size(); i++) {
            row.push_back(line[i]);
            if (line[i] == 'S') {
                start.first = j;
                start.second = i;
            }
            if (line[i] == 'E') {
                end.first = j;
                end.second = i;
            }
        }
        map.push_back(row);
        row.clear();
        j++;
    }
}

void printMap(std::vector<std::vector<char>> map) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void printStartPos() {
    std::cout << "Start at: (" << start.first << ", " << start.second << ")" << std::endl;
}

void printEndPos() {
    std::cout << "End at: (" << end.first << ", " << end.second << ")" << std::endl;
}

long findShortestPath(std::pair<int, int> pos, DIRECTION dir) {
    if (map[pos.first][pos.second] == '#') {
        return INT_MAX;
    }

    if (map[pos.first][pos.second] == 'E') {
        return 1;
    }

    int up = 1000;
    int down = 1000;
    int left = 1000;
    int right = 1000;

    if (dir == DIRECTION::UP) {
        up = 1;
    }else if (dir == DIRECTION::DOWN) {
        down = 1;
    }else if (dir == DIRECTION::LEFT) {
        left = 1;
    }else{
        right = 1;
    }

    int goUp = up + findShortestPath({ pos.first-1, pos.second }, DIRECTION::UP);
    int goDown = down + findShortestPath({ pos.first+1, pos.second }, DIRECTION::DOWN);
    int goLeft = left + findShortestPath({ pos.first, pos.second-1 }, DIRECTION::LEFT);
    int goRight = right + findShortestPath({ pos.first, pos.second+1 }, DIRECTION::RIGHT);
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    printMap(map);
    printStartPos();
    printEndPos();

    std::cout << "SP with sum: " << 0  << std::endl;

    return 0;
}