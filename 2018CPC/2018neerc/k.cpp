#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, k, a[maxn], s; vector<int> ans;

int main(){
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++) scanf("%d", a + i), s += a[i];
    if (s % k) return puts("No"), 0;
    int l = s / k, tot = 0, last = 0;
    for (int i = 0; i < n; i++){
        tot += a[i];
        if (tot > l) return puts("No"), 0;
        else if (tot == l){
            ans.push_back(i - last + 1);
            tot = 0; last = i + 1;
        }
    }
    if (ans.size() != k) return puts("No"), 0;
    int m = 0;
    for (int i = 0; i < ans.size(); i++) m += ans[i];
    if (m != n) return puts("No"), 0;

    puts("Yes");
    for (int i = 0; i < ans.size(); i++){
        if (i) putchar(' ');
        printf("%d", ans[i]);
    }
    return 0;
}