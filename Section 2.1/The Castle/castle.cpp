/*
 ID: cloudzf2
 PROG: castle
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

using namespace std;

int dfs(vector<vector<int> > &maps, vector<vector<int> > &colors, int i, int j, int color) {
    int count = 1;
    colors[i][j] = color;
    if (!(maps[i][j] & 8) && colors[i + 1][j] == -1) count += dfs(maps, colors, i + 1, j, color);
    if (!(maps[i][j] & 4) && colors[i][j + 1] == -1) count += dfs(maps, colors, i, j + 1, color);
    if (!(maps[i][j] & 2) && colors[i - 1][j] == -1) count += dfs(maps, colors, i - 1, j, color);
    if (!(maps[i][j] & 1) && colors[i][j - 1] == -1) count += dfs(maps, colors, i, j - 1, color);
    return count;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("castle.in");
    ofstream fout ("castle.out");
    int M, N;
    fin >> M >> N;
    vector<vector<int> > maps(N, vector<int>(M, 0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            fin >> maps[i][j];
        }
    }
    vector<vector<int> > colors(N, vector<int>(M, -1));
    vector<int> count;
    int color = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (colors[i][j] == -1) {
                count.push_back(dfs(maps, colors, i, j, color));
                color++;
            }
        }
    }
    int maxSize = 0;
    for (int i = 0; i < count.size(); i++) {
        maxSize = max(maxSize, count[i]);
    }
    int largest = 0;
    int idx = 0, idy = 0;
    string dr;
    for (int j = 0; j < M; j++) {
        for (int i = N - 1; i >= 0; i--) {
            if ((maps[i][j] & 2) && i - 1 >= 0) {
                if (colors[i][j] != colors[i - 1][j] && count[colors[i][j]] + count[colors[i - 1][j]] > largest) {
                    largest = count[colors[i][j]] + count[colors[i - 1][j]];
                    idx = i + 1;
                    idy = j + 1;
                    dr = "N";
                }
            }
            if ((maps[i][j] & 4) && j + 1 < M) {
                if (colors[i][j] != colors[i][j + 1] && count[colors[i][j]] + count[colors[i][j + 1]] > largest) {
                    largest = count[colors[i][j]] + count[colors[i][j + 1]];
                    idx = i + 1;
                    idy = j + 1;
                    dr = "E";
                }
            }
        }
    }
    fout << color << endl;
    fout << maxSize << endl;
    fout << largest << endl;
    fout << idx << " " << idy << " " << dr << endl;
    return 0;
}
