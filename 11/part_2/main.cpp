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

std::map<std::string, long> stones;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string word;

        while (linestream >> word) {
            stones[word] = 1;
        }
    }
}

void print(std::map<std::string, long> stones) {
    for(auto s : stones) {
        std::cout << s.first << "(" << s.second << ")" << ", ";
    }
    std::cout << std::endl;
}


void insertOrIncrement(std::map<std::string, long> &map, std::string key, long size) {
    if (map.find(key) == map.end()) {
        map[key] = size;
    }else {
        map[key] += size;
    }
}


int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    print(stones);

    for (int i = 0; i < 75; i++) {
        std::map<std::string, long> nstones;

        for(auto stone : stones) {
            if (stone.first == "0"  ) {
                insertOrIncrement(nstones, "1", stone.second);
            }else if ( stone.first.size() % 2 == 0 ) {
                std::string firsthalf = stone.first.substr(0, stone.first.size() / 2);
                std::string secondhalf = stone.first.substr(stone.first.size() / 2, stone.first.size() / 2);

                long valleft = std::stol(firsthalf);
                long valright = std::stol(secondhalf);

                insertOrIncrement(nstones, std::to_string(valleft), stone.second);
                insertOrIncrement(nstones, std::to_string(valright), stone.second);
            }else {
                long val = atol(stone.first.c_str());
                long nval = val * 2024;
                std::string updatedStones = std::to_string(nval);
                insertOrIncrement(nstones, updatedStones, stone.second);
            }
        }



        stones = nstones;
        nstones.clear();
    }

    print(stones);

    long sum = 0;
    for(auto stone : stones) {
        sum += stone.second;
    }

    std::cout << "Stones " << sum << std::endl;

    return 0;
}