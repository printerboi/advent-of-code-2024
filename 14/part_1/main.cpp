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

int width = 101;
int height = 103;
int seconds = 100;

struct robot {
    std::pair<int, int> pos;
    std::pair<int, int> speed;
};

std::vector<robot> robots;

std::regex coords(R"(p=(-?\d+),(-?\d+)\s+v=(-?\d+),(-?\d+))");


void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    std::vector<std::string> block;

    // Read the file in blocks of 4 lines
    while (getline(file, line)) {
        block.push_back(line); // Add the current line to the block vector
        std::smatch matches;

        std::regex_search(line, matches, coords);

        std::pair<int, int> pos = { std::atoi(matches[1].str().c_str()), std::atoi(matches[2].str().c_str()) };
        std::pair<int, int> speed = { std::atoi(matches[3].str().c_str()), std::atoi(matches[4].str().c_str()) };

        //std::cout << pos.first << " " << pos.second << std::endl;
        //std::cout << speed.first << " " << speed.second << std::endl;

        robot mashine = { pos, speed };
        robots.push_back(mashine);


    }
}

int mod(int a, int b) {
    if (a < 0) {
        return ( -1 * a ) % b;
    }

    if (b < 0) {
        return ( -1 * a ) % b;
    }

    return a % b;
}

void updateRobotPos(robot &robot) {
    // x(t) = x + t * v;
    // (x + t * v) % SIZE

    int x = robot.pos.first + seconds * robot.speed.first;
    int y = robot.pos.second + seconds * robot.speed.second;

    robot.pos = { ((x % width) + width) % width, ((y % height) + height) % height };
}


int calcRobotQuads() {
    int ul = 0;
    int ur = 0;
    int ll = 0;
    int lr = 0;

    for (robot robot : robots) {
        if (robot.pos.first < width/2 && robot.pos.second < height/2) {
            ul++;
        }

        if (robot.pos.first > width/2 && robot.pos.second < height/2) {
            ur++;
        }

        if (robot.pos.first < width/2 && robot.pos.second > height/2) {
            ll++;
        }

        if (robot.pos.first > width/2 && robot.pos.second > height/2) {
            lr++;
        }
    }

    return ul * ur * ll * lr;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    //print()

    long sum = 0;

    for (auto &robot : robots) {
        updateRobotPos(robot);
    }

    for (auto &robot : robots) {
        //std::cout << robot.pos.first << " " << robot.pos.second << std::endl;
    }

    std::cout << "Sum: " << calcRobotQuads() << std::endl;

    return 0;
}