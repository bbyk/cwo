// https://leetcode.com/problems/3sum/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <ctime>

using namespace std;

namespace std {
    template<typename T>
    struct hash<vector<T>> {
        size_t operator()(const vector<T>& v) const {
            hash<T> thash;
            size_t hash_code = v.size();
            for (const auto &i : v) {
                hash_code = (31 * hash_code) + thash(i);
            }
            return hash_code;
        }
    };
}

class Solution {
public:
    vector<vector<int>> threeSum(vector<int> &nums) {
        vector<vector<int>> result;
        if (0 == nums.size()) {
            return result;
        }
        unordered_map<int, int> mapped;
        mapped.reserve(nums.size());
        for (int num : nums) {
            mapped[num]++;
        }
        unordered_set<vector<int>> sresult;
        for (int first : nums) {
            for (auto secondIt = mapped.cbegin(); secondIt != mapped.cend(); ++secondIt) {
                int second = secondIt->first;
                if (first == second && 1 == secondIt->second) {
                    continue;
                }
                int third = -first - second;
                auto thirdIt = mapped.find(third);
                if (thirdIt == mapped.end()
                    || (first == third && 1 == thirdIt->second)
                    || (second == third && 1 == thirdIt->second)) {
                    continue;
                }

                if (first > second) {
                    swap(first, second);
                }
                if (first > third) {
                    swap(first, third);
                }
                if (second > third) {
                    swap(second, third);
                }
                sresult.insert({first, second, third});
            }
        }

        result.resize(sresult.size());
        copy(sresult.begin(), sresult.end(), result.begin());

        return result;
    }
};

namespace std {
    template<typename T>
    ostream &operator<<(ostream &out, const vector<vector<T>> &v) {
        for (const auto &iv : v) {
            cout << '(';
            bool first = true;
            for (const auto &tv : iv) {
                if (first) {
                    first = false;
                } else {
                    cout << ", ";
                }
                cout << tv;
            }
            cout << ')' << endl;
        }

        return out;
    }
}

int main() {
    Solution solution;
    clock_t start = clock();
    vector<int> nums = {7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6};
    clock_t end = clock();

    cout << "took:" << (1000.0 * (end - start) / CLOCKS_PER_SEC) << endl;
    
    cout << solution.threeSum(nums) << endl;
    return 0;
}