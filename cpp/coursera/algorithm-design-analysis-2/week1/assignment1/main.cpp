// https://leetcode.com/problems/3sum/

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>

using namespace std;

using wlpair = pair<int, int>;

class Solution {
public:
    unsigned long schedule(vector<wlpair> &jobs) {
/*        auto comp = [](wlpair &a, wlpair &b) {
            double diffA = double(a.first) / a.second;
            double diffB = double(b.first) / b.second;
            return diffA > diffB;
        };*/
        auto comp = [](wlpair &a, wlpair &b) {
                    int diffA = a.first - a.second;
                    int diffB = b.first - b.second;
                    if (diffA == diffB) {
                        return a.first > b.first;
                    } else {
                        return diffA > diffB;
                    }
                };
        sort(jobs.begin(), jobs.end(), comp);
        unsigned long ci = 0;
        unsigned long sum = 0;
        for (auto &wl : jobs) {
            ci += wl.second;
            sum += ci * wl.first;
        }
        return sum;
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
    wlpair p;
    vector<wlpair> jobs;
    unsigned num_of_jobs, w, l;
    *file >> num_of_jobs;
    while (num_of_jobs--) {
        *file >> p.first;
        *file >> p.second;
        jobs.push_back(p);
    }
    Solution solution;

    cout << solution.schedule(jobs) << endl;
    return 0;
}
