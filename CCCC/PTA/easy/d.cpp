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
const int maxn = 100000 + 5;

int k;
char s[30]; 

int main() {
    scanf("%d", &k);
    int cnt = 0;
    while (scanf("%s", s) == 1) {
        if (s[0] == 'E') break;
        if (k == cnt) {
            puts(s);
            cnt = -1;
        } else {
            if (s[0] == 'C') puts("Bu");
            if (s[0] == 'J') puts("ChuiZi");
            if (s[0] == 'B') puts("JianDao");
        }
        cnt++;
    }
    return 0;
}