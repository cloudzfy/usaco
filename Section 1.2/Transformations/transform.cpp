/*
 ID: cloudzf2
 PROG: transform
 LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

bool rotation90(vector<string> &A, vector<string> &B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[j][N - i - 1]) return false;
        }
    }
    return true;
}

bool rotation180(vector<string> &A, vector<string> &B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[N - i - 1][N - j - 1]) return false;
        }
    }
    return true;
}

bool rotation270(vector<string> &A, vector<string> &B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[N - j - 1][i]) return false;
        }
    }
    return true;
}

bool reflection(vector<string> &A, vector<string> &B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[i][N - j - 1]) return false;
        }
    }
    return true;
}

bool combination(vector<string> &A, vector<string> &B, int N) {
    vector<string> C(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            C[i][j] = A[i][N - j - 1];
        }
    }
    if (!rotation90(C, B, N) && !rotation180(C, B, N) && !rotation270(C, B, N)) return false;
    return true;
}

bool noChange(vector<string> &A, vector<string> &B, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (A[i][j] != B[i][j]) return false;
        }
    }
    return true;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("transform.in");
    ofstream fout ("transform.out");
    int N;
    fin >> N;
    vector<string> before(N);
    vector<string> after(N);
    for (int i = 0; i < N; i++) {
        fin >> before[i];
    }
    for (int i = 0; i < N; i++) {
        fin >> after[i];
    }
    if (rotation90(before, after, N)) fout << 1 << endl;
    else if (rotation180(before, after, N)) fout << 2 << endl;
    else if (rotation270(before, after, N)) fout << 3 << endl;
    else if (reflection(before, after, N)) fout << 4 << endl;
    else if (combination(before, after, N)) fout << 5 << endl;
    else if (noChange(before, after, N)) fout << 6 << endl;
    else fout << 7 << endl;
    return 0;
}
