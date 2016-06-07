/*
 ID: cloudzf2
 PROG: betsy
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
int step[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool checkBoundary(int x, int y) {
    return x >= 0 && x < N && y >= 0 && y < N;
}

bool checkDeadEnd(vector<vector<bool> > & visited, int x, int y) {
    if ((!checkBoundary(x + 1, y) || visited[x + 1][y]) && (!checkBoundary(x - 1, y) || visited[x - 1][y])) {
        if (checkBoundary(x, y - 1) && !visited[x][y - 1] && checkBoundary(x, y + 1) && !visited[x][y + 1])
            return true;
    }
    if ((!checkBoundary(x, y - 1) || visited[x][y - 1]) && (!checkBoundary(x, y + 1) || visited[x][y + 1])) {
        if (checkBoundary(x - 1, y) && !visited[x - 1][y] && checkBoundary(x + 1, y) && !visited[x + 1][y])
            return true;
    }
    return false;
}

int countOutDegree(vector<vector<bool> > &visited, int x, int y) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        int x1 = x + step[i][0], y1 = y + step[i][1];
        if (checkBoundary(x1, y1) && !visited[x1][y1]) count++;
    }
    return count;
}
int dfs(vector<vector<bool> > &visited, int x, int y, int depth) {
    if (depth == N * N) {
        if (x == N - 1 && y == 0) return 1;
        return 0;
    }
    if (x == N - 1 && y == 0) return 0;
    if (checkDeadEnd(visited, x, y)) return 0;
    
    int myans = 0;
    visited[x][y] = true;
    int count = 0, idx = -1;
    for (int i = 0; i < 4; i++) {
        int x1 = x + step[i][0], y1 = y + step[i][1];
        if (checkBoundary(x1, y1) && !visited[x1][y1] && countOutDegree(visited, x1, y1) == 1) {
            if (x1 == N - 1 && y1 == 0) continue;
            count++;
            idx = i;
        }
    }
    if (count == 1) {
        myans += dfs(visited, x + step[idx][0], y + step[idx][1], depth + 1);
    } else {
        for (int i = 0; i < 4; i++) {
            int x1 = x + step[i][0], y1 = y + step[i][1];
            if (checkBoundary(x1, y1) && !visited[x1][y1]) {
                myans += dfs(visited, x1, y1, depth + 1);
            }
        }
    }
    visited[x][y] = false;
    return myans;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("betsy.in");
    ofstream fout ("betsy.out");
    fin >> N;
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    fout << dfs(visited, 0, 0, 1) << endl;
    return 0;
}
