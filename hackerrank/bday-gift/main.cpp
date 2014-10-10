#include <iostream>
#include <fstream>

using namespace std;

/**
* Expectation is sum of products: x * p(x) where x - the outcome of a random function
* and p(x) is a probability of the outcome.
*/
double calc_expectation(unsigned *nb, unsigned len) {
    long res = 0L;
    for (int i = 0; i < len; ++i) {
        res += nb[i];
    }
    return res / 2.0;
}

int main(int argc, const char *argv[]) {

    ifstream st;
    istream *in_file;
    //Helpers for input and output
    if (argc > 1) {
        st.open(argv[1], ios::in);
        in_file = &st;
    } else {
        in_file = &cin;
    }

    unsigned T;
    *in_file >> T;

    unsigned nb[T];

    for (int i = 0; i < T; ++i)
        *in_file >> nb[i];

    std::printf("%.1f", calc_expectation(nb, T));

    return 0;
}