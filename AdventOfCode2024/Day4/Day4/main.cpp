//
//  main.cpp
//  Day4
//
//  Created by Luca Orabona on 06/12/24.
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

bool IsXmax(vector<string> grid, int r, int c){//for part 2
    string diag1 = "";
       diag1 += grid[r][c];
       diag1 += grid[r + 1][c + 1];
       diag1 += grid[r + 2][c + 2];

       string diag2 = "";
       diag2 += grid[r][c + 2];
       diag2 += grid[r + 1][c + 1];
       diag2 += grid[r + 2][c];

       if ((diag1 == "MAS" || diag1 == "SAM") && (diag2 == "MAS" || diag2 == "SAM")) {
           return true;
       }
       return false;
}

int main()
{
    fstream InputFile;
    InputFile.open("input.txt", ios::in);
    if (InputFile.is_open())
    {
        string line;
        string word = "XMAS";
        int sum = 0;
        vector<string> grid;
        vector<pair<int, int>> movements = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
        while (getline(InputFile, line))
        {
            grid.push_back(line);
        }
        int row = static_cast<int>(grid.size());
        int col = static_cast<int>(grid[0].length());
        for (int r = 0; r < row; ++r)
        {
            for (int c = 0; c < col; ++c)
            {

                if (grid[r][c] == 'X')
                {
                    for (auto move : movements)
                    {
                        int x = r;
                        int y = c;
                        for (int i = 1; i <= 3; ++i)
                        {
                            x += move.first;
                            y += move.second;
                            if (x >= 0 && x < row && y >= 0 && y < col && grid[x][y] == word[i])
                            {
                                if (i == 3)
                                {
                                    sum++;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }

        cout <<"The Sum of all XMAS is: "<< sum << endl;
    }
    InputFile.close();
    
    
    cout<<"-----------------PART 2---------------------"<<endl;
    
    fstream newfile;
        newfile.open("input.txt", ios::in);
        if (newfile.is_open())
        {
            string line;
            int sum = 0;
            vector<string> grid;
            while (getline(newfile, line))
            {
                grid.push_back(line);
            }
            int row = static_cast<int>(grid.size());
            int col = static_cast<int>(grid[0].length());
            for (int r = 0; r < row - 2; ++r)
            {
                for (int c = 0; c < col - 2; ++c)
                {
                    if (IsXmax(grid, r, c)) {
                        sum++;
                    }
                }
            }

            cout <<"The Sum of all X-MAS is: "<< sum << endl;
        }
        newfile.close();
}
