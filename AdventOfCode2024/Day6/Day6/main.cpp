//
//  main.cpp
//  Day6
//
//  Created by Luca Orabona on 07/12/24.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
using namespace std;

struct Position
{
    int x;
    int y;
};

bool operator<(const Position& left, const Position& right) {
     return (left.x <right.x || (left.x==right.x && left.y<right.y));
}

enum Directions {up,right,down,left};

void guardMove(long long &answer, const vector<string>& map, vector<vector<bool>>& isVisited, Position pos, Directions dir, vector<Position>& posPassed){
    
    if(!isVisited[pos.x][pos.y]){
        if(map[pos.x][pos.y]!= '^'){
            posPassed.push_back({pos.x,pos.y});
        }
        answer++;
        isVisited[pos.x][pos.y] = true;
    }
    
    Position newPos;
    Directions newDir;
    
    switch (dir) {
        case Directions::up:
            newDir = Directions::right;
            newPos = {pos.x - 1, pos.y};
            break;
        case Directions::right:
            newDir = Directions::down;
            newPos = {pos.x, pos.y + 1};
            break;
        case Directions::down:
            newDir = Directions::left;
            newPos = {pos.x + 1, pos.y};
            break;
        case Directions::left:
            newDir = Directions::up;
            newPos = {pos.x, pos.y - 1};
            break;
    }
    if(newPos.x < 0 || newPos.x >= map.size())return;
    if(newPos.y < 0 || newPos.y >= map[0].size())return;
    
    if(map[newPos.x][newPos.y] == '.' || map[newPos.x][newPos.y] == '^'){
        guardMove(answer,map,isVisited,newPos,dir,posPassed);
    }else if(map[newPos.x][newPos.y] == '#'){
        guardMove(answer, map, isVisited, pos, newDir, posPassed);
    }
    return;
}

bool isLooping(const vector<string>map, std::map<Position, set<Directions>>& all, Position pos, Directions dir){
    Position newPos;
    Directions newDir;
    
    switch (dir) {
        case Directions::up:
            newDir = Directions::right;
            newPos = {pos.x - 1, pos.y};
            break;
        case Directions::right:
            newDir = Directions::down;
            newPos = {pos.x, pos.y + 1};
            break;
        case Directions::down:
            newDir = Directions::left;
            newPos = {pos.x + 1, pos.y};
            break;
        case Directions::left:
            newDir = Directions::up;
            newPos = {pos.x, pos.y - 1};
            break;
    }
    if(newPos.x < 0 || newPos.x >= map.size())return false;
    if(newPos.y < 0 || newPos.y >= map[0].size())return false;
    
    if(map[newPos.x][newPos.y] == '.' || map[newPos.x][newPos.y] == '^'){
        return isLooping(map,all,newPos,dir);
    }else if(map[newPos.x][newPos.y] == '#'){
        if(all[pos].contains(dir)){
            return true;
        }
        else{
            all[pos].insert(dir);
        }
        return isLooping(map, all, pos, newDir);
    }
    return false;
}

Position StartingPos(const vector<string>& map){
    for(int i = 0 ; i< map.size();i++){
        for(int j = 0; j<map[0].size(); j++){
            if(map[i][j] == '^'){
                return{i, j};
            }
        }
    }
    return {-1,-1};//if '^' not found
}


long long posToStuck(vector<string>& map){//for part 2
    long long stuckAns = 0;
    long long alias = 0;
    
    Position start_pos = StartingPos(map);
    std::vector<std::vector<bool>> isVisited (map.size(), std::vector<bool>(map[0].size()));
    std::vector<Position> point_passed;
    
    guardMove(alias, map, isVisited, start_pos, Directions::up, point_passed);
    
    for(auto position : point_passed){
        map[position.x][position.y] = '#';
        
        std::map<Position, std::set<Directions>> all_state;
        if(isLooping(map, all_state, start_pos, Directions::up)){
            ++stuckAns;
        }
        map[position.x][position.y] = '.';
    }
    return stuckAns;
}



int main(){
    ifstream inputFile("Input.txt");
    string line;
    vector<string> map;
    while(getline(inputFile, line)){
        map.push_back(line);
    }
    
    //part 1
    vector<vector<bool>> isVisited(map.size(), vector<bool>(map[0].size()));
    Position startingPos = StartingPos(map);
    vector<Position> posPassed;
    
    long long answer = 0;
    guardMove(answer, map, isVisited, startingPos, Directions::up, posPassed);
    cout<<"the guard moves "<<answer<<" times before leaving the map"<<endl;
    
    //part 2
    long long answer2 = posToStuck(map);
    cout<<answer2<<endl;
}

