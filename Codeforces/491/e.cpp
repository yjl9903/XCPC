#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 20 + 5;

ll n, f[maxn], res = 0;
int cnt[10];
vector<int> v;

void dfs(int c){
    if (v.size() == 10){
        int s = 0;
        for (int i = 0; i < 10; i++)
            s += v[i];
        ll t = f[s];
        for (int i = 0; i < 10; i++)
            t /= f[v[i]];
        res += t;
        return;
    }
    if (cnt[v.size()] == 0){
        v.push_back(0);
        dfs(c);
        v.pop_back();
        return;
    }
    int sta = 1;
    if (v.size() == c)
        sta = 0;
    for (int i = sta; i <= cnt[v.size()]; i++){
        v.push_back(i);
        dfs(c);
        v.pop_back();
    }
}

int main(){
    cin >> n;
    f[0] = f[1] = 1;
    for (int i = 2; i < 21; i++){
        f[i] = f[i - 1] * i;
    }
    while (n){
        cnt[n % 10]++;
        n /= 10;
    }
    for (int i = 1; i <= 9; i++){
        if (!cnt[i])
            continue;
        cnt[i]--;
        dfs(i);
        cnt[i]++;
    }
    cout << res;
    return 0;
}