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

struct FileData {
    int id;
    int length;
};

std::vector<std::pair<int, int>> starts;
std::vector<std::pair<int, int>> ends;
std::vector<std::vector<int>> map;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::vector<int> linemap;
        std::stringstream linestream(line);
        std::string word;

        for ( char c : line ) {
            linemap.push_back((int) c - '0');
        }

        map.push_back(linemap);
    }
}

void print(std::vector<std::vector<int>> map) {
    for(auto r : map) {
        for (auto v : r) {
            std::cout << v;
        }
        std::cout << std::endl;
    }
}

void findStartingpoints() {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j] == 0) {
                starts.push_back(std::make_pair(i, j));
            }
        }
    }

    /*for (int i = starts.size() - 1; i >= 0; i--) {
        std::cout << starts[i].first << " " << starts[i].second << std::endl;
    }*/
}

bool endalredyvisited(int i, int j) {
    for (int k = 0; k < ends.size(); k++) {
        if (ends[k].first == i && ends[k].second == j) {
            return true;
        }
    }

    return false;
}

int getScroreOfPoints(int i, int j) {
    if (i < 0 || j < 0 || i >= map.size() || j >= map[i].size()) {
        return 0;
    }

    if (map[i][j] == 9) {
        ends.push_back(std::make_pair(i, j));
        return 1;
    }


    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;

    if (j >=1 && map[i][j-1] == map[i][j] + 1) {
        left = getScroreOfPoints(i, j-1);
    }

    if (j < map[i].size()-1 && map[i][j+1] == map[i][j] + 1) {
        right = getScroreOfPoints(i, j+1);
    }

    if (i >= 1 && map[i-1][j] == map[i][j] + 1) {
        up = getScroreOfPoints(i-1, j);
    }

    if (i < map.size()-1 && map[i+1][j] == map[i][j] + 1) {
        down = getScroreOfPoints(i+1, j);
    }

    return left + right + up + down;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    //print(map);
    findStartingpoints();

    int sum = 0;
    for (int i = 0; i < starts.size(); i++) {
        sum += getScroreOfPoints(starts[i].first, starts[i].second);
        ends.clear();
    }

    std::cout << "Score: " << sum  << std::endl;

    return 0;
}