/*
 ID: cloudzf2
 PROG: latin
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

int N;
int full, ans;
int row[7][8], col[7][8];
int m[7], visited[7];
long long gCount[8];
int fact[7] = {0, 1, 2, 6, 24, 120, 720};

int find() {
    int ans = 2;
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            int count = 0, p = i;
            do {
                visited[p] = 1;
                p = m[p];
                count++;
            } while (!visited[p]);
            ans = max(ans, count);
        }
    }
    return ans;
}

long long dfs(int x, int y, int group) {
    if (x == N - 1) {
        gCount[group]++;
        return 1;
    }
    long long ans = 0;
    for (int i = 0; i < N; i++) {
        if (!row[x][i] && !col[y][i]) {
            if (x == 1) {
                m[y] = i;
                if (y == N - 1) {
                    group = find();
                    if (gCount[group] > 0) return gCount[group];
                }
            }
            row[x][i] = 1;
            col[y][i] = 1;
            if (y < N - 1) ans += dfs(x, y + 1, group);
            else ans += dfs(x + 1, 1, group);
            row[x][i] = 0;
            col[y][i] = 0;
        }
    }
    return ans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("latin.in");
    ofstream fout ("latin.out");
    fin >> N;
    memset(m, 0, sizeof(m));
    memset(row, 0, sizeof(row));
    memset(col, 0, sizeof(col));
    memset(gCount, 0, sizeof(gCount));
    for (int i = 0; i < N; i++) {
        col[i][i] = 1;
        row[i][i] = 1;
    }
    m[0] = 1;
    fout << dfs(1, 1, 0) * fact[N - 1] << endl;
    return 0;
}
