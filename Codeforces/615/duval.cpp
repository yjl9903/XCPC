#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = (1 << 20) + 5;

char s[maxn];

void duval(char s[], int n) {
    for (int i = 1, j, k; i <= n; ) {
        j = i; k = i + 1;
        while (k <= n && s[j] <= s[k]) {
            if (s[j] < s[k]) {
                j = i;
            } else {
                j++;
            }
            k++;
        }
        while (i <= j) {
            printf("%d ", i + k - j - 1);
            i += k - j;
        }
    }
}

int main() {
    scanf("%s", s + 1);
    duval(s, strlen(s + 1));
    return 0;
}