#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int N, M;

bool isValid(int x, int y) { return x >= 0 && x < N && y >= 0 && y < M; }

int findAntinodes(vector<string> line,const unordered_map<char, vector<vector<int>>> &mp) {

    int antinodes = 0;

    for (const auto &[_, pos] : mp) {
        for (int i = 0; i < pos.size(); i++) {
            for (int j = i + 1; j < pos.size(); j++) {
                int dx = pos[i][0] - pos[j][0], dy = pos[i][1] - pos[j][1];
                int nx = pos[i][0] + dx, ny = pos[i][1] + dy;
                if (isValid(nx, ny) && line[nx][ny] != '#') {
                    antinodes++;
                    line[nx][ny] = '#';
                }
                nx = pos[j][0] - dx;
                ny = pos[j][1] - dy;
                if (isValid(nx, ny) && line[nx][ny] != '#') {
                    antinodes++;
                    line[nx][ny] = '#';
                }
            }
        }
    }

    return antinodes;
}
//part 2
int findExtendedAntinodes(vector<string> line,const unordered_map<char, vector<vector<int>>> &mp) {
    int antinodes = 0;

    for (const auto &[_, pos] : mp) {
        antinodes += pos.size();
        for (int i = 0; i < pos.size(); i++) {
            for (int j = i + 1; j < pos.size(); j++) {
                int dx = pos[i][0] - pos[j][0], dy = pos[i][1] - pos[j][1];
                int nx = pos[i][0] + dx, ny = pos[i][1] + dy;
                while (isValid(nx, ny)) {
                    if (line[nx][ny] == '.') {
                        antinodes++;
                        line[nx][ny] = '#';
                    }
                    nx += dx;
                    ny += dy;
                }
                nx = pos[j][0] - dx;
                ny = pos[j][1] - dy;
                while (isValid(nx, ny)) {
                    if (line[nx][ny] == '.') {
                        antinodes++;
                        line[nx][ny] = '#';
                    }
                    nx -= dx;
                    ny -= dy;
                }
            }
        }
    }
    return antinodes;
}

int main() {
    fstream f("input.txt");
    string ln;

    vector<string> grid;
    while (getline(f, ln)) {
        grid.push_back(ln);
    }
    f.close();

    N = static_cast<int>(grid.size());
    M = static_cast<int>(grid[0].length());

    int sumOfantinodes = 0;
    int ExtSumOfAntinodes = 0;
    unordered_map<char, vector<vector<int>>> mp;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (grid[i][j] != '.') {
                mp[grid[i][j]].push_back({i, j});
            }
        }
    }

    sumOfantinodes = findAntinodes(grid, mp);
    ExtSumOfAntinodes = findExtendedAntinodes(grid, mp);

    cout <<"the sum of antinodes is: "<<sumOfantinodes << endl;
    cout <<"the sum of extended antinodes is: "<<ExtSumOfAntinodes << endl;//part 2

}
