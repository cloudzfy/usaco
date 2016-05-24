/*
 ID: cloudzf2
 PROG: snail
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

int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

struct node {
    int x, y, d;
    node(int x, int y, int d) : x(x), y(y), d(d) {}
};

int toInt(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num *= 10;
        num += s[i] - '0';
    }
    return num;
}

bool checkValid(int x, int y, int N) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

void dfs(vector<vector<char> > &maps, vector<vector<bool> > &visited, int N, int x, int y, int d, int step, int &ans) {
    ans = max(ans, step);
    visited[x][y] = true;
    int x1 = x + direction[d][0];
    int y1 = y + direction[d][1];
    if (checkValid(x1, y1, N) && maps[x1][y1] == '.') {
        if (!visited[x1][y1]) dfs(maps, visited, N, x1, y1, d, step + 1, ans);
    } else {
        x1 = x + direction[(d + 1) % 4][0];
        y1 = y + direction[(d + 1) % 4][1];
        if (checkValid(x1, y1, N) && maps[x1][y1] == '.' && !visited[x1][y1]) {
            dfs(maps, visited, N, x1, y1, (d + 1) % 4, step + 1, ans);
        }
        x1 = x + direction[(d + 3) % 4][0];
        y1 = y + direction[(d + 3) % 4][1];
        if (checkValid(x1, y1, N) && maps[x1][y1] == '.' && !visited[x1][y1]) {
            dfs(maps, visited, N, x1, y1, (d + 3) % 4, step + 1, ans);
        }
    }
    visited[x][y] = false;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("snail.in");
    ofstream fout ("snail.out");
    int N, B;
    fin >> N >> B;
    vector<vector<char> > maps(N, vector<char>(N, '.'));
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    string s;
    for (int i = 0; i < B; i++) {
        fin >> s;
        int x = toInt(s.substr(1)) - 1;
        int y = s[0] - 'A';
        maps[x][y] = '#';
    }
    int ans = 0;
    dfs(maps, visited, N, 0, 0, 1, 1, ans);
    dfs(maps, visited, N, 0, 0, 2, 1, ans);
    fout << ans << endl;
    return 0;
}
