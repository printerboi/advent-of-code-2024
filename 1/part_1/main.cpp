#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main() {
    std::vector<int> leftList;
    std::vector<int> rightList;

    std::ifstream file("input.txt");
    std::string   line;

    // read in the data and save the numbers to the respective lists
    while(std::getline(file, line)) {
        std::stringstream linestream(line);
        std::string word;        
        int left;
        int right;

        bool isLeft = true;
        while (linestream >> word) {
            if(isLeft) {
                leftList.push_back(std::stoi(word));
                isLeft = false;
            }else{
                rightList.push_back(std::stoi(word));
                isLeft = true;
            }
        }
    }

    int distance = 0;
    while (!leftList.empty()) {
        std::vector<int>::iterator leftMinIterator = std::min_element(leftList.begin(), leftList.end());
        int leftIndex = std::distance(std::begin(leftList), leftMinIterator);


        std::vector<int>::iterator rightMinIterator = std::min_element(rightList.begin(), rightList.end());
        int rightIndex = std::distance(std::begin(rightList), rightMinIterator);

        int difference = abs(leftList.at(leftIndex) - rightList.at(rightIndex));
        distance += difference;

        leftList.erase(leftMinIterator);
        rightList.erase(rightMinIterator);
    }
    
    std::cout << "Distance is: " << distance << std::endl;

    return 0;
}