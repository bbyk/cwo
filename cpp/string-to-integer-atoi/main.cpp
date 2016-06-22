// https://leetcode.com/problems/3sum/

#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        if (str.empty()) {
            return 0;
        }
        long acc = 0;
        long sign = 1;
        auto it = str.cbegin();
        for (; it != str.cend(); ++it) {
            char c = *it;
            if (('0' <= c) && (c <= '9')) {
                break;
            } else if (c == '-') {
                ++it;
                sign = -sign;
                break;
            } else if (c == '+') {
                ++it;
                break;
            } else if (c != ' ') {
                return 0;
            }
        }
        for (; it != str.cend(); ++it) {
            char c = *it;
            if (('0' <= c) && (c <= '9')) {
                auto digit = c - '0';
                acc *= 10;
                acc += digit;
            } else {
                break;
            }

            if (acc > INT_MAX + 1L) {
                break;
            }
        }
        return (int)max(min(sign * acc, (long)INT_MAX), (long)INT_MIN);
    }
};

int main() {
    Solution solution;

    cout << solution.myAtoi("9223372036854775809") << endl;
    cout << solution.myAtoi("2147483648") << endl;
    cout << solution.myAtoi("+") << endl;
    cout << solution.myAtoi("") << endl;
    cout << solution.myAtoi("5") << endl;
    cout << solution.myAtoi("-50") << endl;
    return 0;
}
