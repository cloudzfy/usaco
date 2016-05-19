/*
 ID: cloudzf2
 PROG: lgame
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

int alphabets[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};

int calValue(string s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        num += alphabets[s[i] - 'a'];
    }
    return num;
}

void generateWords(string s, set<string> &words) {
    int len = (int)s.length();
    for (int i = 1; i < (1 << len); i++) {
        string word;
        int tmp = i, j = 0;
        while (tmp) {
            if (tmp & 1) word.push_back(s[j]);
            j++;
            tmp >>= 1;
        }
        words.insert(word);
    }
}

bool checkValidation(vector<int> &count, string s) {
    vector<int> scount(26, 0);
    for (int i = 0; i < s.length(); i++) {
        scount[s[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (scount[i] > count[i]) return false;
    }
    return true;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("lgame.in");
    ofstream fout ("lgame.out");
    ifstream dict ("lgame.dict");
    string s;
    fin >> s;
    sort(s.begin(), s.end());
    int num = 0;
    vector<int> count(26, 0);
    for (int i = 0; i < s.length(); i++) {
        count[s[i] - 'a']++;
    }
    unordered_map<string, vector<string> > m;
    string word;
    while (true) {
        dict >> word;
        if (word == ".") break;
        bool isValid = true;
        for (int i = 0; i < word.length(); i++) {
            if (count[word[i] - 'a'] == 0) {
                isValid = false;
                break;
            }
        }
        if (!isValid) continue;
        string tmp = word;
        sort(tmp.begin(), tmp.end());
        m[tmp].push_back(word);
    }
    vector<string> ans;
    set<string> words;
    generateWords(s, words);
    map<int, vector<pair<string, string> > > wordList;
    for (auto it = words.begin(); it != words.end(); it++) {
        wordList[calValue(*it)].push_back(make_pair(*it, ""));
    }
    for (auto it = words.begin(); it != words.end(); it++) {
        auto jt = it;
        jt++;
        for (; jt != words.end(); jt++) {
            if (!checkValidation(count, *it + *jt)) continue;
            wordList[calValue(*it + *jt)].push_back(make_pair(*it, *jt));
        }
    }
    for (auto t = wordList.rbegin(); t != wordList.rend(); t++) {
        num = t->first;
        vector<pair<string, string> > cur = t->second;
        for (int i = 0; i < cur.size(); i++) {
            if (cur[i].second == "") {
                vector<string> a = m[cur[i].first];
                for (int j = 0; j < a.size(); j++) {
                    ans.push_back(a[j]);
                }
            } else {
                vector<string> a = m[cur[i].first];
                vector<string> b = m[cur[i].second];
                for (int j = 0; j < a.size(); j++) {
                    for (int k = 0; k < b.size(); k++) {
                        string aa = a[j];
                        string bb = b[k];
                        if (aa > bb) swap(aa, bb);
                        ans.push_back(aa + " " + bb);
                    }
                }
            }
        }
        if (ans.size() > 0) break;
    }
    sort(ans.begin(), ans.end());
    fout << num << endl;
    for (int i = 0; i < ans.size(); i++) {
        fout << ans[i] << endl;
    }
    return 0;
}
