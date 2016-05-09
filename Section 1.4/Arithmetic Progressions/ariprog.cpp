/*
 ID: cloudzf2
 PROG: ariprog
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
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <set>

using namespace std;

bool m[125010];
int main(int argc, const char * argv[]) {
    ifstream fin ("ariprog.in");
    ofstream fout ("ariprog.out");
    int N, M;
    fin >> N >> M;
    memset(m, 0, sizeof(m));
    for (int i = 0; i <= M; i++) {
        for (int j = 0; j <= M; j++) {
            m[i * i + j * j] = true;
        }
    }
    bool hasValid = false;
    for (int diff = 1; diff <= 2 * M * M / (N - 1); diff++) {
        for (int i = 0; i <= 2 * M * M && i + diff * (N - 1) <= 2 * M * M; i++) {
            if (m[i]) {
                bool isValid = true;
                for (int j = 1; j < N; j++) {
                    if (!m[i + diff * j]) {
                        isValid = false;
                        break;
                    }
                }
                if (isValid) {
                    hasValid = true;
                    fout << i << " " << diff << endl;
                }
            }
        }
    }
    if (!hasValid) fout << "NONE" << endl;
    return 0;
}
