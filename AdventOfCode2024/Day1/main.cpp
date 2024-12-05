//
//  main.cpp
//  AdventOfCode2024
//
//  Created by Luca Orabona on 05/12/24.
//

#include <iostream>
#include <sstream>
#include <fstream>

int main() {
    std::vector<std::string>(list1);
    std::vector<std::string>(list2);
    
    //separate the rows in two files
    std::ifstream inputFile("Input.txt");
    std::ofstream col1File("col1.txt");
    std::ofstream col2File("col2.txt");
    
    std::string  line;
    while (std::getline(inputFile, line)) {
        std::istringstream lineStream(line); // Stream to parse the line
        std::string col1, col2;
        
        // Extract two columns (assuming space or tab-separated values)
        if (lineStream >> col1 >> col2) {
            col1File << col1 << '\n'; // Write the first column to col1.txt
            list1.push_back(col1);
            col2File << col2 << '\n'; // Write the second column to col2.txt
            list2.push_back(col2);
        }
    }
    inputFile.close();
    col1File.close();
    col2File.close();
    
    sort(list1.begin(),list1.end());
    sort(list2.begin(),list2.end());
    
    for(auto & i: list1){
        std::cout<< i<<std::endl;
    }
    std::cout<<"-------------------"<<std::endl;

    for(auto & i: list2){
        std::cout<< i<<std::endl;
    }
    std::cout<<"-------------------"<<std::endl;

    std::vector<int>(distanceList);
    
    int distance = 0;
    int sum = 0;
    
    for(auto it1 = list1.begin(), it2 = list2.begin();
        it1 != list1.end() && it2 != list2.end();
        ++it1, ++it2){
        int value1 = std::stoi(*it1);
        int value2 = std::stoi(*it2);
        distance = value1 - value2;
        distance = abs(distance);
        sum += distance;
        distanceList.push_back(distance);
    }
    
    
    for(auto & i: distanceList){
        std::cout<< i<<std::endl;
    }
    std::cout<<"-------------------"<<std::endl;
    std::cout<<"the sum is "<<sum<<std::endl;
}

