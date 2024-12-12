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

std::vector<std::vector<char>> tiles;
std::vector<std::vector<bool>> visited;

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    while(std::getline(file, line)) {
        std::vector<char> linemap;
        std::vector<bool> visitline;
        std::stringstream linestream(line);
        std::string word;

        for ( char c : line ) {
            linemap.push_back(c);
            visitline.push_back(false);
        }
        tiles.push_back(linemap);
        visited.push_back(visitline);
    }
}

void print() {
    for(auto r : tiles) {
        for(auto c : r) {
            std::cout << c << "";
        }
        std::cout << std::endl;
    }
}

void printRegions(std::vector<std::vector<bool>> regions) {
    std::cout << std::endl;
    for(auto r : regions) {
        for(auto c : r) {
            std::cout << c << "";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::pair<int, int> getValues(int i, int j, char c, std::vector<std::vector<bool>> &region) {
    if (i < 0 || i >= region.size() || j < 0 || j >= region[i].size()) {
        return {0, 1};
    }

    if (tiles[i][j] != c) {
        return {0, 1};
    }

    if (region[i][j]) {
        return {0, 0};
    }

    region[i][j] = true;
    visited[i][j] = true;

    auto left = getValues(i, j-1, c, region);
    auto right = getValues(i, j+1, c, region);
    auto up = getValues(i-1, j, c, region);
    auto down = getValues(i+1, j, c, region);

    int area = 1 + left.first + right.first + up.first + down.first;
    int perimeter = left.second + right.second + up.second + down.second;


    return {area, perimeter};
}

bool isCorner(bool ul, bool ur, bool ll, bool lr) {
    int sum = ul + ur + ll + lr;
    return sum % 2 != 0;
}

bool isEdgecase(bool ul, bool ur, bool ll, bool lr) {
    return (ul == 1 && ur == 0 && ll == 0 && lr == 1 ) ||
        (ul == 0 && ur == 1 && ll == 1 && lr == 0 );
}

int countcorners(std::vector<std::vector<bool>> region) {
    std::vector<bool> y(region[0].size(), false);
    region.insert(region.begin(), y);
    region.insert(region.begin(), y);
    region.insert(region.end(), y);
    region.insert(region.end(), y);

    int cornersum = 0;

    for(int i = 0; i < region.size(); i++) {
        region[i].insert(region[i].begin(), false);
        region[i].insert(region[i].begin(), false);
        region[i].insert(region[i].end(), false);
        region[i].insert(region[i].end(), false);
    }

    for(int i = 1; i < region.size()-1; i=i+1) {
        for(int j = 1; j < region[i].size()-1; j=j+1) {
            if (isCorner(
                region[i][j],
                region[i][j+1],
                region[i+1][j],
                region[i+1][j+1]
            )) {
                cornersum++;
            } else if(isEdgecase(
            region[i][j],
            region[i][j+1],
            region[i+1][j],
            region[i+1][j+1]
            )) {
                cornersum = cornersum + 2;
            }
        }
    }

    //std::cout << "Ecken: " << cornersum << std::endl;
    //printRegions(region);
    return cornersum;
}

long calculate() {
    long sum = 0;

    for (int i = 0; i < tiles.size(); ++i) {
        for (int j = 0; j < tiles[i].size(); ++j) {
            if ( visited[i][j] == false ) {
                std::vector<std::vector<bool>> region(tiles.size(), std::vector<bool>(tiles[i].size(), false));

                auto vals = getValues(i, j, tiles[i][j], region);
                //std::cout << vals.first << ", " << vals.second << std::endl;
                long corners = countcorners(region);
                long area = vals.first;

                sum += area * corners;

                //printRegions(region);
            }
        }
    }

    return sum;
}

int main() {
    std::cout << "Parsing" << std::endl;
    parseInput();
    //print();
    long sum = calculate();

    std::cout << "Cost: " << sum  << std::endl;

    return 0;
}