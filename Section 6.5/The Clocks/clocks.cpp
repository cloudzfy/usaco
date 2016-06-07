/*
 ID: cloudzf2
 PROG: clocks
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

struct node {
    vector<int> clocks;
    vector<int> moves;
    int next;
    node(vector<int> &clocks, vector<int> &moves, int next) : clocks(clocks), moves(moves), next(next) {}
};

struct cmp {
    bool operator()(const node &a, const node &b) {
        if (a.moves.size() == b.moves.size()) {
            for (int i = 0; i < a.moves.size(); i++) {
                if (a.moves[i] != b.moves[i]) return a.moves[i] > b.moves[i];
            }
            return true;
        }
        return a.moves.size() > b.moves.size();
    }
};

int step[9][9] = {{1, 1, 0, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 1, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 1, 1, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 1, 1, 1},
    {0, 0, 0, 0, 1, 1, 0, 1, 1}};

int m[300000];

int getCode(vector<int> &clocks) {
    int code = 0;
    for (int i = 0; i < 9; i++) {
        code <<= 2;
        code += clocks[i];
    }
    return code;
}

node bfs(vector<int> &clocks) {
    priority_queue<node, vector<node>, cmp> q;
    vector<int> moves;
    q.push(node(clocks, moves, 0));
    m[getCode(clocks)] = 1;
    while (!q.empty()) {
        node u = q.top();
        q.pop();
        int code = getCode(u.clocks);
        if (code == 0) return u;
        m[code] = 1;
        if (u.next == 9) continue;
        int s = u.next++;
        if (s == 4 && u.clocks[0] != 0) continue;
        q.push(u);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < u.clocks.size(); j++) {
                u.clocks[j] = (u.clocks[j] + step[s][j]) % 4;
            }
            u.moves.push_back(s + 1);
            if (m[getCode(u.clocks)]) continue;
            q.push(u);
        }
    }
    return node(clocks, moves, 0);
}

int main(int argc, const char * argv[]) {
    ifstream fin ("clocks.in");
    ofstream fout ("clocks.out");
    vector<int> clocks(9, 0);
    for (int i = 0; i < 9; i++) {
        fin >> clocks[i];
        clocks[i] = (clocks[i] / 3) % 4;
    }
    memset(m, 0, sizeof(m));
    node ans = bfs(clocks);
    for (int i = 0; i < ans.moves.size(); i++) {
        if (i != 0) fout << " ";
        fout << ans.moves[i];
    }
    fout << endl;
    return 0;
}
