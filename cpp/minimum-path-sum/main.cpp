// https://leetcode.com/problems/minimum-path-sum/

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    using xrow_type = vector<int>;
public:
    int minPathSum(vector<xrow_type> &grid) {
        // trivial case
        if (grid.empty()) {
            return 0;
        }
        // the grid of the same dimensions as the grid
        // where each cell(x,y) is the min of cell(x - 1, y) and
        // cell(x, y-1)
        vector<xrow_type> min_grid;
        min_grid.reserve(grid.size());

        xrow_type *y_minus_1_row = nullptr;
        for (auto &row : grid) {
            // first line is the same as in the original grid
            xrow_type min_row;
            min_row.reserve(row.size());

            if (min_grid.empty()) {
                // the special case when we don't have previous row
                int x_minus_1 = 0;
                for (auto cost : row) {
                    x_minus_1 += cost;
                    min_row.push_back(x_minus_1);
                }
            } else {
                assert(NULL != y_minus_1_row);

                auto y_minus_1 = y_minus_1_row->begin();
                int x_minus_1 = y_minus_1_row->front();
                for (auto cost : row) {
                    x_minus_1 = min(*y_minus_1, x_minus_1) + cost;
                    min_row.push_back(x_minus_1);
                    ++y_minus_1;
                }
            }
            min_grid.push_back(min_row);
            y_minus_1_row = &min_grid.back();
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