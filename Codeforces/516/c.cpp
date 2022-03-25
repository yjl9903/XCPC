#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 100000 + 5;

int n, cnt[30]; char s[maxn], ans[maxn];
vector<PII> v;

int main(){
    scanf("%d%s", &n, s);
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    for (int i = 0; i < 26; i++){
        while (cnt[i]--){
            putchar(i + 'a');
        }
    }
    return 0;
}