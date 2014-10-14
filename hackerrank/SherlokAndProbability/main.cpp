#include <iostream>
#include <fstream>
#include <tuple>
#include <sstream>
#include <algorithm>

// https://www.hackerrank.com/challenges/sherlock-and-probability

using namespace std;

typedef tuple<unsigned long, unsigned long> fraction;

class Solution {
    unsigned K, N;
    string line;

public:
    Solution(string &line, unsigned N, unsigned K) : line(line), N(N), K(K) {
    }

    string to_string();

private:
    fraction abs_ji_is_less_k();

    static unsigned long gcd(unsigned long l, unsigned long r);
};

unsigned long Solution::gcd(unsigned long l, unsigned long r) {
    if (l < r) {
        unsigned long tmp = r;
        r = l;
        l = tmp;
    }

    if (0 == r)
        return l;
    if (1 == r)
        return 1;

    if ((l & 1) && (r & 1)) {
        return gcd(l - r, r);
    } else if (!(l & 1) && (r & 1)) {
        return gcd(l >> 1, r);
    } else if ((l & 1) && !(r & 1)) {
        return gcd(l, r >> 1);
    } else if (!(l & 1) && !(r & 1)) {
        return gcd(l >> 1, r >> 1) << 1;
    }
    return 0;
}

fraction Solution::abs_ji_is_less_k() {
    unsigned long dd = 0L;
    unsigned long dr = ((unsigned long) N) * N;
    int Kp = 0;
    int Ka = 0;

    for (unsigned i = 0; i <= K && i < N; ++i)
        if ('1' == line[i])
            Ka++;

    for (unsigned i = 0; i < N; ++i) {
        if ('1' == line[i]) {
            dd += Kp;
            dd += Ka;

            Kp++;
            if (i >= K && '1' == line[i - K])
                Kp--;
            if (i + 1 >= N - K || '0' == line[i + K + 1])
                Ka--;
        } else {
            if (i + 1 < N - K && '1' == line[i + K + 1])
                Ka++;
            if (i >= K && '1' == line[i - K])
                Kp--;
        }
    }

    unsigned long gcd = Solution::gcd(dd, dr);
    return make_tuple(dd / gcd, dr / gcd);
}


string Solution::to_string() {
    fraction p = abs_ji_is_less_k();
    if (0 == get<0>(p))
        return "0/1";

    stringstream ss;
    ss << get<0>(p) << '/' << get<1>(p);

    return ss.str();
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

    unsigned T, N, K;
    string line;
    *file >> T;

    while (T--) {
        *file >> N >> K;
        *file >> line;
        auto s = Solution(line, N, K);
        cout << s.to_string() << endl;
    }
}

