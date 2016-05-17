/*
 ID: cloudzf2
 PROG: heritage
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

string makeTree(string inorder, string preorder) {
    if (inorder.length() <= 1) return inorder;
    string postorder;
    int len = (int)inorder.find(preorder[0]);
    postorder += makeTree(inorder.substr(0, len), preorder.substr(1, len));
    postorder += makeTree(inorder.substr(len + 1), preorder.substr(len + 1));
    postorder += preorder[0];
    return postorder;
}

int main(int argc, const char * argv[]) {
    ifstream fin ("heritage.in");
    ofstream fout ("heritage.out");
    string inorder, preorder;
    fin >> inorder >> preorder;
    fout << makeTree(inorder, preorder) << endl;
    return 0;
}
