#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

#define PRIME 1000000007L
#define BITS_IN_BYTE 8

int max(int x, int y) {
    return x < y ? x : y;
}

unsigned next_int(string::iterator &it, unsigned w) {
    unsigned v = 0;

    while (w--) {
        char c = *it++;
        v = (v << 1) + (c == '1' ? 1 : 0);
    }

    return v;
}

unsigned long bignum_mod_prime(string line, unsigned prime) {
    unsigned ubits = sizeof(unsigned) * BITS_IN_BYTE;
    unsigned size = (unsigned int) line.size();
    unsigned ub_rem = (unsigned int) ((1L << ubits) % prime);

    string::iterator it = line.begin();

    unsigned remainder = size % ubits;
    unsigned long v = next_int(it, remainder) % prime;

    size -= remainder;
    while (size > 0) {
        v = ((v * ub_rem) + next_int(it, ubits)) % prime;
        size -= ubits;
    }

    return v;
}

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

    string line;

    getline(*file, line);

    unsigned long a = bignum_mod_prime(line, PRIME);

    getline(*file, line);

    unsigned long b = bignum_mod_prime(line, PRIME);

    unsigned long sum = 0L;

    for (int i = 0; i <= 314159; i++) {
        sum = (sum + a + b) % PRIME;
        b = (b << 1L) % PRIME;
    }

    cout << sum << endl;

    return 0;
}
