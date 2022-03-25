#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];
int vis[maxn];

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin.getline(s, 1000)){
        int len = strlen(s);
        ms(vis, 0);
        for (int i = 2; i < len; i++) 
            if (s[i - 2] == 'y' && s[i - 1] == 'o' && s[i] == 'u')
                vis[i - 2] = 1;
        for (int i = 0; i < len; i++){
            if (vis[i]) printf("we"), i += 2;
            else printf("%c", s[i]);
        }
        puts("");
    }
    return 0;
}