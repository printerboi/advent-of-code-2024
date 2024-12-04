#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <cmath>
#include <cassert>

int starSearch(std::vector<std::vector<char>> &mem) {
    int counter = 0;

    for (int i = 0; i < mem.size(); i++) {
        for (int j=0; j < mem.at(i).size(); j++) {
            if ( mem[i][j] == 'A' ) {
                std::string ultolr;
                std::string lltour;

                if ( i >= 1 && i < mem.size()-1 ) {
                    ultolr = { mem[i-1][j-1], mem[i][j], mem[i+1][j+1]};
                    lltour = { mem[i+1][j-1], mem[i][j], mem[i-1][j+1]};
                }

                // std::cout << ultolr << std::endl;
                // std::cout << lltour << std::endl;

                if(( ultolr == "MAS" || ultolr == "SAM" )  && ( lltour == "MAS" || lltour == "SAM" ) ) {
                    counter++;
                    std::cout<<i<<", "<<j<<std::endl;
                }

            }
        }
    }

    std::cout << "Star: " << counter << std::endl;

    return counter;
}


int main() {
    // Parse the file
    std::vector<std::vector<char>> mem;
    std::ifstream file("input.txt");
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

    starSearch(mem);


    return 0;
}