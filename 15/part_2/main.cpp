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

#define FILENAME "input.txt"

std::vector<std::vector<char>> map;
std::string directions;
std::pair<int, int> position;


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
            if (line[i] == '@') {
                row.push_back('@');
                row.push_back('.');
            }

            if (line[i] == '#' || line[i] == '.') {
                row.push_back(line[i]);
                row.push_back(line[i]);
            }

            if (line[i] == 'O') {
                row.push_back('[');
                row.push_back(']');
            }
        }
        map.push_back(row);
        row.clear();
        j++;
    }

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '@') {
                position.first = i;
                position.second = j;
            }
        }
    }

    while (getline(file, line)) {
        std::string toAppend = line;
        if (!toAppend.empty() && toAppend[toAppend.length()-1] == '\n') {
            toAppend.erase(toAppend.length()-1);
        }
        directions += toAppend;
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

void printDirections() {
    for (int i = 0; i < directions.size(); i++) {
        std::cout << directions[i];
    }
    std::cout << std::endl;
}

void printPlayerPos() {
    std::cout << "Player at: (" << position.first << ", " << position.second << ")" << std::endl;
}

bool checkMove(std::pair<int, int> pos, std::pair<int, int> newPos, std::pair<int, int> veloc, bool secondpartofcrate) {
    if (newPos.first >= map.size() || newPos.second >= map[0].size()) {
        return false;
    }

    if (map[pos.first][pos.second] == '#') {
        return false;
    }

    if (map[pos.first][pos.second] == '.') {
        return true;
    }

    bool canMove = true;

    if (veloc.first == -1 && veloc.second == 0 || veloc.first == 1 && veloc.second == 0) {
        if (map[pos.first][pos.second] == '[' && !secondpartofcrate) {
            std::pair<int, int> secboxhalf = { pos.first, pos.second + 1 };
            canMove = canMove && checkMove(secboxhalf, { secboxhalf.first + veloc.first, secboxhalf.second + veloc.second }, veloc, true);
        }

        if (map[pos.first][pos.second] == ']' && !secondpartofcrate) {
            std::pair<int, int> secboxhalf = { pos.first, pos.second - 1 };
            canMove = canMove && checkMove( secboxhalf, { secboxhalf.first + veloc.first, secboxhalf.second + veloc.second }, veloc, true);
        }
    }

    canMove = canMove && checkMove(newPos, { newPos.first + veloc.first, newPos.second + veloc.second }, veloc, false);


    return canMove;
}

void move(std::pair<int, int> pos, std::pair<int, int> newPos, std::pair<int, int> veloc, bool secondpartofcrate) {
    if (newPos.first >= map.size() || newPos.second >= map[0].size()) {
        return;
    }

    if (map[pos.first][pos.second] == '#') {
        return;
    }

    if (map[pos.first][pos.second] == '.') {
        return;
    }

    if (veloc.first == -1 && veloc.second == 0 || veloc.first == 1 && veloc.second == 0) {
        if (map[pos.first][pos.second] == '[' && !secondpartofcrate) {
            std::pair<int, int> secboxhalf = { pos.first, pos.second + 1 };
            move(secboxhalf, { secboxhalf.first + veloc.first, secboxhalf.second + veloc.second }, veloc, true);
        }

        if (map[pos.first][pos.second] == ']' && !secondpartofcrate) {
            std::pair<int, int> secboxhalf = { pos.first, pos.second - 1 };
            move( secboxhalf, { secboxhalf.first + veloc.first, secboxhalf.second + veloc.second }, veloc, true);
        }
    }

    move(newPos, { newPos.first + veloc.first, newPos.second + veloc.second }, veloc, false);

    char c = map[pos.first][pos.second];
    map[pos.first][pos.second] = map[newPos.first][newPos.second];
    map[newPos.first][newPos.second] = c;

    position.first = newPos.first;
    position.second = newPos.second;
    //printMap(map);
}

void calcMove() {
    for (int d = 0; d < directions.size(); d++) {
        std::cout << std::endl;
        std::cout << "Next move: " << directions[d] << std::endl;

        if (directions[d] == '^') {
            bool isValid = checkMove(position, std::make_pair(position.first - 1, position.second), { -1, 0 }, false);
            if (isValid) {
                move(position, std::make_pair(position.first - 1, position.second), { -1, 0 }, false);
            }
        }else if (directions[d] == 'v') {
            bool isValid = checkMove(position, std::make_pair(position.first + 1, position.second), { 1, 0 }, false);
            if (isValid) {
                move(position, std::make_pair(position.first + 1, position.second), { 1, 0 }, false);
            }
        }else if (directions[d] == '>') {
            bool isValid = checkMove(position, std::make_pair(position.first, position.second + 1), { 0, 1 }, false);
            if (isValid) {
                move(position, std::make_pair(position.first, position.second + 1), { 0, 1 }, false);
            }
        }else if (directions[d] == '<') {
            bool isValid = checkMove(position, std::make_pair(position.first, position.second - 1), { 0, -1 }, false);
            if (isValid) {
                move(position, std::make_pair(position.first, position.second - 1), { 0, -1 }, false);
            }
        }
        printMap(map);
    }
}

long calcGPS() {
    long sum = 0;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == '[') {
                sum += 100 * i + j;
            }
        }
    }

    return sum;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    printMap(map);
    printDirections();
    printPlayerPos();

    calcMove();
    long gpssum = calcGPS();

    std::cout << "GPS Sum: " << gpssum  << std::endl;

    return 0;
}