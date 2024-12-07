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

#define FILENAME "example.txt"

enum class Operation {
    PLUS,
    MULT,
};

std::vector<std::vector<long>> equations;

int getBit(int n, int k) {
    return (n & (1<<k)) != 0;
}

long parse(std::string exp) {
    long result = 0;
    int i=0;
    std::string num = "";
    Operation nextOp = Operation::PLUS;
    bool calc = false;
    int digitcount = 0;

    for(int i=0; i < exp.size(); i++) {
        if(isdigit(exp[i])) {
            //std::cout << exp[i] - '0' << std::endl;
            num += exp[i];
            digitcount++;
        }

        if(exp[i] == '+' || exp[i] == '*') {
            if(nextOp == Operation::PLUS) {
                result += atol(num.c_str());
            }else{
                result *= atol(num.c_str());
            }

            //std::cout << "parsed num: " << num << std::endl;
            if(exp[i] == '+') {
                //std::cout << "parsed op: +" << std::endl;
                nextOp = Operation::PLUS;
            }else{
                //std::cout << "parsed op: *" << std::endl;
                nextOp = Operation::MULT;
            }

            num="";
            digitcount=0;
        }
    }

    //std::cout << "parsed num: " << num << std::endl;


    return result;
}

long calculate() {
    long combined;

    for(auto singleequation : equations) {
        long result = singleequation[0];
        std::vector<long> values(singleequation.begin()+1, singleequation.end());
        int maximalOperations = pow(2, values.size() - 1);

        bool found = false;
        int i = 0;
        while(i < maximalOperations && !found) {
            std::string exp;
            long eqres = 0;


            for(int j = 0; j < values.size(); j++) {
                exp.append(std::to_string(values[j]));
                if(j != values.size() - 1) {
                    if(getBit(i, j) == 0 ){
                        exp.append("+");
                    }else{
                        exp.append("*");
                    }
                }
            }

            long calced = parse(exp + "+");
            if(calced == result) {
                combined += calced;
                found = true;
            }
            //std::cout << exp + "+" << " => \n" << parse(exp + "+") << std::endl;
            i++;
        }
    }

    return combined;
}

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

    // read in the data and save the numbers to the respective lists
    while(std::getline(file, line)) {
        std::vector<long> singleeq;
        std::stringstream linestream(line);
        std::string word;

        while (linestream >> word) {
            singleeq.push_back(std::stol(word));
        }

        equations.push_back(singleeq);
    }

}


int main() {
    parseInput();

    long result = calculate();
    std::cout << "Result: " << result << std::endl;

}