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
        std::regex regex("mul\\([0-9]{1,3},[0-9]{1,3}\\)");

        // Iterate over regex matches
        for (std::sregex_iterator it = std::sregex_iterator(subject.begin(), subject.end(), regex); it != std::sregex_iterator(); it++) {
            // Extract the match
            std::smatch match;
            match = *it;
            std::string substring = match.str(0);

            // Parse the found mul instruction            
            long parsedProd = parseSubstring(substring);
            std::cout << substring << " ";
            std::cout << parseSubstring(substring) << std::endl;

            sum += parsedProd;
        }

    }
   
    std::cout << "Result is: " << sum << std::endl; 

    return 0;
}