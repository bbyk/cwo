// https://leetcode.com/problems/minimum-path-sum/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    using xrow = vector<int>;
public:
    int minPathSum(vector<xrow> &grid) {
        // trivial case
        if (grid.empty()) {
            return 0;
        }
        vector<xrow> min_grid;
        min_grid.reserve(grid.size());

        xrow *prev_row = nullptr;
        for (auto &row : grid) {
            // first line is the same as in the original grid
            xrow min_row;
            min_row.reserve(row.size());

            if (min_grid.empty()) {
                // the special case when we don't have previous row
                int prev = 0;
                for (auto cost : row) {
                    prev += cost;
                    min_row.push_back(prev);
                }
            } else {
                assert(NULL != prev_row);

                auto prevIt = prev_row->begin();
                int prev = prev_row->front();
                for (auto cost : row) {
                    prev = min(*prevIt, prev) + cost;
                    min_row.push_back(prev);
                    ++prevIt;
                }
            }
            min_grid.push_back(min_row);
            prev_row = &min_grid.back();
        }
        return *min_grid.rbegin()->rbegin();
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid{};
    cout << "expected 0, was " << solution.minPathSum(grid) << endl;
    grid = {{1, 2, 3},
            {1, 2, 3}};
    cout << "expected 7, was " << solution.minPathSum(grid) << endl;
    grid = {{1,3,1}, {1,5,1}, {4,2,1}};
    cout << "expected 7, was " << solution.minPathSum(grid) << endl;
    return 0;
}