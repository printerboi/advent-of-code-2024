#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>

/**
 * Check validity of the distances between the numbers. 1 <= distance <= 3
 * 
 * @param list Vector to be checked 
 * @return true if Distance is valid
 * @return false otherwise
 */
bool disancesValid(const std::vector<int> &list) {
  bool isValid = true;
  for (int i = 0; i < list.size()-1; i++) {
    int distance = abs(list.at(i) - list.at(i+1));
    if ( distance > 3 || distance < 1 ) {
      isValid = false;
    }
  }

  return isValid;
}

/**
 * Checks whether the list is sorted ascending or descending.
 * 
 * @param list Vector to be checked
 * @return true If vector is sorted either way
 * @return false otherwise
 */
bool isSorted(const std::vector<int> &list) {
  return std::is_sorted(list.begin(), list.end()) ||
  std::is_sorted(list.rbegin(), list.rend());
}

int main() {
    // Parse the file
    std::vector<std::vector<int>> reportList;
    std::ifstream file("input.txt");
    std::string   line;

    while ( std::getline(file, line) ) {
        std::stringstream linestream(line);
        std::string word;

        std::vector<int> report;
        while (linestream >> word) {
            report.push_back(std::stoi(word));
        }
        reportList.push_back(report);
    }

    // Init our counter
    int safeReports = 0;

    // Iterate over the parsed lines
    for ( std::vector<int> parsedReport : reportList ) {
      // Check if sorted
      if ( isSorted(parsedReport) ) {
        // Check if the distances between the numbers is within range 
        if ( disancesValid(parsedReport) ) {
          safeReports++;
        }
      }
    }

    std::cout << "Safe reports: " << safeReports << std::endl;

    return 0;
}