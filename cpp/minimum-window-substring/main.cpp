// https://leetcode.com/problems/minimum-window-substring/

#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> tc;
        for_each(t.begin(), t.end(), [&](char c) { tc[c]++; });

        unordered_map<char, int> wc; // window counters

        // initial fill in loop -> we should encounter the chars from t
        // at least the same number of times they are in t
        auto tsize = tc.size();

        auto it = s.begin();
        decltype(it) from, to;
        decltype(it) min_from, min_to;

        for(; it < s.end(); ++it) {
            char c = *it;
            if (tc.find(c) == tc.end()) {
                continue;
            }

            // we encountered the first char from t
            if (wc.empty()) {
                from = it;
            }

            auto& cnt = wc[c];
            if (++cnt == tc[c]) {
                --tsize;
            }

            if (tsize == 0) {
                // char after the last char from t that makes full window
                to = it + 1;
                break;
            }
        }

        if (tsize > 0) {
            return "";
        }

        min_from = from;
        min_to = to;

        // move the window ahead and if it shrinks
        while(true) {
            auto from_c = *from;
            if (tc.find(from_c) == tc.end()) {
                ++from;
                continue;
            }

            if (distance(from, to) < distance(min_from, min_to)) {
                min_from = from; min_to = to;
            }

            auto& wc_from_c = wc[from_c];
            auto& tc_from_c = tc[from_c];
            wc_from_c--;
            if (wc_from_c < tc_from_c) {
                // catch up loop
                while (to != s.end()) {
                    auto to_c = *to;
                    ++to;
                    if (tc.find(to_c) != tc.end()) {
                        wc[to_c]++;

                        if (to_c == from_c) {
                            break;
                        }
                    }
                }

                // couldn't find subst from the char being popped, the end.
                if (wc_from_c < tc_from_c) {
                    break;
                }
            }

            ++from;
        }

        return string(min_from, min_to);
    }
};

int main() {
    Solution solution;

    cout << solution.minWindow("ADOBECODEBANC", "ABC") << endl;
    cout << solution.minWindow("ADOBECODEBANC", "ABCF") << endl;
    cout << solution.minWindow("a", "a") << endl;

    return 0;
}

