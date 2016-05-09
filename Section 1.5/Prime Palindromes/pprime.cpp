/*
 ID: cloudzf2
 PROG: pprime
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

void listPrimes(vector<int> &primes) {
    vector<bool> isPrime(10001, true);
    for (int i = 2; i <= 10000; i++) {
        if (isPrime[i]) {
            for (int j = 2; i * j <= 10000; j++) {
                isPrime[i * j] = false;
            }
        }
    }
    for (int i = 2; i <= 10000; i++) {
        if (isPrime[i]) primes.push_back(i);
    }
}

int getNum(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num *= 10;
        num += s[i] - '0';
    }
    return num;
}

bool checkPrime(vector<int> &primes, int num) {
    for (int i = 0; i < primes.size() && primes[i] * primes[i] <= num; i++) {
        if (num % primes[i] == 0) return false;
    }
    return true;
}

void dfs(string myans, int n, vector<int> &primes, vector<int> &ans) {
    if (n == 0) {
        int num = getNum(myans);
        if (checkPrime(primes, num)) {
            ans.push_back(num);
        }
    } else if (n % 2 == 1) {
        for (int i = 0; i <= 9; i++) {
            if (n == 1 && i % 2 == 0) continue;
            char tmp = '0' + i;
            dfs(myans + tmp, n - 1, primes, ans);
        }
    } else {
        for (int i = 0; i <= 9; i++) {
            if (n == 2 && i % 2 == 0) continue;
            char tmp = '0' + i;
            dfs(tmp + myans + tmp, n - 2, primes, ans);
        }
    }
}
int main(int argc, const char * argv[]) {
    ifstream fin ("pprime.in");
    ofstream fout ("pprime.out");
    int A, B;
    fin >> A >> B;
    vector<int> primes;
    listPrimes(primes);
    vector<int> ans;
    for (int i = 1; i <= 8; i++) {
        dfs("", i, primes, ans);
    }
    sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i] >= A && ans[i] <= B) fout << ans[i] << endl;
    }
    return 0;
}
