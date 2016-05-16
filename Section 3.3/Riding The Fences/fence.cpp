/*
 ID: cloudzf2
 PROG: fence
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

int main(int argc, const char * argv[]) {
    ifstream fin ("fence.in");
    ofstream fout ("fence.out");
    int F, a, b;
    int N = 500;
    fin >> F;
    vector<multiset<int> > graph(N, multiset<int>());
    vector<int> degree(N, 0);
    for (int i = 0; i < F; i++) {
        fin >> a >> b;
        graph[a - 1].insert(b - 1);
        graph[b - 1].insert(a - 1);
        degree[a - 1]++;
        degree[b - 1]++;
    }
    int cur = -1;
    for (int i = 0; i < N; i++) {
        if (degree[i] % 2 == 1) {
            cur = i;
            break;
        }
    }
    if (cur == -1) {
        for (int i = 0; i < N; i++) {
            if (degree[i] != 0) {
                cur = i;
                break;
            }
        }
    }
    stack<int> s;
    vector<int> ans;
    s.push(cur);
    while (!s.empty()) {
        cur = s.top();
        if (graph[cur].size() == 0) {
            ans.push_back(cur);
            s.pop();
        } else {
            set<int>::iterator it = graph[cur].begin();
            int next = *it;
            graph[cur].erase(it);
            graph[next].erase(graph[next].find(cur));
            s.push(next);
        }
    }
    for (int i = (int)ans.size() - 1; i >= 0; i--) {
        fout << ans[i] + 1 << endl;
    }
    return 0;
}
