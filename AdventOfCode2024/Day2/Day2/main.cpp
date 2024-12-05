//
//  main.cpp
//  Day2
//
//  Created by Luca Orabona on 05/12/24.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>


bool isSafe(std::vector<int> reports)
{
    bool isDecreasing = true;
    bool isIncreasing = true;
    for (int i = 0; i < reports.size() - 1; i++) {
        if (reports[i] == reports[i + 1]) {
            return false;
        }
        if (abs(reports[i] - reports[i + 1]) > 3) {
            return false;
        }
        if (reports[i + 1] > reports[i]) {
            isDecreasing = false;
        }
        if (reports[i + 1] < reports[i]) {
            isIncreasing = false;
        }
    }

    return isDecreasing || isIncreasing;
}

bool isSafeAll(std::vector<int> reports)
{
    if (isSafe(reports))
        return true;
    for (int i = 0; i < reports.size(); i++) {
        std::vector<int> other = reports;
        other.erase(other.begin() + i);

        if (isSafe(other))
            return true;
    }

    return false;
}
int main() {
    
    int sumOfSafe = 0;
    
    std::ifstream inputFile("Input.txt");

        std::string line;
    while (std::getline(inputFile, line)) {
            std::stringstream stream(line);
            std::vector<int> levels;
            
            int level;
            while (stream >> level)
                levels.push_back(level);

            sumOfSafe += isSafeAll(levels);
        }

        std::cout << sumOfSafe << std::endl;
}
