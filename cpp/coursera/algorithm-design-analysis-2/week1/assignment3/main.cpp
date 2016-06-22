// https://leetcode.com/problems/3sum/

#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
#include <ctime>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Edge {
    int node1;
    int node2;
    int cost;
};

using AdjList = unordered_map<int, vector<Edge *>>;

struct Graph {
    AdjList adjList;
    vector<Edge> edges;
};

class Solution {
public:
    int minSpanningTree(const Graph &graph) {
        if (graph.edges.empty()) {
            return 0;
        }
        unordered_set<int> tree;
        tree.reserve(graph.adjList.size());
        // the spanning tree will contain all the nodes, let's
        // add an arbitrary first one
        tree.insert(graph.edges.begin()->node1);
        int tree_cost = 0;
        while (true) {
            const Edge* min_edge = nullptr;
            for (auto &edge : graph.edges) {
                // the edge does not cross the divide
                if (tree.find(edge.node1) == tree.end() && tree.find(edge.node2) == tree.end()) {
                    continue;
                }

                // the edge is in the spanning tree
                if (tree.find(edge.node1) != tree.end() && tree.find(edge.node2) != tree.end()) {
                    continue;
                }

                if (min_edge == nullptr || min_edge->cost > edge.cost) {
                    min_edge = &edge;
                }
            }

            if (min_edge == nullptr) {
                break;
            }

            if (tree.find(min_edge->node1) != tree.end()) {
                tree.insert(min_edge->node2);
            } else {
                tree.insert(min_edge->node1);
            }
            tree_cost += min_edge->cost;
        }
        assert(tree.size() == graph.adjList.size());

        return tree_cost;
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
    unsigned num_of_nodes, num_of_edges;
    *file >> num_of_nodes;
    *file >> num_of_edges;
    Graph graph;
    graph.edges.resize(num_of_edges);

    auto it = graph.edges.begin();
    while (num_of_edges--) {
        *file >> it->node1;
        *file >> it->node2;
        *file >> it->cost;
        graph.adjList[it->node1].push_back(&(*it));
        graph.adjList[it->node2].push_back(&(*it));
        ++it;
    }
    assert(graph.adjList.size() == num_of_nodes);

    Solution solution;
    cout << solution.minSpanningTree(graph) << endl;
    return 0;
}
