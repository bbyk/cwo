// https://leetcode.com/problems/regular-expression-matching/

#include <fstream>
#include <iostream>

using namespace std;

template<typename T>
class TDArray {
private:
    T *array;
    T **rows;
    size_t height, width;
    size_t size;
public:
    TDArray() = delete;

    inline explicit TDArray(size_t height, size_t width) : height(height), width(width), size(height * width) {
        array = new T[size];
        rows = new T *[height];
        for (size_t i = 0; i < height; ++i) {
            rows[i] = array + (i * width);
        }
    }

    inline T *data() {
        return array;
    }

    inline T *operator[](size_t index) {
        return rows[index];
    }

    inline size_t get_width() {
        return width;
    }

    inline size_t get_height() {
        return height;
    }

    inline size_t get_size() {
        return size;
    }

    ~TDArray() {
        delete[] array;
        delete[] rows;
    }
};

class Solution {
public:
    bool isMatch(string s, string p) {

        // DP algorithm: f(i, j) = true if the p{0 - j} matches s{0 - i}
        // Recurrence:
        // p{j} == s{i} use a[i - 1, j - 1]
        // p{j} == * use (a[i][j - 2] /* zero match */ or a[i - 1][j] && true/false for current match)
        // otherwise false
        TDArray<bool> a{s.size() + 1, p.size() + 1};
        // zero-length pattern matches empty string
        a[0][0] = true;

        // rows - i
        // columns - j
        for (auto j = 1; j <= p.size(); ++j) {
            a[0][j] = (p[j - 1] == '*' ? a[0][j - 2] : false);
        }
        // zero length pattern doesn't match non-zero string
        for (auto i = 1; i <= s.size(); ++i) {
            a[i][0] = false;
        }
        for (auto i = 1; i <= s.size(); ++i) {
            for (auto j = 1; j <= p.size(); ++j) {
                if (s[i - 1] != p[j - 1] && p[j - 1] != '*' && p[j - 1] != '.') {
                    a[i][j] = false;
                } else if (p[j - 1] == '*') {
                    char pc = p[j - 2]; // preceding element of pattern
                    bool f = (pc == s[i - 1] || pc == '.');
                    a[i][j] = (a[i][j - 2] || (a[i - 1][j] && f));
                } else {
                    a[i][j] = a[i - 1][j - 1];
                }
            }
        }
        return a[s.size()][p.size()];
    }
};

int main() {
    Solution solution;
    cout << "Tests:" << endl;

    cout << 0 << solution.isMatch("a", ".*..a*") << endl;
    cout << 0 << solution.isMatch("", "ab*") << endl;
    cout << 0 << solution.isMatch("a", "ab*a") << endl;
    cout << 1 << solution.isMatch("aaa", "a.a") << endl;
    cout << 1 << solution.isMatch("baaabaa", "a*b*.*.*.*a*") << endl;
    cout << 0 << solution.isMatch("baaab", "a*b") << endl;
    cout << 1 << solution.isMatch("aaab", "a*b") << endl;
    cout << 0 << solution.isMatch("aaaabaaab", "a*b") << endl;
    cout << 1 << solution.isMatch("", "b*c*v*") << endl;
    cout << 0 << solution.isMatch("", "b*c*v*d") << endl;
    cout << 1 << solution.isMatch("abc", "abc") << endl;
    cout << 1 << solution.isMatch("bbbba", ".*a*a") << endl;
    cout << 1 << solution.isMatch("a", "a*") << endl;
    cout << 1 << solution.isMatch("a", "ab*") << endl;
    cout << 1 << solution.isMatch("aaa", "ab*a*c*a") << endl;
    cout << 1 << solution.isMatch("aaa", "ab*ac*a") << endl;
    cout << 1 << solution.isMatch("aa", "a*") << endl;
    cout << 1 << solution.isMatch("aaaaa", "a*") << endl;
    cout << 1 << solution.isMatch("aaaaa", ".*") << endl;
    cout << 1 << solution.isMatch("faaaaaaaab", "fa*b") << endl;
    cout << 1 << solution.isMatch("ab", ".*") << endl;
    cout << 0 << solution.isMatch("ab", "a*") << endl;
    cout << 1 << solution.isMatch("aab", "c*a*b") << endl;

    return 0;
}

