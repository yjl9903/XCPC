#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int maxn = 100000 + 5;

char s[maxn], t[maxn], tmp[maxn];
int n;

int main() {
    scanf("%s%s", s, t);
    n = strlen(s);
    int g = 1;
    for (int i = n - 1; i >= 0; i--) {
        tmp[i] = s[i] + g;
        if (tmp[i] > 'z') tmp[i] -= 26, g = 1;
        else g = 0;
    }
    // cout << tmp << endl;
    if (string(tmp) == string(t)) return puts("No such string"), 0;

    int a = n, b = n;
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == 'z') a = i;
        else break;
    }
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == 'a') b = i;
        else break;
    }

    for (int i = 0; i < n; i++){
        if (s[i] < t[i]){
            if (a == i + 1) {
                putchar(s[i++] + 1);
                while (i < n) i++, putchar('a');
            }
            else {
                putchar(s[i++]);
                while (i < n) i++, putchar('z');
            }
            return 0;
        }
        else putchar(s[i]);
    }

    return 0;
}