#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000000 + 5;

int n; char s[maxn], t[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%s%s", &n, s, t);
        vector<int> v; int cnt = 0, s1 = 0, s2 = 0;
        for (int i = 0; i < n; i++){
            if (s[i] == t[i]){
                cnt++; s1++;
            }
            else {
                if (cnt) v.push_back(cnt);
                cnt = 0; s2++;
            }
        }
        if (cnt) v.push_back(cnt);
        if (v.size() == 0) printf("%d\n", 2 * s2 - 2);
        else if (v.size() == 1){
            if (s[0] != t[0] && s[n - 1] != t[n - 1]) puts("6");
            else if (s[0] != t[0] || s[n - 1] != t[n - 1]) printf("%d\n", 2 * s2 + 2 * s1 - 2);
            else printf("%lld\n", 1ll * s1 * (s1 + 1) / 2);
        }
        else if (v.size() == 2){
            if (s[0] != t[0] && s[n - 1] != t[n - 1]) puts("0");
            else if (s[0] != t[0] || s[n - 1] != t[n - 1]) puts("6");
            else printf("%d\n", 2 * s1 + 2 * s2 - 2);
        }
        else if (v.size() == 3){
            if (s[0] == t[0] && s[n - 1] == t[n - 1]) puts("6");
            else puts("0");
        }
        else puts("0");
    }
    return 0;
}