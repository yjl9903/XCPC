#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 11000000 + 5;

char a[maxn];

namespace manacher{
    char s[maxn << 1] = "##";
    int n, hw[maxn << 1];
    void init(){
        int len = strlen(a);
        for (int i = 0; i < len; i++){
            s[i * 2 + 2] = a[i];
            s[i * 2 + 3] = '#';
        }
        n = len * 2 + 2; s[n] = 0;
    }
    void manacher(){
        int maxr = 0, m = 0;
        for (int i = 1; i < n; i++){
            if (i < maxr) hw[i] = min(hw[m * 2 - i], hw[m] + m - i);
            else hw[i] = 1;
            while (s[i + hw[i]] == s[i - hw[i]]) hw[i]++;
            if (hw[i] + i > maxr){
                m = i; maxr = hw[i] + i;
            }
        }
    }
    int getMax(){
        init(); manacher(); int ans = 1;
        for (int i = 0; i < n; i++) ans = max(ans, hw[i]);
        return ans - 1;
    }
}

int main(){
    scanf("%s", a);
    printf("%d", manacher::getMax());
    return 0;
}