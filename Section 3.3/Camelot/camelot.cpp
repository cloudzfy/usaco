/*
 ID: cloudzf2
 PROG: camelot
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

using namespace std;

#define INT_MAX 2147483647

int king[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
int knight[8][2] = {{-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};

bool isInRange(int x, int left, int right) {
    return x >= left && x < right;
}

void bfsKing(vector<vector<int> > &kingSteps, int R, int C) {
    queue<int> q;
    kingSteps[0][0] = 0;
    q.push(0);
    while (!q.empty()) {
        int x = q.front() / C;
        int y = q.front() % C;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int x1 = x + king[i][0];
            int y1 = y + king[i][1];
            if (isInRange(x1, 0, R) && isInRange(y1, 0, C)) {
                if (kingSteps[x1][y1] == -1 || kingSteps[x1][y1] > kingSteps[x][y] + 1) {
                    kingSteps[x1][y1] = kingSteps[x][y] + 1;
                    q.push(x1 * C + y1);
                }
            }
        }
    }
}

void bfsKnights(vector<vector<int> > &knightSteps, int x, int y, int R, int C) {
    vector<vector<int> > knightStep(R, vector<int>(C, -1));
    queue<int> q;
    knightStep[x][y] = 0;
    q.push(x * C + y);
    while (!q.empty()) {
        int x = q.front() / C;
        int y = q.front() % C;
        q.pop();
        for (int i = 0; i < 8; i++) {
            int x1 = x + knight[i][0];
            int y1 = y + knight[i][1];
            if (isInRange(x1, 0, R) && isInRange(y1, 0, C)) {
                if (knightStep[x1][y1] == -1 || knightStep[x1][y1] > knightStep[x][y] + 1) {
                    knightStep[x1][y1] = knightStep[x][y] + 1;
                    q.push(x1 * C + y1);
                }
            }
        }
    }
    int pos = x * C + y;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            knightSteps[pos][i * C + j] = knightStep[i][j];
            knightSteps[i * C + j][pos] = knightStep[i][j];
        }
    }
}

int solve(vector<vector<int> > &kingSteps, vector<vector<int> > &knightSteps, vector<pair<int, int> > &pos, int x, int y, int R, int C) {
    int kingMove = kingSteps[abs(pos[0].first - x)][abs(pos[0].second - y)];
    int myans = 0;
    bool isValid = true;
    for (int i = 1; i < pos.size(); i++) {
        if (knightSteps[pos[i].first * C + pos[i].second][x * C + y] == -1) isValid = false;
        myans += knightSteps[pos[i].first * C + pos[i].second][x * C + y];
    }
    int ans = INT_MAX;
    if (isValid) ans = kingMove + myans;
    for (int t = 0; t <= 2; t++) {
        for (int i = 0; i < 8; i++) {
            int x1 = pos[0].first + king[i][0] * t;
            int y1 = pos[0].second + king[i][1] * t;
            if (!isInRange(x1, 0, R) || !isInRange(y1, 0, C)) continue;
            kingMove = kingSteps[abs(pos[0].first - x1)][abs(pos[0].second - y1)];
            if (knightSteps[x1 * C + y1][x * C + y] == -1) continue;
            int knightMove = knightSteps[x1 * C + y1][x * C + y];
            for (int j = 1; j < pos.size(); j++) {
                if (knightSteps[pos[j].first * C + pos[j].second][x * C + y] == -1) continue;
                if (knightSteps[pos[j].first * C + pos[j].second][x1 * C + y1] == -1) continue;
                ans = min(ans, myans - knightSteps[pos[j].first * C + pos[j].second][x * C + y] + knightSteps[pos[j].first * C + pos[j].second][x1 * C + y1] + knightMove + kingMove);
            }
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("camelot.in");
    ofstream fout ("camelot.out");
    int R, C;
    fin >> R >> C;
    vector<pair<int, int> > pos;
    char ch;
    int x;
    while (fin >> ch >> x) {
        pos.push_back(make_pair(x - 1, ch - 'A'));
    }
    vector<vector<int> > kingSteps(R, vector<int>(C, -1));
    vector<vector<int> > knightSteps(R * C, vector<int>(R * C, -1));
    bfsKing(kingSteps, R, C);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            bfsKnights(knightSteps, i, j, R, C);
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            ans = min(ans, solve(kingSteps, knightSteps, pos, i, j, R, C));
        }
    }
    fout << ans << endl;
    return 0;
}
