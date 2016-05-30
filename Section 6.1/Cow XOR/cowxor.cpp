/*
 ID: cloudzf2
 PROG: cowxor
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

struct trie {
    int idx;
    trie* next[2];
    trie() {
        idx = 0;
        memset(next, 0, sizeof(next));
    }
};

void add(trie *root, int idx, int num, int depth) {
    if (depth == 21) {
        root->idx = idx;
        return;
    }
    if ((1 << (20 - depth)) & num) {
        if (root->next[1] == NULL) root->next[1] = new trie();
        add(root->next[1], idx, num, depth + 1);
    }
    else {
        if (root->next[0] == NULL) root->next[0] = new trie();
        add(root->next[0], idx, num, depth + 1);
    }
}

void query(trie *root, int &idx, int &num, int depth) {
    if (depth == 21) {
        idx = root->idx;
        return;
    }
    if ((1 << (20 - depth)) & num) {
        if (root->next[1] == NULL) {
            num -= 1 << (20 - depth);
            query(root->next[0], idx, num, depth + 1);
        } else {
            query(root->next[1], idx, num, depth + 1);
        }
    } else {
        if (root->next[0] == NULL) {
            num += 1 << (20 - depth);
            query(root->next[1], idx, num, depth + 1);
        } else {
            query(root->next[0], idx, num, depth + 1);
        }
    }
}
int main(int argc, const char * argv[]) {
    ifstream fin ("cowxor.in");
    ofstream fout ("cowxor.out");
    int N;
    fin >> N;
    vector<int> data(N, 0);
    for (int i = 0; i < N; i++) {
        fin >> data[i];
    }
    vector<int> m(N + 1, 0);
    for (int i = 0; i < N; i++) {
        m[i + 1] = data[i] ^ m[i];
    }
    trie *root = new trie();
    add(root, 0, 0, 0);
    int ans = -1, a = 0, b = 0;
    for (int i = 1; i <= N; i++) {
        int num = ((1 << 21) - 1) ^ m[i];
        int idx = 0;
        query(root, idx, num, 0);
        if ((m[i] ^ num) > ans) {
            a = idx == 0 ? i : idx + 1;
            b = i;
            ans = m[i] ^ num;
        }
        add(root, i, m[i], 0);
    }
    fout << ans << " " << a << " " << b << endl;
    return 0;
}
