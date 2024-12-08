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
std::vector<std::vector<char>> animation;
std::vector<std::pair<int, int>> candidates;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::vector<char> linemap;
        std::stringstream linestream(line);
        std::string word;

        for ( char c : line ) {
            linemap.push_back(c);
        }

        map.push_back(linemap);
        animation.push_back(linemap);
    }
}

int manhattendistance(std::pair<int, int> pointA, std::pair<int, int> pointB) {
    return abs(pointA.first - pointB.first) + abs(pointA.second - pointB.second);
}

void findCandidates() {
    for(int i = 0; i < map.size(); i++) {
        for(int j = 0; j < map[i].size(); j++) {
            if (isdigit(map[i][j]) || isalpha(map[i][j])) {
                candidates.push_back({i, j});
            }
        }
    }
}

void print() {
    std::cout << "===============" << std::endl;
    for(auto row : animation) {
        for( auto c : row) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
    std::cout << "===============" << std::endl << std::endl;
}

void findAntinodes() {
    for(int i = 0; i < candidates.size(); i++) {
        for (int j = 0; j < candidates.size(); j++) {
            if (i != j) {
                std::pair<int, int> pointA = candidates[i];
                std::pair<int, int> pointB = candidates[j];

                if (map[pointA.first][pointA.second] == map[pointB.first][pointB.second]) {
                    int dx = pointB.second - pointA.second;
                    int dy = pointB.first - pointA.first;

                    for (int m=0; m < map.size(); m++) {
                        std::pair<int, int> antiA = { pointA.first + m*dy, pointA.second + m*dx };
                        //std::pair<int, int> antiB = { pointB.first + dy, pointB.second + dx };

                        if (antiA.first >= 0 && antiA.first < map.size() && antiA.second >= 0 && antiA.second < map[0].size()) {
                            animation[antiA.first][antiA.second] = '#';
                            print();
                        }
                    }

                    /*if (antiB.first != pointB.first && antiB.second != pointB.second)  {
                        if (antiB.first >= 0 && antiB.first < map.size() && antiB.second >= 0 && antiB.second < map[i].size()) {
                            if (map[antiB.first][antiB.second] != '#' && (!isdigit(map[antiB.first][antiB.second]) && !isalpha(map[antiB.first][antiB.second]))) {
                                antinodes.push_back(antiB);
                                animation[antiB.first][antiB.second] = '#';
                                print();
                                count++;
                            }
                        }
                    }*/
                }
            }
        }
    }
}

int main() {
    parseInput();

    findCandidates();

    std::cout << "Candidates found: " << std::endl;
    for (auto c : candidates) {
        std::cout << c.first + 1 << ' ' << c.second + 1 << std::endl;
    }

    findAntinodes();
    int foundNodes = 0;

    for (auto row : animation) {
        for (auto c : row) {
            if (c == '#') {
                foundNodes++;
            }
        }
    }

    std::cout << "Antinodes found: " << std::endl;


    std::cout << "Antinodes count: " << foundNodes << std::endl;
    return 0;
}