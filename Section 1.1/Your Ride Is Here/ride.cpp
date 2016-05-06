/*
 ID: cloudzf2
 PROG: ride
 LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("ride.in");
    ofstream fout ("ride.out");
    string a, b;
    fin >> a >> b;
    int x = 1, y = 1;
    for (int i = 0; i < a.length(); i++) {
        x *= a[i] - 'A' + 1;
    }
    for (int i = 0; i < b.length(); i++) {
        y *= b[i] - 'A' + 1;
    }
    if (x % 47 == y % 47) fout << "GO" << endl;
    else fout << "STAY" << endl;
    return 0;
}
