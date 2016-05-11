/*
 ID: cloudzf2
 PROG: ttwo
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

int main(int argc, const char * argv[]) {
    ifstream fin ("ttwo.in");
    ofstream fout ("ttwo.out");
    int N = 10;
    vector<string> maps(N, string());
    for (int i = 0; i < N; i++) {
        fin >> maps[i];
    }
    int xf = 0, yf = 0, xc = 0, yc = 0;
    int direction[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int stepF = 0, stepC = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (maps[i][j] == 'F') {
                xf = i;
                yf = j;
            }
            if (maps[i][j] == 'C') {
                xc = i;
                yc = j;
            }
        }
    }
    bool visited[10][10][4][10][10][4];
    memset(visited, 0, sizeof(visited));
    int count = 1;
    while (true) {
        if (xf + direction[stepF][0] < 0 || xf + direction[stepF][0] >= N) stepF = (stepF + 1) % 4;
        else if (yf + direction[stepF][1] < 0 || yf + direction[stepF][1] >= N) stepF = (stepF + 1) % 4;
        else if (maps[xf + direction[stepF][0]][yf + direction[stepF][1]] == '*') stepF = (stepF + 1) % 4;
        else {
            xf += direction[stepF][0];
            yf += direction[stepF][1];
        }
        if (xc + direction[stepC][0] < 0 || xc + direction[stepC][0] >= N) stepC = (stepC + 1) % 4;
        else if (yc + direction[stepC][1] < 0 || yc + direction[stepC][1] >= N) stepC = (stepC + 1) % 4;
        else if (maps[xc + direction[stepC][0]][yc + direction[stepC][1]] == '*') stepC = (stepC + 1) % 4;
        else {
            xc += direction[stepC][0];
            yc += direction[stepC][1];
        }
        if (xf == xc && yf == yc) {
            fout << count << endl;
            return 0;
        }
        count++;
        if (visited[xf][yf][stepF][xc][yc][stepC]) {
            fout << 0 << endl;
            return 0;
        } else visited[xf][yf][stepF][xc][yc][stepC] = true;
    }
    return 0;
}
