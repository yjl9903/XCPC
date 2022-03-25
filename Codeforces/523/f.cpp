#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int rand(){
    static int seed = 233;
    return seed = int(seed * 482711ll % 2147483647);
}
int n, k;

bool ask(int a, int c, int b){
    cout << "? " << a << ' ' << b << ' ' << c << endl;
    char s[10]; cin >> s;
    return s[0] == 'Y';
}

vector<int> get(int x, int y){
    int l = x, r = y;
    for (int i = 1; i <= n; i++){
        if (i == x || i == y) continue;
        if (ask(l, r, i) == false){
            if (ask(i, r, l)) l = i;
            else if (ask(l, i, r)) r = i;
        }
    }
    vector<int> v; v.push_back(l); v.push_back(r);
    for (int i = 1; i <= n; i++){
        if (i == l || i == r) continue;
        if (ask(l, r, i)) v.push_back(i);
    }
    return v;
}

int main(){
    cin >> n >> k;
    int dep = 0;
    for (int i = 1, t = k; i <= n; i++, t *= k){
        if (n == (t - 1) / (k - 1)) {
            dep = i; break;
        }
    }
    vector<int> ans;
    // cout << dep << endl;
    while (1){
        int x = rand() % n + 1, y = rand() % n + 1;
        while (x == y) x = rand() % n + 1, y = rand() % n + 1;
        ans = get(x, y);
        if (ans.size() == 2 * dep - 1) break;
    }
    // cout << "ha" << endl;
    for (int i = 2; i < ans.size(); i++){
        int c = 0;
        for (int j = 2; j < ans.size(); j++){
            if (i == j) continue;
            if (ask(ans[0], ans[i], ans[j])) c++;
        }
        if (c == dep - 2) return cout << "! " << ans[i] << endl, 0;
    }
    return 0;
}