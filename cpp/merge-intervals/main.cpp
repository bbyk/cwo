// https://leetcode.com/problems/merge-intervals/

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Interval {
    int start;
    int end;

    Interval() : start(0), end(0) {}

    Interval(int s, int e) : start(s), end(e) {}
};


namespace std {
    ostream &operator<<(ostream &out, const vector<Interval> &v) {
        if (v.empty()) {
            out << "[]";
        } else {
            bool first = true;
            for (auto &i : v) {
                if (first) {
                    first = false;
                } else {
                    out << ',';
                }
                out << '[' << i.start << ',' << i.end << ']';
            }
        }

        out << endl;
        return out;
    }
}

class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {
        vector<Interval> res;
        if (intervals.empty()) {
            return res;
        }
        sort(intervals.begin(), intervals.end(),
             [](const Interval &l, const Interval &r) { return l.start < r.start; });

        res.push_back(intervals[0]);
        for (auto it = intervals.begin() + 1; it < intervals.end(); ++it) {
            auto &last = res.back();
            if (it->start > last.end) {
                res.push_back(*it);
            } else if (last.end < it->end) {
                last.end = it->end;
            }

        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<Interval> v;
    v = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    cout << solution.merge(v) << endl;
    v = {};
    cout << solution.merge(v) << endl;
    v = {{1, 2}, {3, 4}};
    cout << solution.merge(v) << endl;
    v = {{1,4},{2,3}};
    cout << solution.merge(v) << endl;
    return 0;
}

