
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>

int main() {
    std::string line;
    long sum = 0;


    while (std::getline(std::cin, line)) {
        int linesum = 0;
        std::vector<int> numberList;

        int i = line.size()-1;

        while(i >= 0) {
            char element = line.at(i);
            if(isdigit(element)) {
                int val = element - '0';
                numberList.push_back(val);
            }
            i--;
        }

        linesum += (numberList.front()) + 10 * (numberList.back());
        sum += linesum;
        std::cout << linesum << std::endl;
    }

    std::cout << "Finalsum: " << sum << std::endl;
    
    return 0;
}