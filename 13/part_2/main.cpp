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

struct automata {
    std::pair<long, long> a_button;
    std::pair<long, long> b_button;
    std::pair<long, long> price;
};

std::vector<automata> mashines;

std::regex coords(R"(X\+(\d+),\s*Y\+(\d+))");
std::regex pricecoords(R"(X\=(\d+),\s*Y\=(\d+))");


void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    std::vector<std::string> block;
    int lineCount = 0;

    // Read the file in blocks of 4 lines
    while (getline(file, line)) {
        block.push_back(line); // Add the current line to the block vector
        lineCount++;

        // When we've read 4 lines, print the block and reset the vector
        if (lineCount % 4 == 0) {
            //std::cout << block[0] << std::endl;
            std::string abuttonstr = block[0];
            std::string bbuttonstr = block[1];
            std::string pricestr = block[2];
            std::smatch amatch;
            std::smatch bmatch;
            std::smatch pricematch;


            std::regex_search(abuttonstr, amatch, coords);
            std::regex_search(bbuttonstr, bmatch, coords);
            std::regex_search(pricestr, pricematch, pricecoords);

            std::pair<long, long> acoords = { std::stol(amatch[1].str()), std::stol(amatch[2].str()) };
            std::pair<long, long> bcoords = { std::stol(bmatch[1].str()), std::stol(bmatch[2].str()) };
            std::pair<long, long> pricecoords = { std::stol(pricematch[1].str()) + 10000000000000, std::stol(pricematch[2].str()) + 10000000000000 };

            std::cout << acoords.first << " " << acoords.second << std::endl;
            std::cout << bcoords.first << " " << bcoords.second << std::endl;
            std::cout << pricecoords.first << " " << pricecoords.second << std::endl;

            automata mashine = { acoords, bcoords, pricecoords };
            mashines.push_back(mashine);


            block.clear(); // Reset the block for the next group of lines
        }
    }
}

std::pair<long, long> solve(automata mashine) {
    long ax = mashine.a_button.first;
    long ay = mashine.a_button.second;

    long bx = mashine.b_button.first;
    long by = mashine.b_button.second;

    long px = mashine.price.first;
    long py = mashine.price.second;

    long a = (px * by - py * bx) / (ax * by - ay * bx);
    long b = (px - a * ax) / bx;

    if (a < 0 || b < 0  || a * ax + b * bx != px || a * ay + b * by != py) {
        return { -1, -1 };
    }

    return { a, b };
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    //print()

    long sum = 0;

    for (auto &mashine : mashines) {
        std::cout << "goal: " << mashine.price.first << ", " << mashine.price.second << std::endl;
        auto presses = solve(mashine);
        if (presses.first > 0 && presses.second > 0) {
            sum += 3* presses.first + presses.second;
        }
    }

    std::cout << "Cost: " << sum  << std::endl;

    return 0;
}