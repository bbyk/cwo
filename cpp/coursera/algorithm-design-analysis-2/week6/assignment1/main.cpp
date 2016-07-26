// 2SAT
#include <fstream>
#include <iostream>
#include <cassert>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>

using namespace std;

/**
 * describes the a clause in the 2SAT problem in a form of Vars[var1Ord] || Vars[var2ord]. Negative values mean !.
 */
struct Clause {
    int var1ord;
    int var2ord;
};

class Solution {

public:
    bool is_SATisfiable(vector<Clause> &clauses) {
        // build https://en.wikipedia.org/wiki/Implication_graph
        unordered_map<int, vector<int>> graph;
        for (auto &clause : clauses) {
            graph[-clause.var1ord].push_back(clause.var2ord);
            graph[-clause.var2ord].push_back(clause.var1ord);
        }

        unordered_map<int, vector<int>> tr_graph;
        for (auto &kv : graph) {
            for (auto v : kv.second) {
                tr_graph[v].push_back(kv.first);
            }
        }

        // now we should use either of SCC algorithms: Kasaraju
        // first time - regular DFS with post-order traversal
        vector<int> order;
        order.reserve(clauses.size());

        unordered_set<int> visited;
        for (auto &kv : graph) {
            if (visited.find(kv.first) != visited.end()) {
                continue;
            }

            stack<int> stack;
            stack.push(kv.first);
            visited.insert(kv.first);

            while (!stack.empty()) {
                auto vertex = stack.top();
                bool has_unvisited_childeren = false;

                for (auto nbor : graph[vertex]) {
                    if (visited.find(nbor) != visited.end()) {
                        continue;
                    }

                    visited.insert(nbor);
                    stack.push(nbor);

                    has_unvisited_childeren = true;
                }

                if (!has_unvisited_childeren) {
                    stack.pop();
                    order.push_back(vertex);
                }
            }
        }

        unordered_map<int, unordered_set<int>> scc;
        visited.clear();
        // now we need to follow the order in the order
        // iterate the transpose graph
        // in the order reverse
        for (auto it = order.rbegin(); it != order.rend(); ++it) {
            int vertex = *it;
            if (visited.find(vertex) != visited.end()) {
                continue;
            }

            // vertex, root
            stack<pair<int, int>> stack;
            stack.push({vertex, vertex});
            visited.insert(vertex);

            while (!stack.empty()) {
                auto pair = stack.top();
                stack.pop();
                bool has_unvisited_childeren = false;

                for (auto &nbor : tr_graph[pair.first]) {
                    if (visited.find(nbor) != visited.end()) {
                        continue;
                    }

                    visited.insert(nbor);
                    stack.push({nbor, pair.second});
                    has_unvisited_childeren = true;
                }

                if (pair.first != pair.second || has_unvisited_childeren) {
                    scc[pair.second].insert(pair.first);
                }
            }
        }

        for (auto &kv : scc) {
            unordered_set<int> tset;
            for (auto v : kv.second) {
                if (tset.find(-v) == tset.end()) {
                    tset.insert(v);
                } else {
                    return false;
                }
            }
        }

        return true;
    }
};


int main(int argc, char *argv[]) {

    for (int i = 1; i < argc; ++i) {
        ifstream st;
        istream *file;

        st.open(argv[i], ios::in);
        assert(!st.fail());
        file = &st;

        size_t num_of_vertices;
        *file >> num_of_vertices;
        Clause clause;
        vector<Clause> clauses;
        clauses.reserve(num_of_vertices);

        while (num_of_vertices--) {
            *file >> clause.var1ord >> clause.var2ord;
            clauses.push_back(clause);
        }
        Solution solution;

        cout << solution.is_SATisfiable(clauses) << endl;
    }
    return 0;
}
