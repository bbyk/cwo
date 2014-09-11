/* https://www.hackerrank.com/challenges/flowers */
#include <iostream>
#include <fstream>

using namespace std;

void merge_arrays(int *l, int size_l, int *r, int size_r, int *merge) {
    while (size_l > 0 || size_r > 0) {
        if (!size_l || (size_r && *l > *r)) {
            *merge++ = *r++;
            size_r--;
        } else {
            *merge++ = *l++;
            size_l--;
        }
    }
}

void merge_sort(int *input, int *merge, int size) {
    if (size <= 1) {
        return;
    }

    int m = size >> 1;

    merge_sort(input, merge, m);
    merge_sort(input + m, merge + m, size - m);

    merge_arrays(input, m, input + m, size - m, merge);

    while (size--)
        *input++ = *merge++;
}

void merge_sort(int *input, int size) {
    int merge[size];
    merge_sort(input, merge, size);
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

    int N, K;
    *file >> N >> K;
    int C[N];

    for (int i = 0; i < N; i++) {
        *file >> C[i];
    }

    merge_sort(C, N);

    unsigned result = 0;
    for (int i = 0; i < N; i++) {
        result += C[N - i - 1] * ((i / K) + 1);
    }

    cout << result << std::endl;

    return 0;
}
