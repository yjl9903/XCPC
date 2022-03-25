#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn]; int n;

bool check(string s){
    if (s.empty()) return 1;
    if (s == "0") return 0;
    if (s[0] < '1' || s[0] > '9') return 1;
    for (int i = 1; i < s.length(); i++) if (s[i] < '0' || s[i] > '9') return 1;
    return 0;
}

int main(){
    scanf("%s", s); n = strlen(s);
    vector<string> v[2];
    string tmp("");
    for (int i = 0; i < n; i++){
        if (s[i] == ',' || s[i] == ';') {
            v[check(tmp)].push_back(tmp);
            tmp = ""; continue;
        }
        tmp.push_back(s[i]);
    }
    v[check(tmp)].push_back(tmp);
    if (v[0].empty()) cout << '-' << endl;
    else {
        cout << '"';
        for (int i = 0; i < v[0].size(); i++){
            if (i) cout << ',';
            cout << v[0][i];
        }
        cout << '"' << endl;
    }
    if (v[1].empty()) cout << '-' << endl;
    else {
        cout << '"';
        for (int i = 0; i < v[1].size(); i++){
            if (i) cout << ',';
            cout << v[1][i];
        }
        cout << '"' << endl;
    }
    return 0;
}