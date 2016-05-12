/*
 ID: cloudzf2
 PROG: fact4
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
#include <map>
#include <iomanip>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("fact4.in");
    ofstream fout ("fact4.out");
    int N;
    fin >> N;
    int num = 1, two = 0, five = 0;
    for (int i = 2; i <= N; i++) {
        int tmp = i;
        while (tmp % 2 == 0) {
            tmp /= 2;
            two++;
        }
        while (tmp % 5 == 0) {
            tmp /= 5;
            five++;
        }
        num = (num * tmp) % 10;
    }
    if (two - five == 0) {
        fout << num << endl;
    } else {
        int twos[4] = {6, 2, 4, 8};
        fout << (twos[(two - five) % 4] * num) % 10 << endl;
    }
    return 0;
}
