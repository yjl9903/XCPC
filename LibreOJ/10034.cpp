#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 998244353;
const int maxn = 100000 + 5;

string s;
unordered_set<string> mp;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while (T--) {
        string tmp; cin >> tmp >> s;
        if (tmp[0] == 'a') {
            // mp.insert(s.substr(4));
            mp.insert(s);
        } else if (tmp[0] == 'f') {
            // if (mp.count(s.substr(5))) puts("yes");
            if (mp.count(s)) puts("yes");
            else puts("no");
        }
    }
    return 0;
}