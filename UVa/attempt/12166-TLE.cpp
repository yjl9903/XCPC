#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

int val[maxn], leaf[maxn], cnt = 0, height = 0;

int dfs(int p){
    if (leaf[p])    return 0;
    return max(dfs(2 * p), dfs(2 * p + 1)) + 1;
}

int change(int p, ll v){
    // cout << p << endl;
    if(leaf[p]) return val[p] != v;
    return change(2 * p, v / 2) + change(2 * p + 1, v / 2);
}

int solve(){
    int res = 1 << 30;
    if (height == 0)    return 0;
    if (height == 1)    return val[2] != val[3];
    for (int i = (1 << height); i < (1 << (height + 1)); i++){
        if (leaf[i]){
            int t = 0, tot = i;
            ll w = val[i];
            while (tot > 1){
                if (tot % 2){
                    t += change(tot - 1, w);
                }
                else{
                    t += change(tot + 1, w);
                }
                // cout << '-' << endl;
                w <<= 1;
                tot >>= 1;
            }
            res = min(res, t);
        }
    }
    return res;
}

int main(){
    int T; cin >> T;
    while (T--){
        memset(val, 0, sizeof val); memset(leaf, 0, sizeof leaf);
        string x; cin >> x;
        int tot = 1; cnt = 0;   height = 0;
        for (int i = 0; i < x.length(); i++){
            if (x[i] == '['){
                tot *= 2;
            }
            else if (x[i] == ']'){
                tot /= 2;
            }
            else if (x[i] == ','){
                tot++;
            }
            else if (x[i] >= '0' && x[i] <= '9'){
                int t = 0;
                while (x[i] >= '0' && x[i] <= '9'){
                    t = t * 10 + x[i++] - '0';
                }
                i--;
                val[tot] = t;   cnt++;  leaf[tot] = 1;
            }
        }
        height = dfs(1);
        cout << solve() << endl;
    }
    return 0;
}