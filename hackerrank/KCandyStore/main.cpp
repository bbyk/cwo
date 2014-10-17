#include <iostream>
#include <fstream>

const unsigned MOD = 1000000000L;
unsigned cache[1000][1000];

unsigned ncr(unsigned int n, unsigned int k);

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

    unsigned T, N, K;
    *file >> T;

    while (T--) {
        *file >> N >> K;

        // use http://en.wikipedia.org/wiki/Binomial_coefficient#Combinatorics_and_statistics
        cout << ncr(N + K - 1, K) << endl;
    }

    return 0;
}

unsigned ncr(unsigned int n, unsigned int k) {
    if (n == k || k == 0)
        return 1;
    unsigned cached = cache[n][k];
    if (!cached) {
        // symmetry of pascal's triange
        cached = cache[n][n - k];
        if (!cached)
            cached = ((ncr(n - 1, k - 1) + ncr(n - 1, k)) % MOD);
        cache[n][k] = cached;
    }


    return cached;
}