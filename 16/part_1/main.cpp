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

#define FILENAME "input.txt"

std::vector<std::vector<char>> map;
std::vector<std::vector<bool>> predsmap;
std::vector<std::pair<int, int>> path;
std::pair<int, int> start;
std::pair<int, int> end;
long globmin = INT_MAX;

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

    predsmap.resize(map.size(), std::vector<bool>(map.size(), false));
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

void printPath(std::vector<std::vector<bool>> locmap) {
    for (int i = 0; i < locmap.size(); i++) {
        for (int j = 0; j < locmap[i].size(); j++) {
            if (locmap[i][j]) {
                std::cout << "█";
            }else if (map[i][j] == '#') {
                std::cout << '#';
            }else {
                std::cout << '.';
            }
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

bool nodeVisited(std::vector<std::pair<int, int>> &preds, std::pair<int, int> node) {
    for (auto n : preds) {
        if (node.first == n.first && node.second == n.second) {
            return true;
        }
    }

    return false;
}

long findShortestPath(std::pair<int, int> pos, DIRECTION dir, std::vector<std::vector<bool>> &preds, long steps) {
    if (map[pos.first][pos.second] == '#' || steps > globmin) {
        return 999999;
    }

    if (map[pos.first][pos.second] == 'E') {
        globmin = steps;
        std::cout << globmin << std::endl;
        return 1;
    }

    long up = 1001;
    long down = 1001;
    long left = 1001;
    long right = 1001;

    if (dir == DIRECTION::UP) {
        up = 1;
    }else if (dir == DIRECTION::DOWN) {
        down = 1;
    }else if (dir == DIRECTION::LEFT) {
        left = 1;
    }else{
        right = 1;
    }

    long goUp = 999999;
    long goDown = 999999;
    long goLeft = 999999;
    long goRight = 999999;

    if (!preds[pos.first-1][pos.second] && steps + up < globmin) {
        auto locmap = preds;
        locmap[pos.first-1][pos.second] = true;
        //printPath(locmap);
        goUp = up + findShortestPath({ pos.first-1, pos.second }, DIRECTION::UP, locmap, steps+up);
    }

    if (!preds[pos.first+1][pos.second] && steps + down < globmin) {
        auto locmap = preds;
        locmap[pos.first+1][pos.second] = true;
        //printPath(locmap);
        goDown = down + findShortestPath({ pos.first+1, pos.second }, DIRECTION::DOWN, locmap, steps+down);
    }

    if (!preds[pos.first][pos.second-1] && steps + left < globmin) {
        auto locmap = preds;
        locmap[pos.first][pos.second-1] = true;
        //printPath(locmap);
        goLeft = left + findShortestPath({ pos.first, pos.second-1 }, DIRECTION::LEFT, locmap, steps+left);
    }

    if (!preds[pos.first][pos.second+1] && steps + right < globmin) {
        auto locmap = preds;
        locmap[pos.first][pos.second+1] = true;
        //printPath(locmap);
        goRight = right + findShortestPath({ pos.first, pos.second+1 }, DIRECTION::RIGHT, locmap, steps+right);
    }

    long min = std::min(goUp, std::min(goDown, std::min(goLeft, goRight)));

    return min;
}

long findShortestIterativPath() {
    std::vector<std::pair<int, int>> nodelist = { start };

    while (nodelist.size() > 0) {
        std::pair<int, int> node = nodelist.front();

        if (map[node.first][node.second] == 'E') {
            break;
        }



    }
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();

    printMap(map);
    printStartPos();
    printEndPos();
    std::vector<std::pair<int, int>> nodes;
    long shortestWay = findShortestPath({ start.first, start.second }, DIRECTION::RIGHT, predsmap, 0);

    std::cout << "SP with sum: " << shortestWay-1  << std::endl;

    return 0;
}