/*
 ID: cloudzf2
 PROG: packrec
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
#include <stack>
#include <cmath>

using namespace std;

#define INF 2147483647

vector<vector<pair<int, int> > > M;

void dfs(vector<pair<int, int> > &rects, vector<pair<int, bool> > &myans, int cur) {
    if (cur == 4) {
        vector<pair<int, int> > tmp;
        for (int i = 0; i < 4; i++) {
            if (myans[i].second) {
                tmp.push_back(make_pair(rects[myans[i].first].second, rects[myans[i].first].first));
            } else {
                tmp.push_back(make_pair(rects[myans[i].first].first, rects[myans[i].first].second));
            }
        }
        M.push_back(tmp);
        return;
    }
    for (int i = 0; i < 4; i++) {
        bool isValid = true;
        for (int j = 0; j < myans.size(); j++) {
            if (myans[j].first == i) {
                isValid = false;
                break;
            }
        }
        if (isValid) {
            myans.push_back(make_pair(i, false));
            dfs(rects, myans, cur + 1);
            myans.pop_back();
            myans.push_back(make_pair(i, true));
            dfs(rects, myans, cur + 1);
            myans.pop_back();
        }
    }
}

void checkAns(set<pair<int, int> > &ans, int &area, int a, int b) {
    if (a > b) swap(a, b);
    if (area > a * b) {
        ans.clear();
        area = a * b;
        ans.insert(make_pair(a, b));
    } else if (area == a * b) {
        ans.insert(make_pair(a, b));
    }
}
int main(int argc, const char * argv[]) {
    ifstream fin ("packrec.in");
    ofstream fout ("packrec.out");
    vector<pair<int, int> > rects;
    int a, b;
    for (int i = 0; i < 4; i++) {
        fin >> a >> b;
        rects.push_back(make_pair(a, b));
    }
    vector<pair<int, bool>> myans;
    dfs(rects, myans, 0);
    set<pair<int, int> > ans;
    int area = INF;
    for (int i = 0; i < M.size(); i++) {
        a = M[i][0].first + M[i][1].first + M[i][2].first + M[i][3].first;
        b = max(M[i][0].second, max(M[i][1].second, max(M[i][2].second, M[i][3].second)));
        checkAns(ans, area, a, b);
        a = max(M[i][0].first, M[i][1].first + M[i][2].first + M[i][3].first);
        b = M[i][0].second + max(M[i][1].second, max(M[i][2].second, M[i][3].second));
        checkAns(ans, area, a, b);
        a = max(M[i][0].first, M[i][1].first + M[i][2].first) + M[i][3].first;
        b = max(max(M[i][1].second, M[i][2].second) + M[i][0].second, M[i][3].second);
        checkAns(ans, area, a, b);
        a = M[i][0].first + M[i][3].first + max(M[i][1].first, M[i][2].first);
        b = max(M[i][0].second, max(M[i][3].second, M[i][1].second + M[i][2].second));
        checkAns(ans, area, a, b);
        if (M[i][1].second > M[i][3].second && M[i][2].first > M[i][3].first) continue;
        if (M[i][1].second < M[i][3].second && M[i][0].first > M[i][1].first) continue;
        a = max(M[i][0].first + M[i][2].first, M[i][1].first + M[i][3].first);
        b = max(M[i][0].second + M[i][1].second, M[i][2].second + M[i][3].second);
        checkAns(ans, area, a, b);
    }
    fout << area << endl;
    for (auto it = ans.begin(); it != ans.end(); it++) {
        fout << it->first << " " << it->second << endl;
    }
    return 0;
}
