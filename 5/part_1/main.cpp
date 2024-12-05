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

std::map<int, std::vector<int>> rules;
std::vector<std::vector<int>> updates;

void parseRules() {
    // Parse the file
    std::ifstream file("input_rules.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;

        std::string key = line.substr(0, line.find('|'));
        std::string rule = line.substr(line.find('|')+1, line.length());


        rules[atoi(key.c_str())].push_back(atoi(rule.c_str()));
    }

/*     for(auto const &r : rules) {
        std::cout << "Key: " << r.first << "|";
        for(auto const &a : r.second) {
            std::cout << a << ", ";
        }
        std::cout << std::endl;
    } */
}

void parseUpdates() {
    // Parse the file
    std::ifstream file("input_q.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;
        std::vector<int> row;

        //std::cout << linestream.str() << std::endl;

        while( linestream.good() ) {
            std::string substr;
            std::getline( linestream, substr, ',' );
            row.push_back( atoi(substr.c_str()) );
        }

        /* for(int elm : row) {
            std::cout << elm << ", ";
        }

        std::cout << std::endl; */

        updates.push_back(row);
    }
}

std::vector<std::vector<int>> ruleDoesApply(){
    std::vector<std::vector<int>> corordered;
    
    for(auto row: updates) {
        bool applies = true;

        for(auto rule: rules) {
            int key = rule.first;
            std::vector<int> values = rule.second;

            for(auto val : values) {
                auto itkey = std::find(row.begin(), row.end(), key);
                auto itval = std::find(row.begin(), row.end(), val);

                // Check if both numbers are contained
                if(itkey != row.end() && itval != row.end()) {
                    int indexKey = itkey - row.begin();
                    int indexVal = itval - row.begin();

                    //std::cout << "Between " << indexKey << " and " << indexVal << std::endl;

                    if(indexKey > indexVal) {
                        std::cout << "Violation in ";
                        for(int elm : row) {
                            std::cout << elm << ", ";
                        }
                        std::cout << "Between " << key << " and " << val << std::endl;

                        applies = false;
                    }
                }
            }
        }

        if(applies) {
            corordered.push_back(row);
        }
    }

    return corordered;
    
}

int main() {
    long sum = 0; 

    parseRules();
    parseUpdates();

    std::vector<std::vector<int>> appliesto = ruleDoesApply();

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for (std::vector<int> row : appliesto) {
        for(int elm : row) {
            std::cout << elm << ", ";
        }

        std::cout << std::endl;
    }

    for (std::vector<int> row : appliesto) {
        auto mid = row.begin() + row.size() / 2;
        sum += *mid;
        std::cout << "mid: " << *mid << std::endl; 
    }

    std::cout << "Sum: " << sum << std::endl; 

    return 0;
}