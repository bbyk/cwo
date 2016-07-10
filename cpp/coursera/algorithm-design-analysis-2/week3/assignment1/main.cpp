// https://leetcode.com/problems/3sum/

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/**
 * An being put into the knapsack.
 */
struct Item {
    unsigned value, weight;
};

class Solution {
public:
    size_t optimal_value(size_t knapsack_size, vector<Item> &items) {
        size_t *buffer = new size_t[(items.size() + 1) * (knapsack_size + 1)];
        size_t **arr = new size_t *[knapsack_size + 1];
        for (unsigned i = 0; i <= knapsack_size; ++i) {
            arr[i] = buffer + i * (items.size() + 1);
        }
        for (unsigned w = 0; w <= knapsack_size; ++w) {
            arr[w][0] = 0;
        }
        for (unsigned w = 0; w <= knapsack_size; ++w) {
            for (unsigned i = 1; i <= items.size(); ++i) {
                size_t solution1 = arr[w][i - 1];
                auto &item = items[i - 1];
                if (w > item.weight) {
                    size_t solution2 = arr[w - item.weight][i - 1] + item.value;
                    arr[w][i] = max(solution1, solution2);
                } else {
                    arr[w][i] = solution1;
                }
            }
        }
        return arr[knapsack_size][items.size()];
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
