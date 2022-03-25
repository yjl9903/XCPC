#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int maxn = 100000 + 5;

char s[200];
char v1[maxn][105], v2[maxn][105];
int t1, t2;
unordered_map<ull,int> mp1, mp2;

ull Hash(string s){
    const int seed = 131;
    const int p1 = 1e9 + 7;
    ull ans = 0;
    for (int i = 0; i < s.length(); i++){
        ans = (ans * seed + s[i]) % p1;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin.getline(s, 150)){
        string str(s); if (s[0] == '@') break;
        for (int i = 0; i < str.length(); i++){
            if (str[i] == ']'){
                mp1[Hash(str.substr(0, i + 1))] = t1;
                memcpy(v1[t1++], str.substr(1, i - 1).c_str(), 100);
                mp2[Hash(str.substr(i + 2, str.length() - i - 2))] = t2;
                memcpy(v2[t2++], str.substr(i + 2, str.length() - i - 2).c_str(), 100);
                break;
            }
        }
    }
    int T; cin >> T; cin.ignore();
    while (T--){
        cin.getline(s, 100);
        string str(s);
        if (s[0] == '['){
            // str = str.substr(1, str.length() - 2);
            ull x = Hash(str);
            if (mp1.count(x)){
                printf("%s\n", v2[mp1[x]]);
            }
            else puts("what?");
        }
        else {
            ull x = Hash(str);
            if (mp2.count(x)){
                printf("%s\n", v1[mp2[x]]);
            }
            else puts("what?");
        }
    }
    return 0;
}