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

std::vector<std::pair<int, int>> rules;
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


        rules.push_back(std::pair<int, int>(atoi(key.c_str()), atoi(rule.c_str())));
    }
}

void parseUpdates() {
    // Parse the file
    std::ifstream file("input_q.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;
        std::vector<int> row;

        while( linestream.good() ) {
            std::string substr;
            std::getline( linestream, substr, ',' );
            row.push_back( atoi(substr.c_str()) );
        }

        updates.push_back(row);
    }
}

bool isRuleInValid(std::vector<int> row, std::pair<int, int> rule) {
    auto itkey = std::find(row.begin(), row.end(), rule.first);
    auto itval = std::find(row.begin(), row.end(), rule.second);

    // Check if both numbers are contained
    if(itkey != row.end() && itval != row.end()) {
        int indexKey = itkey - row.begin();
        int indexVal = itval - row.begin();

        if(indexKey > indexVal) {
            return true;
        }
    }

    return false;
}

std::vector<int> resort(std::vector<int> &row, std::pair<int, int> rule) {
    auto itkey = std::find(row.begin(), row.end(), rule.first);
    auto itval = std::find(row.begin(), row.end(), rule.second);

    // Check if both numbers are contained
    if(itkey != row.end() && itval != row.end()) {
        int indexKey = itkey - row.begin();
        int indexVal = itval - row.begin();

        if(indexKey > indexVal) {
            std::swap(row[indexKey], row[indexVal]);
        }
    }

    return row;
}


int main() {
    long sum = 0; 

    parseRules();
    parseUpdates();

    std::vector<std::vector<int>> doesNotApply;

    std::copy_if(updates.begin(), updates.end(), std::back_inserter(doesNotApply), 
        [](std::vector<int> i){
            bool inValid = false;
            for(auto rule : rules) {
                bool check = isRuleInValid(i, rule);
                inValid = inValid || isRuleInValid(i, rule);
                if(check) {
                    //std::cout << rule.first << ", " << rule.second << std::endl;
                }
            }
            return inValid;
        } 
    );

    std::vector<bool> validity;

    for(int i = 0; i < doesNotApply.size(); i++) {
        validity.push_back(false);
    }

    for(int i = 0; i < doesNotApply.size(); i++) {
        bool allrulesapply = false;
        while(!allrulesapply) {
            int errors = 0;
            for(auto rule : rules) {
                bool invalid = isRuleInValid(doesNotApply[i], rule);
                //std::cout << i << ":" << invalid << std::endl;

                if(invalid) {
                   doesNotApply[i] = resort(doesNotApply[i], rule);
                   errors++;
                }
            }

            allrulesapply = errors == 0;
            std::cout << allrulesapply << std::endl;
        }
    }
    

    for (std::vector<int> row : doesNotApply) {
        for(int elm : row) {
            std::cout << elm << ", ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    for (std::vector<int> row : doesNotApply) {
        auto mid = row.begin() + row.size() / 2;
        sum += *mid;
        std::cout << "mid: " << *mid << std::endl; 
    }

    std::cout << "Sum: " << sum << std::endl; 

    return 0;
}