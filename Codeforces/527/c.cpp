#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200 + 5;

struct node {
    string s;
    int id;
    bool operator<(const node& b) const {
        return s.length() < b.s.length();
    }
}s[maxn];

int n;
char ans[maxn];

int getans(string p) {
    for (int i = 1; i <= 2 * n - 2; i += 2) {
        if (s[i].s == p.substr(0, i / 2 + 1) && s[i + 1].s == p.substr(p.length() - i / 2 - 1, i / 2 + 1)) {
            ans[s[i].id] = 'P'; ans[s[i + 1].id] = 'S';
        }
        else if (s[i + 1].s == p.substr(0, i / 2 + 1) && s[i].s == p.substr(p.length() - i / 2 - 1, i / 2 + 1)) {
            ans[s[i].id] = 'S'; ans[s[i + 1].id] = 'P';
        } else return 0;
    }
    return 1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for (int i = 1; i <= 2 * n - 2; i++) cin >> s[i].s, s[i].id = i;
    if (n == 2) return puts("PS"), 0;
    sort(s + 1, s + 2 * n - 1);
    if (getans(s[1].s + s[2 * n - 3].s));
    else if (getans(s[1].s + s[2 * n - 2].s));
    else if (getans(s[2].s + s[2 * n - 3].s));
    else getans(s[2].s + s[2 * n - 2].s);
    cout << ans + 1;
    return 0;
}