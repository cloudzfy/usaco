/*
 ID: cloudzf2
 PROG: job
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

using namespace std;

struct cmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) {
        return a.first + a.second > b.first + b.second;
    }
};

int main(int argc, const char * argv[]) {
    ifstream fin ("job.in");
    ofstream fout ("job.out");
    int N, M1, M2;
    fin >> N >> M1 >> M2;
    vector<int> A(M1, 0);
    vector<int> B(M2, 0);
    for (int i = 0; i < M1; i++) {
        fin >> A[i];
    }
    for (int i = 0; i < M2; i++) {
        fin >> B[i];
    }
    priority_queue<pair<int, int>, vector<pair<int, int> >, cmp> pq;
    for (int i = 0; i < M1; i++) {
        pq.push(make_pair(0, A[i]));
    }
    vector<int> jobs(N, 0);
    int ans1 = 0;
    for (int i = 0; i < N; i++) {
        pair<int, int> cur = pq.top();
        pq.pop();
        jobs[i] = cur.first + cur.second;
        ans1 = max(ans1, jobs[i]);
        cur.first += cur.second;
        pq.push(cur);
    }
    while (!pq.empty()) pq.pop();
    for (int i = 0; i < M2; i++) {
        pq.push(make_pair(0, B[i]));
    }
    int ans2 = 0;
    for (int i = N - 1; i >= 0; i--) {
        pair<int, int> cur = pq.top();
        pq.pop();
        jobs[i] += cur.first + cur.second;
        ans2 = max(ans2, jobs[i]);
        cur.first += cur.second;
        pq.push(cur);
    }
    fout << ans1 << " " << ans2 << endl;
    return 0;
}
