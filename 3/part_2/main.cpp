#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <regex>
#include <cmath>
#include <cassert>

/**
 * Active var to enable/disable calculation on do() and don't()
 */
bool active = true;

/**
 * Parse a given mul(x,y) string. Iterates over the string from back to frond and calculates the product
 * 
 * @param substring String to be parsed
 */
long parseSubstring(std::string &substring) {
    int i=substring.size();
    int power=0;
    long prod = 1;
    long num = 0;

    // Iterate back to front, to handle power of 10 calculation
    while(i > 0) {
        if(isdigit(substring[i])) {
            num += (substring[i] - '0') * std::pow(10, power);
            power++;
        }

        // Reset power and indicate a new number or the end of the number part
        if(substring[i] == ',' || substring[i] == '(') {
            power = 0;
            prod *= num;
            num=0;
        }

        i--;
    }

    return prod;
}

/**
 * Parse a given list of mul, do, and don't instructions
 * 
 * @param list Vector of instructions to be parsed
 */
long parseList(std::vector<std::string> &list) {
    long sum = 0;

    for(std::string inst : list) {
        // If we encouter a do, enable calculation globally
        if(inst == "do()"){
            active = true;

        // If we encouter a don't, disable calculation globally
        }else if(inst == "don't()"){
            active = false;
        } else {
        // In any other case, parse the mult instruction and calculate the result
            if(active) {
                sum += parseSubstring(inst);
            }
        }
    }

    return sum;
}


int main() {
    // Parse the file
    std::vector<std::string> mem;
    std::ifstream file("input.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;

        while (linestream >> word) {
            mem.push_back(word);
        }
    }

    long long sum = 0;
    // Iterate over the lines in the file
    for(std::string memline : mem) {
        // Perform regex magic...
        std::smatch match;
        std::string subject = memline;
        std::regex regex("(mul\\([0-9]{1,3},[0-9]{1,3}\\))|(do\\(\\)|don't\\(\\))");
        std::vector<std::string> instList;

        // Iterate over regex matches
        for (std::sregex_iterator it = std::sregex_iterator(subject.begin(), subject.end(), regex); it != std::sregex_iterator(); it++) {
            // Extract the match
            std::smatch match;
            match = *it;
            std::string substring = match.str(0);
            instList.push_back(substring);
            std::cout << substring << std::endl;
        }

        // Parse the list of matched instructions
        sum += parseList(instList);

    }
   
    std::cout << "Result is: " << sum << std::endl; 

    return 0;
}