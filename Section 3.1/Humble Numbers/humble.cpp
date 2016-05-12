/*
 ID: cloudzf2
 PROG: humble
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

using namespace std;

struct node {
    int value, prime, index;
    node(int value, int prime, int index) : value(value), prime(prime), index(index) {}
};

struct cmp {
    bool operator()(const node &a, const node &b) {
        return a.value > b.value;
    }
};

int main(int argc, const char * argv[]) {
    ifstream fin ("humble.in");
    ofstream fout ("humble.out");
    int K, N, s;
    fin >> K >> N;
    priority_queue<node, vector<node>, cmp> primes;
    for (int i = 0; i < K; i++) {
        fin >> s;
        primes.push(node(s, s, 0));
    }
    vector<int> dp;
    int count = 0;
    while (count < N) {
        node cur = primes.top();
        primes.pop();
        if (count == 0 || dp[count - 1] < cur.value) {
            dp.push_back(cur.value);
            count++;
        }
        cur.value = cur.prime * dp[cur.index];
        cur.index++;
        primes.push(cur);
    }
    fout << dp[N - 1] << endl;
    return 0;
}
