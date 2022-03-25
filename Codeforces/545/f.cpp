#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

string query(vector<int> v) {
    cout << "next";
    for (int& x: v) cout << ' ' << x;
    cout << endl;
    string s; getline(cin, s);
    return s;
}

int main() {
    while (true) {
        query({0, 1});
        string s = query({1});
        if (s.find("01") != string::npos) break;
    }
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    while (true) {
        string s = query(v);
        if (s.find("0123456789") != string::npos) break;
    }
    cout << "done" << endl;
    return 0;
}