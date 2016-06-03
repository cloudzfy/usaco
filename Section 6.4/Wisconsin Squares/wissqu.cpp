/*
 ID: cloudzf2
 PROG: wissqu
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

int f[4][4][5];
int visited[4][4];
int type[5];

struct node {
    int x, y;
    char t;
    node(int x, int y, char t) : x(x), y(y), t(t) {}
};

void setStat(int x, int y, int t, int val) {
    f[x][y][t] += val;
    if (x > 0) f[x - 1][y][t] += val;
    if (x < 3) f[x + 1][y][t] += val;
    if (y > 0) f[x][y - 1][t] += val;
    if (y < 3) f[x][y + 1][t] += val;
    if (x > 0 && y > 0) f[x - 1][y - 1][t] += val;
    if (x > 0 && y < 3) f[x - 1][y + 1][t] += val;
    if (x < 3 && y > 0) f[x + 1][y - 1][t] += val;
    if (x < 3 && y < 3) f[x + 1][y + 1][t] += val;
}

void initialization(vector<string> &maps) {
    memset(f, 0, sizeof(f));
    memset(type, 0, sizeof(type));
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int t = maps[i][j] - 'A';
            setStat(i, j, t, 1);
            type[t]++;
        }
    }
    type[2]--;
}

bool dfs1(vector<string> &maps, vector<node> &ans) {
    if (ans.size() == 16) return true;
    for (int t = 0; t < 5; t++) {
        if (type[t] > 0) {
            type[t]--;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (!visited[i][j] && maps[i][j] != 'A' + t && f[i][j][t] == 0) {
                        visited[i][j] = 1;
                        ans.push_back(node(i + 1, j + 1, 'A' + t));
                        setStat(i, j, maps[i][j] - 'A', -1);
                        setStat(i, j, t, 1);
                        if (dfs1(maps, ans)) return true;
                        visited[i][j] = 0;
                        ans.pop_back();
                        setStat(i, j, maps[i][j] - 'A', 1);
                        setStat(i, j, t, -1);
                    }
                }
            }
            type[t]++;
        }
    }
    return false;
}

int dfs2(vector<string> &maps, int depth) {
    if (depth == 16) return 1;
    int ans = 0;
    for (int t = 0; t < 5; t++) {
        if (type[t] > 0) {
            type[t]--;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (!visited[i][j] && maps[i][j] != 'A' + t && f[i][j][t] == 0) {
                        visited[i][j] = 1;
                        setStat(i, j, maps[i][j] - 'A', -1);
                        setStat(i, j, t, 1);
                        ans += dfs2(maps, depth + 1);
                        visited[i][j] = 0;
                        setStat(i, j, maps[i][j] - 'A', 1);
                        setStat(i, j, t, -1);
                    }
                }
            }
            type[t]++;
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("wissqu.in");
    ofstream fout ("wissqu.out");
    vector<string> maps(4, "");
    for (int i = 0; i < 4; i++) {
        fin >> maps[i];
    }
    initialization(maps);
    vector<node> ans;
    bool isValid = false;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!visited[i][j] && maps[i][j] != 'D' && f[i][j][3] == 0) {
                visited[i][j] = 1;
                ans.push_back(node(i + 1, j + 1, 'D'));
                setStat(i, j, maps[i][j] - 'A', -1);
                setStat(i, j, 3, 1);
                if (dfs1(maps, ans)) {
                    isValid = true;
                    break;
                }
                visited[i][j] = 0;
                ans.pop_back();
                setStat(i, j, maps[i][j] - 'A', 1);
                setStat(i, j, 3, -1);
            }
        }
        if (isValid) break;
    }
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i].t << " " << ans[i].x << " " << ans[i].y << endl;
    }
    initialization(maps);
    int total = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!visited[i][j] && maps[i][j] != 'D' && f[i][j][3] == 0) {
                visited[i][j] = 1;
                setStat(i, j, maps[i][j] - 'A', -1);
                setStat(i, j, 3, 1);
                total += dfs2(maps, 1);
                visited[i][j] = 0;
                setStat(i, j, maps[i][j] - 'A', 1);
                setStat(i, j, 3, -1);
            }
        }
    }
    fout << total << endl;
    return 0;
}
