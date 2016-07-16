//Floyd-Warshall

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <climits>
#include <ctime>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;
using slong = long long;

struct Edge {
    unsigned n1, n2;
    slong d;
};

class Solution {
public:
    bool shortest_shortest_path(size_t num_of_vertices, vector<Edge> &edges, slong& result) {
        // run Floyd-Warshall, create a 3-D array
        size_t d2_slice_size = num_of_vertices * num_of_vertices;
        size_t d3_size = d2_slice_size * (num_of_vertices + 1);
        slong *buffer = new slong[d3_size];
        {
            slong *b = buffer;
            slong *e = buffer + d3_size;
            while (b != e) {
                *b++ = LLONG_MAX; // plus infinity
            }
        }

        slong ***d3a = new slong **[num_of_vertices + 1];

        for (auto i = 0; i <= num_of_vertices; ++i) {
            slong **slice = new slong *[num_of_vertices];
            for (auto j = 0; j < num_of_vertices; ++j) {
                slice[j] = buffer + d2_slice_size * i + num_of_vertices * j;
            }
            d3a[i] = slice;
        }

        for (auto &edge : edges) {
            d3a[0][edge.n1][edge.n2] = edge.d;
            d3a[0][edge.n1][edge.n1] = 0LL;
            d3a[0][edge.n2][edge.n2] = 0LL;
        }

        for (auto k = 1; k <= num_of_vertices; ++k) {
            for (auto i = 0; i < num_of_vertices; ++i) {
                for (auto j = 0; j < num_of_vertices; ++j) {
                    d3a[k][i][j] = min(
                            d3a[k - 1][i][j],
                            d3a[k - 1][i][k - 1] == LLONG_MAX || d3a[k - 1][k - 1][j] == LLONG_MAX ? LLONG_MAX : d3a[k - 1][i][k - 1] + d3a[k - 1][k - 1][j]
                    );
                }
            }
        }

        for (auto i = 0; i < num_of_vertices; ++i) {
            slong v = d3a[num_of_vertices][i][i];
            if (v < 0) {
                return false;
            }
        }

        result = d3a[num_of_vertices][0][1];
        for (auto i = 0; i < num_of_vertices - 1; ++i) {
            for (auto j = i + 1; j < num_of_vertices; ++j) {
                result = min(result, d3a[num_of_vertices][i][j]);
            }
        }

        // memory clean up
        for (auto i = 0; i <= num_of_vertices; ++i) {
            delete[] d3a[i];
        }
        delete[] buffer;

        return true;
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
    size_t num_of_vertices, num_of_edges;
    *file >> num_of_vertices;
    *file >> num_of_edges;
    while (num_of_edges--) {
        *file >> e.n1;
        *file >> e.n2;
        *file >> e.d;
        // let's deal with zero based indexing
        --e.n1;
        --e.n2;
        edges.push_back(e);
    }
    Solution solution;

    slong result;
    bool b = solution.shortest_shortest_path(num_of_vertices, edges, result);
    if (b) {
        cout << result << endl;
    } else {
        cout << "negative cycle" << endl;
    }
    return 0;
}
