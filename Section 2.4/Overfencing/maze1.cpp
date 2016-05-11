/*
 ID: cloudzf2
 PROG: maze1
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

using namespace std;

#define INT_MAX 2147483647
int W, H;

void dfs(vector<vector<int> > &maps, vector<string> &maze, int i, int j, int step) {
    maps[i][j] = step;
    if (i - 1 >= 0 && maze[2 * i][2 * j + 1] == ' ' && maps[i - 1][j] > step + 1) {
        dfs(maps, maze, i - 1, j, step + 1);
    }
    if (i + 1 < H && maze[2 * i + 2][2 * j + 1] == ' ' && maps[i + 1][j] > step + 1) {
        dfs(maps, maze, i + 1, j, step + 1);
    }
    if (j - 1 >= 0 && maze[2 * i + 1][2 * j] == ' ' && maps[i][j - 1] > step + 1) {
        dfs(maps, maze, i, j - 1, step + 1);
    }
    if (j + 1 < W && maze[2 * i + 1][2 * j + 2] == ' ' && maps[i][j + 1] > step + 1) {
        dfs(maps, maze, i, j + 1, step + 1);
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("maze1.in");
    ofstream fout ("maze1.out");
    fin >> W >> H;
    string ch;
    getline(fin, ch);
    vector<string> maze(2 * H + 1, string());
    for (int i = 0; i < 2 * H + 1; i++) {
        getline(fin, maze[i]);
    }
    vector<vector<int> > maps(H, vector<int>(W, INT_MAX));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 0 && maze[0][2 * j + 1] == ' ') {
                dfs(maps, maze, i, j, 1);
            } else if (i == H - 1 && maze[2 * H][2 * j + 1] == ' ') {
                dfs(maps, maze, i, j, 1);
            } else if (j == 0 && maze[2 * i + 1][0] == ' ') {
                dfs(maps, maze, i, j, 1);
            } else if (j == W - 1 && maze[2 * i + 1][2 * W] == ' ') {
                dfs(maps, maze, i, j, 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ans = max(ans, maps[i][j]);
        }
    }
    fout << ans << endl;
    return 0;
}
