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

std::vector<std::string> stones;
std::map<int, int> lookup;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string word;

        while (linestream >> word) {
            stones.push_back(word);
        }
    }
}

void print(std::vector<std::string> stones) {
    for(auto s : stones) {
        std::cout << s << std::endl;
    }
}



int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    print(stones);

    for (int i = 0; i < 25; i++) {
        std::vector<std::string> nstones;

        for(int j = 0; j < stones.size(); j++) {
            if (stones[j] == "0"  ) {
                nstones.push_back("1");
            }else if ( stones[j].size() % 2 == 0 ) {
                std::string firsthalf = stones[j].substr(0, stones[j].size() / 2);
                std::string secondhalf = stones[j].substr(stones[j].size() / 2, stones[j].size() / 2);

                int valleft = std::stol(firsthalf);
                int valright = std::stol(secondhalf);

                nstones.push_back(std::to_string(valleft));
                nstones.push_back(std::to_string(valright));
            }else {
                long val = atol(stones[j].c_str());
                long nval = val * 2024;
                std::string updatedStones = std::to_string(nval);
                nstones.push_back(updatedStones);
            }
        }

        stones = nstones;
        nstones.clear();
    }

    std::cout << "Stones " << stones.size() << std::endl;

    return 0;
}