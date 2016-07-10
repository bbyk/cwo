// https://leetcode.com/problems/3sum/

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <stack>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/**
 * An item being put into the knapsack.
 */
struct Item {
    unsigned value, weight;
};

struct SolutionKey {
    size_t i;
    size_t w;

    inline friend bool operator==(const SolutionKey& left, const SolutionKey& right) {
        return left.i == right.i && left.w == right.w;
    }
};

template<>
struct hash<SolutionKey> {
    inline size_t operator()(SolutionKey v) const {
        return hash<size_t>()(v.i) * 31 + hash<size_t>()(v.w);
    }
};

class Solution {
public:
    size_t optimal_value(size_t knapsack_size, vector<Item> &items) {
        if (knapsack_size == 0 || items.empty()) {
            return 0;
        }
        unordered_map<SolutionKey, size_t> visited_solution;
        vector<SolutionKey> stack;
        stack.reserve(max(knapsack_size, items.size()));

        SolutionKey targetSolution{items.size(), knapsack_size};
        stack.push_back(targetSolution);
        while (!stack.empty()) {
            auto &key = stack.back();
            if (0 == key.i || 0 == key.w) {
                visited_solution[key] = 0;
                stack.pop_back();
                continue;
            }

            auto pkey = key;
            --pkey.i;
            auto solution1 = visited_solution.find(pkey);
            if (solution1 == visited_solution.end()) {
                stack.push_back(pkey);
                continue;
            }

            auto &item = items[key.i - 1];
            pkey = key;
            if (pkey.w > item.weight) {
                --pkey.i;
                pkey.w -= item.weight;

                auto solution2 = visited_solution.find(pkey);
                if (solution2 == visited_solution.end()) {
                    stack.push_back(pkey);
                    continue;
                }

                visited_solution[key] = max(solution1->second, solution2->second + item.value);
            } else{
                visited_solution[key] = solution1->second;
            }

            stack.pop_back();
        }

        return visited_solution[targetSolution];
    }
};

int main(int argc, char *argv[]) {
    ifstream st;
    istream *file;

    if (argc > 1) {
        st.open(argv[1], ios::in);
        assert(!st.fail());
        file = &st;
    } else {
        file = &cin;
    }
    size_t knapsack_size, num_of_items;
    *file >> knapsack_size >> num_of_items;

    vector<Item> items;
    items.resize(num_of_items);

    auto it = items.begin();
    while (num_of_items--) {
        *file >> it->value >> it->weight;
        ++it;
    }

    Solution solution;
    cout << solution.optimal_value(knapsack_size, items) << endl;
    return 0;
}
