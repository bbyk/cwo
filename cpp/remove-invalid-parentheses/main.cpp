// https://leetcode.com/problems/remove-invalid-parentheses/

#include <iostream>
#include <vector>
#include <deque>
#include <unordered_set>

using namespace std;

class Solution {

public:
    vector<string> removeInvalidParentheses(string s) {
        unordered_set<string> res;
        deque<tuple<string, int, size_t, size_t>> queue;
        queue.push_back(make_tuple(move(s), 0, 0ul, 0ul));
        while (res.empty()) {
            for (auto &perm : queue) {
                int cnt = 0;
                auto i = 0ul;
                for (; i < get<0>(perm).size(); ++i) {
                    const char c = get<0>(perm)[i];
                    if (cnt < 0 && c == '(') {
                        break;
                    }
                    if (c == '(') ++cnt; else if (c == ')') --cnt;
                }
                if (cnt == 0) {
                    res.insert(get<0>(perm));
                } else {
                    get<1>(perm) = cnt;
                    get<2>(perm) = i;
                }
            }

            if (!res.empty()) {
                break;
            }

            // prune permutation from the current level
            auto t = queue.size();
            while (t > 0) {
                auto &perm = queue.front();
                for (auto i = get<3>(perm); i < get<2>(perm); ++i) {
                    const char c = get<0>(perm)[i];
                    if ((c == ')' && get<1>(perm) < 0) || (c == '(' && get<1>(perm) > 0)) {
                        auto new_perm = get<0>(perm);
                        new_perm.erase(i, 1);
                        queue.push_back(make_tuple(new_perm, 0, 0ul, i));
                    }
                }

                queue.pop_front();
                --t;
            }
        }

        return vector<string>(res.begin(), res.end());
    }
};

namespace std {
    template<typename T>
    ostream &operator<<(ostream &out, const vector<T> &v) {
        bool first = true;
        out << '[';
        for (const auto &iv : v) {
            if (first) {
                first = false;
            } else {
                out << ", ";
            }
            out << iv;
        }
        out << ']' << endl;

        return out;
    }
}

int main() {
    Solution solution;

    cout << solution.removeInvalidParentheses("((()((s((((()") << endl;
    cout << solution.removeInvalidParentheses(")(((") << endl;
    cout << solution.removeInvalidParentheses("()((((((()l(") << endl;
    cout << solution.removeInvalidParentheses("") << endl;
    cout << solution.removeInvalidParentheses("(a)())()") << endl;
    cout << solution.removeInvalidParentheses("()())()") << endl;
    cout << solution.removeInvalidParentheses("") << endl;
    cout << solution.removeInvalidParentheses("()") << endl;
    return 0;
}
