/*
 ID: cloudzf2
 PROG: gift1
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
    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");
    int np, money, ng;
    fin >> np;
    unordered_map<string, int> m;
    vector<string> name(np);
    for (int i = 0; i < np; i++) {
        fin >> name[i];
        m[name[i]] = 0;
    }
    string giver, givee;
    for (int i = 0; i < np; i++) {
        fin >> giver;
        fin >> money >> ng;
        m[giver] -= money;
        if (ng == 0) continue;
        int tmp = money / ng;
        for (int j = 0; j < ng; j++) {
            fin >> givee;
            m[givee] += tmp;
            money -= tmp;
        }
        m[giver] += money;
    }
    for (int i = 0; i < np; i++) {
        fout << name[i] << " " << m[name[i]] <<endl;
    }
    return 0;
}
