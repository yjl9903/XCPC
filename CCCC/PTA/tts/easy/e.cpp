#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n; char ch[2], s[maxn];

int main() {
    cin >> n >> ch; cin.ignore();
    cin.getline(s, maxn - 1);
    int len = strlen(s);
    if (len >= n) {
        for (int i = len - n; i < len; i++) putchar(s[i]);
    } else {
        for (int i = 0; i < n - len; i++) putchar(ch[0]);
        puts(s);
    }
    return 0;
}