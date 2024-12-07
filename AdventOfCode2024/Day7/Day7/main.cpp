//
//  main.cpp
//  Day7
//
//  Created by Luca Orabona on 07/12/24.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>
using namespace std;


long long Evaluate(const string& line) {
    istringstream ss(line);
    long long Result, num;
        char op;

        ss >> Result;
        while (ss >> op) {
            if (op == '|') {
                char after;
                ss >> after;
                if (after == '|') {
                    ss >> num;
                    string concat = to_string(Result) + to_string(num);
                    Result = stoll(concat);
                }
            } else {
                ss >> num;
                if (op == '+') {
                    Result += num;
                } else if (op == '*') {
                    Result *= num;
                }
            }
        }

        return Result;
}

bool checkOp(const vector<long long>& numbers, size_t i, const string& curr, long long expResult) {
    if (i == numbers.size()) {
        long long value = Evaluate(curr);
        if (value == expResult) {
            return true;
        }
        return false;
    }
    bool check = false;
    check |= checkOp(numbers, i + 1, curr + "+" + to_string(numbers[i]), expResult);
    check |= checkOp(numbers, i + 1, curr + "*" + to_string(numbers[i]), expResult);
    check |= checkOp(numbers, i + 1, curr + "||" + to_string(numbers[i]), expResult);
    return check;
}


bool evaluateAll(const vector<long long>& nums, long long target) {
    return checkOp(nums, 1, to_string(nums[0]), target);
}

int main() {
    ifstream inputFile("Input.txt");

        string line;
        long long sumOfValid = 0;

        while (getline(inputFile, line)) {
            size_t pos = line.find(':');

            long long target = stoll(line.substr(0, pos));
            string val = line.substr(pos + 1);

            istringstream iss(val);
            vector<long long> numbers;
            long long num;
            while (iss >> num) {
                numbers.push_back(num);
            }

            if (evaluateAll(numbers, target)) {
                sumOfValid += target;
            }
        }

        cout << sumOfValid << endl;
}
