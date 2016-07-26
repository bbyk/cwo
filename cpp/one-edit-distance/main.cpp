// https://leetcode.com/problems/one-edit-distance/
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.size() > t.size()) {
            swap(s, t);
        }

        auto max_d = t.size() - s.size();
        if (max_d > 1) {
            return false;
        }

        // Recurrence:
        // f(i,j) how many edits apart
        // f(i,j) = /
        //   Si = Ti , f(i - 1, j - 1)
        //   Si != Ti, f(i - 1, j) + 1 or f(i, j - 1) + 1
        // if f(i, j ) == 2 -> terminate the algorithm

        // we don't need a s by t 2d array, instead this is enough
        auto a = new int[s.size() + 1][3];
        a[0][1] = 0;
        a[0][2] = 1;
        if (!s.empty())
            a[1][0] = 1;
        auto end_j = 1 + max_d;


        for (auto i = 1; i <= s.size(); ++i) {
            for (auto j = 0; j < 3; ++j) {
                auto jj = i + (j - 1);
                if (jj < 1) {
                    continue;
                }

                auto v = a[i - 1][j] + (s[i - 1] == t[jj - 1] ? 0 : 1);
                v = min(v, j == 0 ? 2 : a[i][j - 1] + 1);
                v = min(v, j == 2 ? 2 : a[i - 1][j + 1] + 1);

                if (v == 2 && j == end_j) {
                    return false;
                }

                a[i][j] = v;
            }
        }

        bool result = a[s.size()][end_j] == 1;
        delete[] a;
        return result;
    }
};

int main() {
    Solution solution;

    cout << 0 << solution.isOneEditDistance("abcdef", "abc_de_f") << endl;
    cout << 1 << solution.isOneEditDistance("abcdef", "abc_def") << endl;
    cout << 1 << solution.isOneEditDistance("abcdef", "abcdefg") << endl;
    cout << 1 << solution.isOneEditDistance("abcdef", "gabcdef") << endl;
    cout << 1 << solution.isOneEditDistance("ab", "a") << endl;
    cout << 1 << solution.isOneEditDistance("abb", "bbb") << endl;
    cout << 1 << solution.isOneEditDistance("bbb", "bba") << endl;
    cout << 0 << solution.isOneEditDistance("bbb", "aba") << endl;
    cout << 0 << solution.isOneEditDistance("aab", "a") << endl;
    cout << 0 << solution.isOneEditDistance("", "") << endl;
    cout << 0 << solution.isOneEditDistance("a", "a") << endl;
    return 0;
}

