#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

int n, hd; char s[maxn];

void sub(int i, int x){
    if (s[i] - '0' < x){
        s[i] = s[i] + 10 - x;
        i--;
        while(i >= hd && s[i] == '0') s[i--] = '9';
        if (i >= hd) s[i]--;
        if (i == hd && i < n - 1 && s[i] == '0') hd++;
    }
    else{
        s[i] -= x;
    }
}
bool check(int i){ // s <= 90000 : true
    if (i > hd) return true;
    if (s[i] < '9') return false;
    while (i < n && s[i] == '0') i++;
    return i == n;
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s); n = strlen(s); hd = 0;
        // sub(n - 1, 8); cout << s + hd << endl;
        if (n == 1){
            printf("%c\n", s[0] - 1); continue;
        }
        if (n == 2 && s[0] == '1'){
            if (s[1] == '0') printf("9\n");
            else printf("%c%c\n", s[1], s[1]);
            continue;
        }
        sub(n - 1, 1);
        for (int i = n - 1; i >= 0; i--){
            if (!check(i)) {
                sub(n - 1, 1); s[i]++;
                // cout << s << endl; 
                for (int j = i; j < n; j++) putchar(s[j]);
                for (int j = n - 2; j >= i; j--) putchar(s[j]);
                puts("");
                break;
            }
            sub(i, 9);
            if (!check(i)) {
                sub(n - 1, 1); s[i]++;
                for (int j = i; j < n; j++) putchar(s[j]);
                for (int j = n - 1; j >= i; j--) putchar(s[j]);
                puts("");
                break;
            }
            sub(i, 9);
        }
    }
    return 0;
}