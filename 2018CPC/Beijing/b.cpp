#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#ifdef XLor
  #define dbg(args...) do {cout << "debug -> "; err(args);} while (0)
#else
  #define dbg(...)
#endif
void err() {std::cout << std::endl;}
template<typename T, typename...Args>
void err(T a, Args...args){std::cout << a << ' '; err(args...);}
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n, len[15], vis[30];
char ss[15][30], tmp[15];
string ans;

bool check(int k, int l){
    int tot = 0;
    for (int i = 0; i < len[k]; i++){
        tot = 0;
        for (int j = i; j < i + len[k]; j++){
            if (ss[k][j % len[k]] == tmp[tot]){
                tot++;
                if (tot == l) return true;
            }
        }
    }
    return false;
}

string get(string s){
    string tmp; vector<string> v; 
    for (int i = 0; i < s.length(); i++){
        tmp.clear();
        for (int j = i; j < i + s.length(); j++) tmp.push_back(s[j % s.length()]);
        v.push_back(tmp);
    }
    sort(v.begin(), v.end());
    return v[0];
}

int main(){
    while (~scanf("%d", &n)){
        int ml = 0, p = -1;
        for (int i = 0; i < n; i++){
            scanf("%s", ss[i]); len[i] = strlen(ss[i]);
            if (len[i] > ml) ml = len[i], p = i;
            // for (int j = 0; j < len[i]; j++) ss[i][j + len[i]] = ss[i][j];
        }
        int maxs = 1 << len[p], res = -1;
        for (int s = 1; s < maxs; s++){
            int t = 0; ms(tmp, 0);
            for (int i = 0; i < ml; i++){
                if ((1 << i) & s) tmp[t++] = ss[p][i]; 
            }
            // dbg(tmp);
            int flag = 0;
            for (int i = 0; i < n; i++){
                if (i == p) continue;
                if (!check(i, t)) {
                    flag = 1; break;
                }
            }
            if (flag) continue;
            if (t >= res){
                string tt = get(string(tmp));
                if (t > res) ans = tt;
                else if (tt < ans) ans = tt;
                res = t;
            }
        }
        if (res == -1) puts("0");
        else cout << ans << '\n';
    }
    return 0;
}