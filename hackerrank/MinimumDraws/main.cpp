#include <iostream>
#include <fstream>

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

    unsigned T, N;
    *file >> T;

    while (T--) {
        *file >> N;
        cout << N + 1 << endl;
    }
}
