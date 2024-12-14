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
    std::pair<int, int> a_button;
    std::pair<int, int> b_button;
    std::pair<int, int> price;
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

            std::pair<int, int> acoords = { std::stol(amatch[1].str()), std::stol(amatch[2].str()) };
            std::pair<int, int> bcoords = { std::stol(bmatch[1].str()), std::stol(bmatch[2].str()) };
            std::pair<int, int> pricecoords = { std::stol(pricematch[1].str()), std::stol(pricematch[2].str()) };

            std::cout << acoords.first << " " << acoords.second << std::endl;
            std::cout << bcoords.first << " " << bcoords.second << std::endl;
            std::cout << pricecoords.first << " " << pricecoords.second << std::endl;

            automata mashine = { acoords, bcoords, pricecoords };
            mashines.push_back(mashine);


            block.clear(); // Reset the block for the next group of lines
        }
    }
}


long findMinPrice(long height, long width, automata m) {
    long min = 999999;

    for (int b = 0; b <= 100; b++) {
        for (int a = 0; a <= 100; a++) {
            long solX =  m.a_button.first * a + m.b_button.first * b;
            long solY =  m.a_button.second * a + m.b_button.second * b;

            if (solX == width && solY == height) {
                long cost = 3 * a + b;

                if (cost < min) {
                    min = cost;
                }
            }
        }
    }

    std::cout << "Minimum price: " << min << std::endl;
    return min;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    //print()

    long sum = 0;

    for (auto &mashine : mashines) {
        std::cout << "goal: " << mashine.price.first << ", " << mashine.price.second << std::endl;
        long cost = findMinPrice(mashine.price.second, mashine.price.first, mashine);
        if (cost < 999999) {
            sum += cost;
        }
    }

    std::cout << "Cost: " << sum  << std::endl;

    return 0;
}