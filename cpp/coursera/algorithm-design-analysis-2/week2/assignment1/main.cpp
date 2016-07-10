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

struct Edge {
    int n1, n2;
    unsigned d;
};

class Solution {
public:
    unsigned max_spacing(size_t k /* num of clusters */, vector<Edge> &edges) {
        unordered_map<int, unordered_set<int> *> nu;

        sort(edges.begin(), edges.end(), [](Edge &e1, Edge &e2) {
            return e1.d < e2.d;
        });
        size_t numk = 0;
        for (Edge &e : edges) {
            auto &pset1 = nu[e.n1];
            if (pset1 == nullptr) {
                pset1 = new unordered_set<int>{e.n1};
                ++numk;
            }
            auto &pset2 = nu[e.n2];
            if (pset2 == nullptr) {
                pset2 = new unordered_set<int>{e.n2};
                ++numk;
            }
        }
        assert(numk >= k);
        auto e_it = edges.begin();
        while (e_it != edges.end()) {
            Edge &e = *e_it;
            // the nodes are in the same cluster, skip
            auto cluster1 = nu[e.n1];
            auto cluster2 = nu[e.n2];
            // we're in the same cluster, skip
            if (cluster1 != cluster2) {
                if (numk == k) {
                    break;
                }
                // merge to the set with the greater cardinality: cluster1 is greater set
                if (cluster1->size() < cluster2->size()) {
                    swap(cluster1, cluster2);
                }

                for (int node : *cluster2) {
                    cluster1->insert(node);
                    nu[node] = cluster1;
                }

                delete cluster2;
                --numk;
            }
            ++e_it;
        }
        return e_it->d;
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
    Edge e;
    vector<Edge> edges;
    unsigned num_of_edges;
    *file >> num_of_edges;
    while (num_of_edges--) {
        *file >> e.n1;
        *file >> e.n2;
        *file >> e.d;
        edges.push_back(e);
    }
    Solution solution;

    cout << solution.max_spacing(4, edges) << endl;
    return 0;
}
