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


struct BmpHeader {
    char bitmapSignatureBytes[2] = {'B', 'M'};
    uint32_t sizeOfBitmapFile = 54 + 31209;
    uint32_t reservedBytes = 0;
    uint32_t pixelDataOffset = 54;
} bmpHeader;

struct BmpInfoHeader {
    uint32_t sizeOfThisHeader = 40;
    int32_t width = 101; // in pixels
    int32_t height = 103; // in pixels
    uint16_t numberOfColorPlanes = 1; // must be 1
    uint16_t colorDepth = 24;
    uint32_t compressionMethod = 0;
    uint32_t rawBitmapDataSize = 0; // generally ignored
    int32_t horizontalResolution = 3780; // in pixel per meter
    int32_t verticalResolution = 3780; // in pixel per meter
    uint32_t colorTableEntries = 0;
    uint32_t importantColors = 0;
} bmpInfoHeader;


struct PixelWhite {
    uint8_t blue = 255;
    uint8_t green = 255;
    uint8_t red = 0;
} pixelW;


struct PixelBlack {
    uint8_t blue = 0;
    uint8_t green = 0;
    uint8_t red = 0;
} pixelB;




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

void updateRobotPos(robot &robot, int sec) {
    // x(t) = x + t * v;
    // (x + t * v) % SIZE

    int x = robot.pos.first + sec * robot.speed.first;
    int y = robot.pos.second + sec * robot.speed.second;

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
    //std::cout << "Parsing" << std::endl;
    parseInput();
    //print()

    long sum = 0;

    long seconds = 10000;

    for (long s = 0; s < seconds; s=s+1) {
        std::vector<std::vector<bool>> grid = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));

        for (robot robot : robots) {
            updateRobotPos(robot, s);
            grid[robot.pos.second][robot.pos.first] = true;
        }

        std::string filename = "output_" + std::to_string(s) +  ".ppm";

        constexpr auto dimx = 101u, dimy = 103u;

        std::ofstream ofs(filename, std::ios_base::out | std::ios_base::binary);
        ofs << "P6\n" << dimx << ' ' << dimy << "\n255\n";

        //std::cout << std::endl;
        //std::cout << "============= sec: " << s << " =================" <<  std::endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (grid[i][j]) {
                    ofs << static_cast<char>(255)
                << static_cast<char>(0)
                << static_cast<char>(0);
                }else {
                    ofs << static_cast<char>(255)
                << static_cast<char>(255)
                << static_cast<char>(255);
                }

            }
        }

        //std::cout << std::endl;
    }

    return 0;
}