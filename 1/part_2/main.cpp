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

    int simscore = 0;
    for(int num : leftList) {
        int occurences = std::count(rightList.begin(), rightList.end(), num);
        int sim = num * occurences;
        simscore += sim;
    }
    
    std::cout << "Simscore is: " << simscore << std::endl;

    return 0;
}