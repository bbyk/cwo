//Floyd-Warshall

#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>

using namespace std;
using slong = long long;

struct Vertex {
    double x, y;
};

template<typename T>
class TDArray {
private:
    T *array;
    T **rows;
    size_t height, width;
    size_t size;
public:
    TDArray() = delete;

    inline explicit TDArray(size_t height, size_t width) : height(height), width(width), size(height * width) {
        array = new T[size];
        rows = new T *[height];
        for (size_t i = 0; i < height; ++i) {
            rows[i] = array + (i * width);
        }
    }

    inline T *data() {
        return array;
    }

    inline T *operator[](size_t index) {
        return rows[index];
    }

    inline size_t get_width() {
        return width;
    }

    inline size_t get_height() {
        return height;
    }

    inline size_t get_size() {
        return size;
    }

    ~TDArray() {
        delete[] array;
        delete[] rows;
    }
};

class Solution {
private:
    /**
     * variable-precision SWAR algorithm
     * http://stackoverflow.com/a/109025/1666801
     */
    static int bitCount(unsigned i) {
        // Java: use >>> instead of >>
        // C or C++: use uint32_t
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        return (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    }

public:
    /**
     * Use Held-Karp
     * https://www.youtube.com/watch?v=-JjA4BLQyqE
     */
    double tsp(vector<Vertex> &vertices) {
        size_t num_vertices = vertices.size();

        // as the graph is complete let's precalculate all the distances via an adjacency matrix
        TDArray<double> am{num_vertices, num_vertices};

        // fill up the adjacency matrix with Euclidean distances between vertices.
        for (size_t i = 0; i < num_vertices - 1; ++i) {
            for (size_t j = 1; j < num_vertices; ++j) {
                // calc Euclidean distance between vertices as the length of the edge
                double e_distance = sqrt((vertices[i].x - vertices[j].x) * (vertices[i].x - vertices[j].x) +
                                         (vertices[i].y - vertices[j].y) * (vertices[i].y - vertices[j].y));
                am[i][j] = e_distance;
                am[j][i] = e_distance;
            }
        }

        // generate the powerset of the vertices we should visit
        unsigned num_of_subsets = 1u << num_vertices; // 2 to the cardinality of the set
        vector<vector<unsigned>> subset_size_m;
        subset_size_m.resize(num_vertices + 1);

        for (unsigned i = 0; i < num_of_subsets; ++i) {
            subset_size_m[bitCount(i)].push_back(i);
        }

        // memoization for the TSP as the 2-D array
        // begin base case initialization
        TDArray<double> a{num_of_subsets, num_vertices};
        for (size_t i = 0; i < a.get_size(); ++i) {
            a.data()[i] = numeric_limits<double>::infinity();
        }

        // S = {1} - visited vertices set has the first one in it, 0 - first vertex as destination
        a[1][0] = 0;
        // end base case initialization

        // main loop
        for (unsigned m = 2; m <= num_vertices; ++m) {
            for (unsigned S : subset_size_m[m]) {
                if ((S & 1) == 0) {
                    // skip the sets S that don't have first vertex in it
                    continue;
                }

                unsigned bit = 2;
                unsigned j = 1; // j vertex in S but first vertex (zero-based numeration), 1 - means second vertex

                while (bit <= S) {
                    if (S & bit) {
                        double &v = a[S][j];
                        // S - {j}
                        unsigned Smj = S ^bit;
                        unsigned bit_k = 1;
                        unsigned k = 0;

                        while (bit_k <= Smj) {
                            if (Smj & bit_k) {
                                v = min(v, a[Smj][k] + am[k][j]);
                            }
                            ++k;
                            bit_k <<= 1;
                        }
                    }

                    ++j;
                    bit <<= 1;
                }
            }
        }

        double result = numeric_limits<double>::infinity();

        unsigned S = subset_size_m[num_vertices][0];
        assert(S == ((1 << num_vertices) - 1));

        for (unsigned j = 1; j < num_vertices; ++j) {
            result = min(result, a[S][j] + am[j][0]);
        }

        return result;
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
    Vertex v;
    size_t num_of_vertices;
    *file >> num_of_vertices;
    vector<Vertex> vertices;
    vertices.reserve(num_of_vertices);
    while (num_of_vertices--) {
        *file >> v.x >> v.y;
        vertices.push_back(v);
    }
    Solution solution;

    cout << solution.tsp(vertices) << endl;
    return 0;
}
