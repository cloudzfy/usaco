/*
 ID: cloudzf2
 PROG: milk3
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

struct buckets {
    int A, B, C;
    buckets(int A, int B, int C) : A(A), B(B), C(C) {}
    bool operator==(const buckets &x) const {
        return A == x.A && B == x.B && C == x.C;
    }
};

struct NodeHash {
    size_t operator () (const buckets &x) const {
        return x.A * 441 + x.B * 21 + x.C;
    }
};

int main(int argc, const char * argv[]) {
    ifstream fin ("milk3.in");
    ofstream fout ("milk3.out");
    int A, B, C;
    fin >> A >> B >> C;
    set<int> ans;
    queue<buckets> q;
    unordered_set<buckets, NodeHash> m;
    q.push(buckets(0, 0, C));
    m.insert(buckets(0, 0, C));
    while (!q.empty()) {
        buckets cur = q.front();
        q.pop();
        if (cur.A == 0) ans.insert(cur.C);
        if (cur.A != A) {
            if (cur.B != 0) {
                buckets tmp = cur;
                tmp.A += min(cur.B, A - cur.A);
                tmp.B -= min(cur.B, A - cur.A);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
            if (cur.C != 0) {
                buckets tmp = cur;
                tmp.A += min(cur.C, A - cur.A);
                tmp.C -= min(cur.C, A - cur.A);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
        }
        if (cur.B != B) {
            if (cur.A != 0) {
                buckets tmp = cur;
                tmp.B += min(cur.A, B - cur.B);
                tmp.A -= min(cur.A, B - cur.B);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
            if (cur.C != 0) {
                buckets tmp = cur;
                tmp.B += min(cur.C, B - cur.B);
                tmp.C -= min(cur.C, B - cur.B);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
        }
        if (cur.C != C) {
            if (cur.A != 0) {
                buckets tmp = cur;
                tmp.C += min(cur.A, C - cur.C);
                tmp.A -= min(cur.A, C - cur.C);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
            if (cur.B != 0) {
                buckets tmp = cur;
                tmp.C += min(cur.B, C - cur.C);
                tmp.B -= min(cur.B, C - cur.C);
                if (m.find(tmp) == m.end()) {
                    q.push(tmp);
                    m.insert(tmp);
                }
            }
        }
    }
    int count = 0;
    for (auto it = ans.begin(); it != ans.end(); it++) {
        if (count != 0) fout << " ";
        fout << *it;
        count++;
    }
    fout << endl;
    return 0;
}
