//
//  main.cpp
//  Day3
//
//  Created by Luca Orabona on 05/12/24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
int main() {
   
    std::ifstream InputFile("Input.txt");
    std::string input;
    std::string stream;
    
    while(std::getline(InputFile,stream)){
        input.append(stream);
    }
    const std::regex baseRegex("mul\\((\\d+,\\d+)\\)|(don't\\(\\))|(do\\(\\))");
    
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), baseRegex);
    auto words_end = std::sregex_iterator();
    
    int sum = 0;
    bool check  = true;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i){
        std::smatch match = *i;
        long pos = match[1].str().find(",");
        std::string num1, num2;
        
        if(!match[1].str().empty() && check == true){
            num1 = match[1].str().substr(0, pos);
            num2 = match[1].str().substr(pos + 1,match[1].str().size());
            
                int num1Int = std::stoi(num1);
                int num2Int = std::stoi(num2);
                sum += (num1Int * num2Int);
        }else if(!match[2].str().empty()){
            check = false;
        }else if(!match[3].str().empty()){
            check  = true;
        }
    }
    std::cout<<"The Results are: ";
    std::cout<<sum<<std::endl;
}
