#include <iostream>
#include <fstream>
#include <map>
#include <unordered_map>

const unsigned MAX_N = 50000;
const unsigned long PRIME = 1000000007L;
using namespace std;

int main(int argc, const char *argv[]) {
    ifstream st;
    istream *file;
    //Helpers for input and output
    if (argc > 1) {
        st.open(argv[1], ios::in);
        file = &st;
    } else {
        file = &cin;
    }

    unsigned T, N, c;
    *file >> T;

    while (T--) {
        *file >> N;

        unordered_map<unsigned, unsigned> ht;
        for (auto i = 0; i < N; i++) {
            *file >> c;
            auto it = ht.find(c);
            if (it != ht.end()) {
                it->second++;
            } else {
                ht[c] = 1;
            }
        }

        unsigned sum = 0;
        unsigned long comb = 1;

        for (unsigned i = 0; i < MAX_N; i++) {
            auto it = ht.find(i);
            if (it != ht.end()) {
                sum += it->second;
                N -= it->second;
            }

            if (!sum) {
                if (N)
                    cout << 0 << endl;
                else
                    cout << comb << endl;

                break;
            }

            comb = (comb * sum) % PRIME;

            sum--;
        }
    }
}