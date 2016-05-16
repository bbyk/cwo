#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        if (b.size() > a.size()) {
            swap(a, b);
        }

        auto ait = a.rbegin();
        auto bit = b.rbegin();
        string result;
        result.reserve(a.size() + 1);
        char carry = 0;

        while (ait != a.rend()) {
            const char ac = (const char) (('0' == *ait) ? 0 : 1);
            const char bc = (const char) (('0' == *bit || bit == b.rend()) ? 0 : 1);
            const char opres = ac + bc + carry;
            const char digit = (const char) (opres & 1);
            carry = (char) ((opres & 2) >> 1);

            result.insert(result.begin(), digit == 1 ? '1' : '0');

            ++ait;
            if (bit != b.rend())
                ++bit;
        }

        if (carry)
            result.insert(result.begin(), '1');

        return result;
    }
};

int main() {
    Solution solution;
    cout << "Expected sum 100: " << solution.addBinary("11", "1") << endl;
    cout << "Expected sum 1010: " << solution.addBinary("101", "101") << endl;
    cout << "Expected sum 101: " << solution.addBinary("", "101") << endl;
    return 0;
}