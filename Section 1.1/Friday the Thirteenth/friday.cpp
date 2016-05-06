/*
 ID: cloudzf2
 PROG: friday
 LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cstring>
#include <vector>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("friday.in");
    ofstream fout ("friday.out");
    int N;
    fin >> N;
    vector<int> count(7, 0);
    int months1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int months2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day = 1;
    for (int i = 0; i < N; i++) {
        bool isLeap = false;
        if ((1900 + i) % 100 == 0) {
            if ((1900 + i) % 400 == 0) isLeap = true;
        } else if ((1900 + i) % 4 == 0) {
            isLeap = true;
        }
        for (int j = 0; j < 12; j++) {
            count[(day + 13) % 7]++;
            if (isLeap) day += months2[j];
            else day += months1[j];
        }
    }
    for (int i = 0; i < 7; i++) {
        if (i != 0) fout << " ";
        fout << count[i];
    }
    fout << endl;
    return 0;
}
