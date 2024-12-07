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

enum class Operation {
    PLUS,
    MULT,
    CONCAT
};

std::vector<std::vector<long>> equations;

std::vector<int> toTernary(std::vector<int> &converted, int i) {
    int n = i;

    int j=0;
    while (n > 0) {
        converted[converted.size()- 1 - j] = n % 3;
        n = n / 3;
        j++;
    }

    return converted;
}

int getBit(int n, int k) {
    return (n & (1<<k)) != 0;
}

long parse(std::string exp) {
    long result = 0;
    int i=0;
    std::string num = "";
    Operation nextOp = Operation::PLUS;
    bool calc = false;

    for(int i=0; i < exp.size(); i++) {
        if(isdigit(exp[i])) {
            num += exp[i];
        }

        if(exp[i] == '+' || exp[i] == '*' || exp[i] == '|') {
            if(nextOp == Operation::PLUS) {
                result += atol(num.c_str());
            }else if(nextOp == Operation::MULT){
                result *= atol(num.c_str());
            }else {
                result = atol((std::to_string(result) + num).c_str());
            }

            if(exp[i] == '+') {
                nextOp = Operation::PLUS;
                num="";
            }else if(exp[i] == '*'){
                nextOp = Operation::MULT;
                num="";
            }else {
                nextOp = Operation::CONCAT;
                num="";
            }
        }
    }

    return result;
}

long calculate() {
    long combined = 0;

    for(auto singleequation : equations) {
        long result = singleequation[0];
        std::vector<long> values(singleequation.begin()+1, singleequation.end());
        int maximalOperations = pow(3, values.size() - 1);

        bool found = false;
        int i = 0;
        while(i < maximalOperations && !found) {
            std::string exp;
            long eqres = 0;
            std::vector<int> bitsequenceternary(values.size()-1);
            toTernary(bitsequenceternary, i);

            for(int j = 0; j < values.size(); j++) {
                exp.append(std::to_string(values[j]));
                if(j != values.size() - 1) {
                    if(bitsequenceternary[j] == 0){
                        exp.append("+");
                    }else if(bitsequenceternary[j] == 1){
                        exp.append("*");
                    } else {
                        exp.append("|");
                    }
                }
            }


            long calced = parse(exp + "+");
            if(calced == result) {
                combined += calced;
                found = true;
            }
            i++;
        }
    }

    return combined;
}

void parseInput() {
    std::ifstream file(FILENAME);
    std::string line;

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