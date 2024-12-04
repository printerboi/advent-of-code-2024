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

void print(std::vector<std::vector<char>> &mem) {
    std::vector<std::vector<char>>::iterator row;
    std::vector<char>::iterator col;
    for (row = mem.begin(); row != mem.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            std::cout << *col;
        }
        std::cout << std::endl;
    }
}

int searchForward(std::vector<std::vector<char>> &mem) {
    int counter = 0;
    std::vector<std::vector<char>>::iterator row;
    std::regex regex("XMAS");

    for (row = mem.begin(); row != mem.end(); row++) {
        std::string rowstring = std::accumulate(row->begin(), row->end(), std::string(), [](const std::string &a, char b) { return a + b; });
        std::ptrdiff_t const match_count(std::distance(std::sregex_iterator(rowstring.begin(), rowstring.end(), regex), std::sregex_iterator()));
        counter = counter + match_count;
    }

    std::cout << "Forward: " << counter << std::endl;

    return 0;
}

int searchBackward(std::vector<std::vector<char>> &mem) {
    int counter = 0;
    std::vector<std::vector<char>>::reverse_iterator row;
    std::regex regex("SAMX");

    for (row = mem.rbegin(); row != mem.rend(); row++) {
        std::string rowstring = std::accumulate(row->begin(), row->end(), std::string(), [](const std::string &a, char b) { return a + b; });
        std::ptrdiff_t const match_count(std::distance(std::sregex_iterator(rowstring.begin(), rowstring.end(), regex), std::sregex_iterator()));
        counter = counter + match_count;
    }

    std::cout << "Backwards: " << counter << std::endl;

    return 0;
}

int starSearch(std::vector<std::vector<char>> &mem){
    int counter = 0;

    for(int i = 0; i < mem.size(); i++) {
        for(int j=0; j < mem.at(i).size(); j++) {
            char marker = mem[i][j];

            if(marker == 'X' || marker == 'S') {
                //Check left
                std::string west;
                std::string east;
                std::string north;
                std::string south;

                std::string ne;
                std::string es;
                std::string sw;
                std::string wn;
                
                if(j < mem.at(i).size()-3){ east = { mem[i][j], mem[i][j+1], mem[i][j+2], mem[i][j+3] };}

                if(j > 3) { west = { mem[i][j-3], mem[i][j-2], mem[i][j-1], mem[i][j] };}

                if(i < mem.size()-3){south = { mem[i][j], mem[i+1][j], mem[i+2][j], mem[i+3][j] };}

                if(i > 3) {north = { mem[i-3][j], mem[i-2][j], mem[i-1][j], mem[i][j] };}

                if(j < mem.at(i).size()-3 && i > 3) {
                    ne = { mem[i][j], mem[i-1][j+1], mem[i-2][j+2], mem[i-3][j+3]};
                }

                if(j < mem.at(i).size()-3 && i < mem.size()-3) {
                    es = { mem[i][j], mem[i+1][j+1], mem[i+2][j+2], mem[i+3][j+3]};
                }

                if(j > 3 && i < mem.size()-3) {
                    sw = { mem[i][j], mem[i+1][j-1], mem[i+2][j-2], mem[i+3][j-3]};
                }

                if(i > 3 && j > 3) {
                    wn = { mem[i][j], mem[i-1][j-1], mem[i-1][j-2], mem[i-1][j-3]};
                }

                std::cout << "\tNE: " << ne << " " << i << "," << j << std::endl;
                //std::cout << "\tEast: " << east << std::endl;
                //std::cout << "\tNorth: " << north << std::endl;
                //std::cout << "\tSouth: " << south << std::endl;

                if(east == "XMAS" || east == "SAMX") { counter++; }
                if(west == "SAMX" || west == "XMAS") { counter++; }
                if(north == "XMAS" || north == "SAMX") { counter++; }
                if(south == "SAMX" || south == "XMAS") { counter++; }




            }
        }
    }

    std::cout << "Star: " << counter << std::endl;

    return counter;
}


int main() {
    // Parse the file
    std::vector<std::vector<char>> mem;
    std::ifstream file("example.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;
        std::vector<char> row;

        for(char c : line) {
            row.push_back(c);
        }

        mem.push_back(row);
    }

    searchForward(mem);
    searchBackward(mem);
    starSearch(mem);


    return 0;
}