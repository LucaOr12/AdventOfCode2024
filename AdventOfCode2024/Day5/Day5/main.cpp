//
//  main.cpp
//  Day5
//
//  Created by Luca Orabona on 06/12/24.
//

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

unordered_map<int, unordered_set<int>>(pairs);

bool isLess(int x, int y){
    if(pairs[x].find(y) != pairs[x].end()){
        return true;
    }else return false;
}

int main() {
    pairs.clear();
    ifstream inputFile("Input.txt");
    string line;
    
    while(getline(inputFile,line) && !line.empty()){
        int num1 = stoi(line.substr(0,2));
        int num2 = stoi(line.substr(3,2));
        pairs[num1].insert(num2);
    }
    
    int sum = 0;
    while(inputFile >> line){
        vector<int> updates;
        for(int i = 0; i<line.length();i += 3){
            updates.push_back(stoi(line.substr(i,2)));
        }
        vector<int> SortedUpdates = updates;
        sort(updates.begin(),updates.end(),isLess);
        if(SortedUpdates != updates){//in part 2 i changed this from '==' to '!='
            sum += updates[updates.size()/2];
        }
        
        
    }
    cout<<"The sum is: "<<sum<<endl;
    
    
}
