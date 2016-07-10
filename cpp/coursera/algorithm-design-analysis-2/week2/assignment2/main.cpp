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
#include <deque>

using namespace std;

class Solution {
public:
    unsigned swap_bits(unsigned v, unsigned i, unsigned j) {
        unsigned ibit = unsigned(1) << i;
        unsigned jbit = unsigned(1) << j;
        if (i == j) {
            return v & (~ibit);
        } else if (v & jbit) {
            return (v | ibit) & (~jbit);
        } else {
            return v & (~ibit);
        }
    }

    size_t max_clusters(unsigned min_spacing, unsigned bits, vector<unsigned> &nodes) {
        unordered_map<unsigned*, unordered_set<unsigned*>*> nu;
        for (auto &node : nodes) {
            nu[&node] = nullptr;
        }

        unordered_map<unsigned, unordered_set<unsigned *>*> counter;
        counter.reserve(nodes.size());
        {
            for (unsigned i = 0; i < bits - 1; ++i) {
                for (unsigned j = i + 1; j < bits; ++j) {
                    counter.clear();

                    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
                        unsigned v = *it;
                        unsigned mv = swap_bits(v, i, 0);
                        mv = swap_bits(mv, j, 1);
                        assert((mv & 3) == 0);
                        auto &tset = counter[mv];
                        if (tset == nullptr) {
                            tset = new unordered_set<unsigned*>();
                        }
                        tset->insert(&*it);
                    }

                    for (auto &kv : counter) {
                        unordered_set<unsigned*> tmpUnion (*kv.second);
                        unordered_set<unsigned*>* left = nullptr;

                        for (auto node : tmpUnion) {
                            unordered_set<unsigned*>* right = nu[node];
                            if (right == nullptr) {
                                for (auto n : *kv.second) {
                                    nu[n] = kv.second;
                                }
                                continue;
                            }
                            if (left == nullptr) {
                                left = nu[node];
                            }
                            if (right == left) {
                                continue;
                            }

//                            cout << *node << ',' << left << ',' << left->size() << ',' << right << ',' << right->size() << endl;
                            if (left->size() < right->size()) {
                                swap(left, right);
                            }
//                            cout << *node << ',' << left << ',' << left->size() << ',' << right << ',' << right->size() << endl;

                            for (auto n : *right) {
                                assert(nu[n] == right);
                                left->insert(n);
                                nu[n] = left;
                            }
//                            for (auto n : *left) {
//                                cout << *n << endl;
//                            }

                            delete right;
                        }
//                        cout << endl;
                    }
                }
            }
        }
        size_t cnt = 0;
        unordered_set<unordered_set<unsigned*>*> clusters;
        for (auto &kv : nu) {
            if (kv.second == nullptr) {
                continue;
            }
            if (clusters.insert(kv.second).second) {
                ++cnt;
            }
        }
        return cnt;
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
    vector<unsigned> nodes;
    nodes.push_back(1);
    nodes.push_back(1);
    nodes.push_back(2);
    nodes.push_back(0b110000);
    nodes.push_back(0b11000);
//    nodes.push_back(0b100);
    cout << Solution().max_clusters(3, 6, nodes) << endl;
    nodes.clear();
    nodes.push_back(1);
    nodes.push_back(1);
    nodes.push_back(2);
    nodes.push_back(0b10000);
    nodes.push_back(0b11000);
    nodes.push_back(0b100);

    cout << Solution().max_clusters(3, 5, nodes) << endl;
    nodes.clear();

    nodes.push_back(1);
    nodes.push_back(1);
    nodes.push_back(2);
    nodes.push_back(0b1110000);

    cout << Solution().max_clusters(3, 7, nodes) << endl;
    nodes.clear();

    unsigned num_of_nodes, bits;
    *file >> num_of_nodes;
//    num_of_nodes = 200;
    *file >> bits;
    nodes.resize(num_of_nodes);

    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        unsigned v = 0;
        unsigned bit;
        for (auto i = 0; i < bits; ++i) {
            v <<= 1;
            *file >> bit;
            v |= bit;
        }
        *it = v;
    }
    reverse(nodes.begin(), nodes.end());

    cout << Solution().max_clusters(3, bits, nodes) << endl;
    return 0;
}
