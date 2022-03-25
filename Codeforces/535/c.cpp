#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 200000 + 5;

int n; char s[maxn], t[maxn];
char p[5] = "BGR";

int main(){
    scanf("%d%s", &n, s);
    int mn = 1e9;
    do {
        int cnt = 0;
        for (int i = 0; i < n; i++) if (s[i] != p[i % 3]) cnt++;
        if (cnt < mn) {
            mn = cnt;
            for (int i = 0; i < n; i++) t[i] = p[i % 3];
        }
    } while (next_permutation(p, p + 3));
    printf("%d\n%s", mn, t);
    return 0;
}