#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10000 + 5;

char s[maxn];

int getmin(char* s){
    int n = strlen(s), i = 0, j = 1, k = 0;
    while (i < n && j < n && k < n){
        int t = s[(i + k) % n] - s[(j + k) % n];
        if (!t) k++;
        else {
            if (t > 0) i += k + 1;
            else j += k + 1;
            if (i == j) j++;
            k = 0;
        }
    }
    return min(i, j) + 1;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        printf("%d\n", getmin(s));
    }
    return 0;
}