/*
 ID: cloudzf2
 PROG: shopping
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

struct offer {
    vector<pair<int, int> > items;
    int price;
};

int dp[6][6][6][6][6];

void initialize(vector<int> &prices, vector<int> &required) {
    vector<int> idx(5, 0);
    for (idx[0] = 0; idx[0] <= required[0]; idx[0]++) {
        for (idx[1] = 0; idx[1] <= required[1]; idx[1]++) {
            for (idx[2] = 0; idx[2] <= required[2]; idx[2]++) {
                for (idx[3] = 0; idx[3] <= required[3]; idx[3]++) {
                    for (idx[4] = 0; idx[4] <= required[4]; idx[4]++) {
                        dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]] = idx[0] * prices[0] + idx[1] * prices[1] + idx[2] * prices[2] + idx[3] * prices[3] + idx[4] * prices[4];
                    }
                }
            }
        }
    }
}

void solve(offer cur, vector<int> &required) {
    vector<int> idx(5, 0);
    vector<int> pre(5, 0);
    for (idx[0] = 0; idx[0] <= required[0]; idx[0]++) {
        for (idx[1] = 0; idx[1] <= required[1]; idx[1]++) {
            for (idx[2] = 0; idx[2] <= required[2]; idx[2]++) {
                for (idx[3] = 0; idx[3] <= required[3]; idx[3]++) {
                    for (idx[4] = 0; idx[4] <= required[4]; idx[4]++) {
                        pre = idx;
                        bool isValid = true;
                        for (int i = 0; i < cur.items.size(); i++) {
                            if (pre[cur.items[i].first] < cur.items[i].second) {
                                isValid = false;
                                break;
                            }
                            pre[cur.items[i].first] -= cur.items[i].second;
                        }
                        if (!isValid) continue;
                        dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]] = min(dp[idx[0]][idx[1]][idx[2]][idx[3]][idx[4]], cur.price + dp[pre[0]][pre[1]][pre[2]][pre[3]][pre[4]]);
                    }
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    ifstream fin ("shopping.in");
    ofstream fout ("shopping.out");
    int s, n, c, k, b, p;
    vector<offer> offers;
    unordered_map<int, int> codes;
    fin >> s;
    for (int i = 0; i < s; i++) {
        fin >> n;
        offer o;
        for (int i = 0; i < n; i++) {
            fin >> c >> k;
            o.items.push_back(make_pair(c, k));
        }
        fin >> o.price;
        offers.push_back(o);
    }
    fin >> b;
    vector<int> required(5, 0);
    vector<int> prices(5, 0);
    int count = 0;
    for (int i = 0; i < b; i++) {
        fin >> c >> k >> p;
        if (codes.find(c) == codes.end()) {
            codes[c] = count++;
        }
        required[codes[c]] = k;
        prices[codes[c]] = p;
    }
    memset(dp, 0, sizeof(dp));
    initialize(prices, required);
    for (int i = 0; i < s; i++) {
        bool isValid = true;
        for (int j = 0; j < offers[i].items.size(); j++) {
            if (codes.find(offers[i].items[j].first) == codes.end()) {
                isValid = false;
                break;
            } else {
                offers[i].items[j].first = codes[offers[i].items[j].first];
            }
        }
        if (!isValid) continue;
        solve(offers[i], required);
    }
    fout << dp[required[0]][required[1]][required[2]][required[3]][required[4]] << endl;
    return 0;
}
