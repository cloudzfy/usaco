/*
 ID: cloudzf2
 PROG: picture
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

struct line {
    int x1, x2, y;
    bool isFirst;
    line(int x1, int x2, int y, int isFirst) : x1(x1), x2(x2), y(y), isFirst(isFirst) {}
};

bool cmp(const line &a, const line &b) {
    if (a.y == b.y) {
        if (a.isFirst && b.isFirst) return a.x1 < b.x1;
        return a.isFirst;
    }
    return a.y < b.y;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("picture.in");
    ofstream fout ("picture.out");
    int N, x1, x2, y1, y2;
    fin >> N;
    vector<line> vertical;
    vector<line> hortizontal;
    int top = 10000, bottom = -10000, left = 10000, right = -10000;
    for (int i = 0; i < N; i++) {
        fin >> x1 >> y1 >> x2 >> y2;
        vertical.push_back(line(y1, y2, x1, true));
        vertical.push_back(line(y1, y2, x2, false));
        hortizontal.push_back(line(x1, x2, y1, true));
        hortizontal.push_back(line(x1, x2, y2, false));
        top = min(top, y1);
        bottom = max(bottom, y2);
        left = min(left, x1);
        right = max(right, x2);
    }
    int ans = 0;
    sort(vertical.begin(), vertical.end(), cmp);
    vector<int> count1(bottom - top, 0);
    for (int i = 0; i < vertical.size(); i++) {
        for (int j = vertical[i].x1 - top; j < vertical[i].x2 - top; j++) {
            if (vertical[i].isFirst) {
                if (count1[j] == 0) ans++;
                count1[j]++;
            } else {
                if (count1[j] == 1) ans++;
                count1[j]--;
            }
        }
    }
    sort(hortizontal.begin(), hortizontal.end(), cmp);
    vector<int> count2(right - left, 0);
    for (int i = 0; i < hortizontal.size(); i++) {
        for (int j = hortizontal[i].x1 - left; j < hortizontal[i].x2 - left; j++) {
            if (hortizontal[i].isFirst) {
                if (count2[j] == 0) ans++;
                count2[j]++;
            } else {
                if (count2[j] == 1) ans++;
                count2[j]--;
            }
        }
    }
    fout << ans << endl;
    return 0;
}
