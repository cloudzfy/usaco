/*
 ID: cloudzf2
 PROG: fence8
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

bool dfs(vector<int> &remain, vector<int> &rail, int now, int cur, int maxWaste) {
    if (cur < 0) return true;
    int waste = 0;
    for (int i = 0; i < remain.size(); i++) {
        if (remain[i] < rail[0]) waste += remain[i];
    }
    if (waste > maxWaste) return false;
    if (now != 0 && rail[cur] != rail[cur + 1]) now = 0;
    for (int i = now; i < remain.size(); i++) {
        if (remain[i] < rail[cur]) continue;
        remain[i] -= rail[cur];
        if (dfs(remain, rail, i, cur - 1, maxWaste)) return true;
        remain[i] += rail[cur];
    }
    return false;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("fence8.in");
    ofstream fout ("fence8.out");
    int N, R;
    fin >> N;
    vector<int> board(N, 0);
    int sumBoard = 0;
    for (int i = 0; i < N; i++) {
        fin >> board[i];
        sumBoard += board[i];
    }
    fin >> R;
    vector<int> rail(R, 0);
    int sumRail = 0;
    for (int i = 0; i < R; i++) {
        fin >> rail[i];
        sumRail += rail[i];
    }
    sort(rail.begin(), rail.end());
    int left = 0, right = R - 1;
    while (right >= 0 && sumRail > sumBoard) {
        sumRail -= rail[right];
        right--;
    }
    vector<int> maxWaste(right + 1, 0);
    maxWaste[0] = rail[0];
    for (int i = 1; i <= right; i++) {
        maxWaste[i] = maxWaste[i - 1] + rail[i];
    }
    for (int i = 0; i <= right; i++) {
        maxWaste[i] = sumBoard - maxWaste[i];
    }
    bool isValid = false;
    for (int i = 0; i < board.size(); i++) {
        if (board[i] >= rail[0]) {
            isValid = true;
            break;
        }
    }
    if (left > right || !isValid) {
        fout << 0 << endl;
        return 0;
    }
    while (left < right) {
        int mid = (left + right + 1) / 2;
        vector<int> remain = board;
        if (dfs(remain, rail, 0, mid, maxWaste[mid])) left = mid;
        else right = mid - 1;
    }
    fout << left + 1 << endl;
    return 0;
}
