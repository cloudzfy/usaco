/*
 ID: cloudzf2
 PROG: namenum
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

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream fin ("namenum.in");
    ofstream fout ("namenum.out");
    ifstream dict ("dict.txt");
    unordered_map<string, vector<string>> m;
    string name;
    while (dict >> name) {
        bool isValid = true;
        string num = name;
        for (int i = 0; i < name.length(); i++) {
            if (name[i] == 'Q' || name[i] == 'Z') {
                isValid = false;
                break;
            } else if (name[i] < 'Q') {
                num[i] = '2' + (name[i] - 'A') / 3;
            } else {
                num[i] = '7' + (name[i] - 'Q') / 3;
            }
        }
        if (isValid) {
            m[num].push_back(name);
        }
    }
    string num;
    fin >> num;
    if (m.find(num) != m.end()) {
        vector<string> names = m[num];
        sort(names.begin(), names.end());
        for (int i = 0; i < names.size(); i++) {
            fout << names[i] << endl;
        }
    } else {
        fout << "NONE" << endl;
    }
    return 0;
}
