// https://leetcode.com/problems/combination-sum-ii/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

namespace std {
    template<>
    struct hash<pair<size_t, int>> {
        inline size_t operator()(const pair<size_t, int> p) const {
            return hash<size_t>()(p.first) * 31 + hash<int>()(p.second);
        }
    };
}

class Solution {
private:
    using cell = pair<size_t, int>;
public:
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target) {
        vector<vector<int>> result;
        // trivial case #1
        if (candidates.empty()) {
            // can't ever make target
            return result;
        }
        // trivial case #2
        if (*min_element(candidates.begin(), candidates.end()) > target) {
            // all the values are greater then target -> never be able to make target
            return result;
        }

        vector<int> sorted;
        sorted.resize(candidates.size());
        copy(candidates.begin(), candidates.end(), sorted.begin());
        sort(sorted.rbegin(), sorted.rend());

        // now we should use dynamic programming with some cache
        unordered_map<cell, bool> cache;
        // Define f(i, sum) -> bool where it's true if there is a subset that make the sum in the
        // range from 0,i
        // f(i, sum) = sorted[i] = sum or f(i - 1, sum - sorted[i]) or f(i - 1, sum)
        //
        function<bool(size_t, int)> f = [&](size_t i, int sum) {
            if (sum < 0) {
                return false;
            }
            cell key = {i, sum};
            auto needle = cache.find(key);
            if (needle == cache.end()) {
                bool &v = cache[key];

                int si = sorted[i];
                v = (sum == si);
                if (!v && i > 0) {
                    v = f(i - 1, sum - si);
                    if (!v) {
                        v = f(i - 1, sum);
                    }
                }

                return static_cast<bool>(v);
            }
            return needle->second;
        };

        vector<int> subset;
        function<void(size_t, int)> tr = [&](size_t i, int sum) {
            int si = sorted[i];
            if (f(i, sum)) {
                if (i > 0) {
                    size_t k = i;
                    while (k > 0) {
                        --k;
                        if (sorted[k] != si) {
                            tr(k, sum);
                            break;
                        }
                    }
                }
                subset.push_back(si);
                if (si == sum) {
                    result.push_back(subset);
                }

                if (i > 0) {
                    tr(i - 1, sum - si);
                }
                subset.pop_back();
            }
        };

        tr(sorted.size() - 1, target);

        return result;
    }
};

namespace std {
    template<typename T>
    ostream &operator<<(ostream &out, const vector<vector<T>> &v) {
        for (const auto &iv : v) {
            out << '(';
            bool first = true;
            for (const auto &tv : iv) {
                if (first) {
                    first = false;
                } else {
                    out << ", ";
                }
                out << tv;
            }
            out << ')' << endl;
        }

        return out;
    }
}

int main() {
    Solution solution;
    vector<int> candidates;
    candidates = {1, 2};
    cout << solution.combinationSum2(candidates, 2) << endl;
    candidates = {1, 1};
    cout << solution.combinationSum2(candidates, 1) << endl;
    candidates = {10, 1, 2, 7, 6, 1, 5};
    cout << solution.combinationSum2(candidates, 8) << endl;
    return 0;
}