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
            row.push_back(line[i]);
            if (line[i] == '@') {
                position.first = j;
                position.second = i;
            }
        }
        map.push_back(row);
        row.clear();
        j++;
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

bool performMove(std::pair<int, int> pos, std::pair<int, int> newPos, std::pair<int, int> veloc) {
    if (newPos.first >= map.size() || newPos.second >= map[0].size()) {
        return false;
    }

    if (map[pos.first][pos.second] == '#') {
        return false;
    }

    if (map[pos.first][pos.second] == '.') {
        return true;
    }

    bool canMove = performMove(newPos, { newPos.first + veloc.first, newPos.second + veloc.second }, veloc);
    if (canMove) {
        char c = map[pos.first][pos.second];
        map[pos.first][pos.second] = map[newPos.first][newPos.second];
        map[newPos.first][newPos.second] = c;

        position.first = newPos.first;
        position.second = newPos.second;

        return true;
    }

    return false;
}

void calcMove() {
    for (int d = 0; d < directions.size(); d++) {
        std::cout << std::endl;
        std::cout << "Next move: " << directions[d] << std::endl;

        if (directions[d] == '^') {
            performMove(position, std::make_pair(position.first - 1, position.second), { -1, 0 });
        }else if (directions[d] == 'v') {
            performMove(position, std::make_pair(position.first + 1, position.second), { 1, 0 });
        }else if (directions[d] == '>') {
            performMove(position, std::make_pair(position.first, position.second + 1), { 0, 1 });
        }else if (directions[d] == '<') {
            performMove(position, std::make_pair(position.first, position.second - 1), { 0, -1 });
        }

        printMap(map);
    }
}

long calcGPS() {
    long sum = 0;

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 'O') {
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