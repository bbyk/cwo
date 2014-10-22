#include <iostream>
#include <fstream>
#include <assert.h>

// https://www.hackerrank.com/challenges/manasa-and-combinatorics
// influenced by this explanation: http://codeforces.com/blog/entry/12071

const unsigned PRIME = 99991;

using namespace std;

unsigned nCr_luke_mod_prime(unsigned long n, unsigned long k);

unsigned nCr_mod_prime(unsigned, unsigned);

unsigned mod_mult_inverse(unsigned long);

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

    unsigned T;
    unsigned long N;
    *file >> T;

    while (T--) {
        *file >> N;
        unsigned long As = N;
        unsigned long Bs = As << 1;
        unsigned long AsPlusBs = Bs + As;

        // all ways to allocate As
        long res = nCr_luke_mod_prime(AsPlusBs, As);

        // minus those wrongly allocated
        res -= (nCr_luke_mod_prime(AsPlusBs, As - 1) << 1) % PRIME;
        if (res < 0)
            res = PRIME + res;

        if (As > 1) {
            // plus those we accidentally took away: http://en.wikipedia.org/wiki/Inclusion%E2%80%93exclusion_principle#Counting_integers
            res += nCr_luke_mod_prime(AsPlusBs, As - 2);
        }

        res %= PRIME;

        cout << res << endl;
    }

    return 0;
}

/**
 * http://en.wikipedia.org/wiki/Lucas%27_theorem : make n and k baseP numbers and call nCr_mod_prime for them.
 */
unsigned nCr_luke_mod_prime(unsigned long n, unsigned long k) {
    assert (n >= k);

    if (0 == k)
        return 1;
    if (n == k)
        return 1;

    unsigned long res = 1;

    while (n > 0) {
        unsigned nBaseP = (unsigned int) (n % PRIME);
        unsigned kBaseP = (unsigned int) (k % PRIME);

        res = (res * nCr_mod_prime(nBaseP, kBaseP)) % PRIME;

        if (!res)
            break;

        n /= PRIME;
        k /= PRIME;
    }

    return (unsigned int) res;
}

/**
* http://en.wikipedia.org/wiki/Binomial_coefficient#Multiplicative_formula, nominator and denominator calculated separately
* because we want to take modulo of them.
*/
unsigned nCr_mod_prime(unsigned n, unsigned k) {
    if (k > n)
        return 0; // convention for http://en.wikipedia.org/wiki/Lucas%27_theorem
    if (0 == k)
        return 1;
    if (n == k)
        return 1;

    unsigned long nominator = 1L;
    unsigned long denominator = 1L;

    //
    for (unsigned i = 0; i < k; ++i) {
        nominator = (nominator * (n - i)) % PRIME;
        denominator = (denominator * (i + 1)) % PRIME;
    }

    // just nominator / denominator won't get us correct value because
    // we have been take modulo of them. We need http://en.wikipedia.org/wiki/Modular_multiplicative_inverse
    unsigned inverse = mod_mult_inverse(denominator);

    // now let's just do a x inverse
    unsigned res = (unsigned int) ((nominator * inverse) % PRIME);

    return res;
}

/**
* http://en.wikipedia.org/wiki/Modular_multiplicative_inverse
* m - is prime, so just do pow(a, m - 2)
*
* Time: logarithmic to number of bit in PRIME
*/
unsigned mod_mult_inverse(unsigned long a) {
    if (1 == a)
        return 1;
    unsigned res = 1;

    unsigned m = PRIME - 2;
    while (m > 0) {
        if (m & 1)
            res = (unsigned int) ((res * a) % PRIME);
        a = (a * a) % PRIME;
        m >>= 1;
    }

    return res;
}

