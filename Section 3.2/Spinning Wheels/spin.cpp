/*
 ID: cloudzf2
 PROG: spin
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
    ifstream fin ("spin.in");
    ofstream fout ("spin.out");
    vector<int> speed(5, 0);
    vector<vector<pair<int, int> > > wedges(5, vector<pair<int, int> >());
    for (int i = 0; i < 5; i++) {
        int W, s, e;
        fin >> speed[i];
        fin >> W;
        for (int j = 0; j < W; j++) {
            fin >> s >> e;
            wedges[i].push_back(make_pair(s, e));
        }
    }
    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < 360; j++) {
            bool allWheel = true;
            for (int k = 0; k < 5; k++) {
                bool oneWheel = false;
                for (int l = 0; l < wedges[k].size(); l++) {
                    if (wedges[k][l].first <= j && wedges[k][l].first + wedges[k][l].second >= j) oneWheel = true;
                    if (wedges[k][l].first > j && wedges[k][l].first + wedges[k][l].second >= 360 + j) oneWheel = true;
                }
                if (!oneWheel) {
                    allWheel = false;
                    break;
                }
            }
            if (allWheel) {
                fout << i << endl;
                return 0;
            }
        }
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < wedges[j].size(); k++) {
                wedges[j][k].first = (wedges[j][k].first + speed[j]) % 360;
            }
        }
    }
    fout << "none" << endl;
    return 0;
}
