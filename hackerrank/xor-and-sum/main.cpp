// https://www.hackerrank.com/challenges/xor-and-sum/submissions/code/2209370

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
#define MAX_ITER 314159

void bignum_mod_prime(string line, unsigned long *a1pr, unsigned long *a0pr, unsigned max_bits, unsigned prime) {
    unsigned long v1 = 0;
    unsigned long v0 = 0;
    unsigned long w = line.size();

    for (int i = max_bits - 1; i >= 0; i--) {
        char c = i >= w ? '0' : line[w - i - 1];
        v1 = ((v1 << 1) + (c == '1' ? 1 : 0)) % prime;
        v0 = ((v0 << 1) + (c == '1' ? 0 : 1)) % prime;

        a1pr[i] = v1;
        a0pr[i] = v0;
    }
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

    string a, b;

    getline(*file, a);
    getline(*file, b);

    unsigned max_bits = MAX_ITER;

    // partial a or b % PRIME. e.g. a = 11011,
    // 1 % PRIME, 11 % PRIME, 110 % PRIME, 1101 % PRIME, 11011 % PRIME
    unsigned long *a1pr = new unsigned long[max_bits];
    unsigned long *a0pr = new unsigned long[max_bits];

    bignum_mod_prime(a, a1pr, a0pr, max_bits, PRIME);

    unsigned long sum0 = 0L;
    unsigned long sum1 = 0L;

    unsigned long aw = a.size();
    unsigned long bw = b.size();

    unsigned long av = 1L;
    unsigned long bv = 1L;

    for (long i = 0; i < MAX_ITER; i++) {
        bv = (bv << 1) % PRIME;
    }

    unsigned long suma = 0L;

    for (long i = 0; i < MAX_ITER; i++) {
        char c = i >= aw ? '0' : a[aw - i - 1];
        if ('1' == c) {
            suma = (suma + av) % PRIME;
        }
        av = (av << 1) % PRIME;
        sum0 = (sum0 + suma) % PRIME;
    }

    av = 1L;
    unsigned long sumb = bv;

    for (long i = 0; i < max(bw, aw); i++) {
        char c = i >= bw ? '0' : b[bw - i - 1];
        if ('0' == c) {
            sum0 = (sum0 + (a1pr[i] * av)) % PRIME;
        } else {
            sum1 = (sum1 + (a0pr[i] * av) + sumb) % PRIME;
        }

        av = (av << 1) % PRIME;
        bv = (bv << 1) % PRIME;
        sumb = (sumb + bv) % PRIME;
    }

    unsigned long sum = (sum0 + sum1) % PRIME;
    cout << sum << endl;

    delete[] a1pr;
    delete[] a0pr;

    return 0;
}
