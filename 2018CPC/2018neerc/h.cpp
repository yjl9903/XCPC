#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;
const int seed = 40;

int n, q; char st[maxn][10];
unordered_map<ll,int> mp, gid;

int get(char ch){
    if (ch >= 'a' && ch <= 'z') return ch - 'a' + 1;
    if (ch >= '0' && ch <= '9') return ch - '0' + 27;
    return 37;
}
ll Hash(string s){
    ll ans = 0; 
    for (char& x : s){
        ans = ans * seed + get(x);
    }
    return ans;
}
void init(string s, int id){
    unordered_map<ll,int> tmp;
    for (int i = 0; i < s.size(); i++){
        ll ans = 0;
        for (int j = i; j < s.size(); j++){
            ans = ans * seed + get(s[j]);
            tmp[ans]++; 
        }
    }
    for (auto& x : tmp){
        mp[x.first]++;
        gid[x.first] = id;
    }
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%s", st[i]); 
        init(st[i], i);
    }
    scanf("%d", &q); char s[10];
    while (q--){
        scanf("%s", s); ll h = Hash(s);
        // cout << h << endl;
        if (mp.count(h)){
            printf("%d %s\n", mp[h], st[gid[h]]);
        }
        else puts("0 -");
    }
    return 0;
}