#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100000 + 5;

char s[maxn], t[maxn];

// aaabzzzz
// aaacaaaa

int main(){
    scanf("%s%s", s, t); int n = strlen(s);
    for (int i = 0; i < n; i++) 
        if (s[i] > t[i]){
            swap(s, t); break;
        }
        else if (s[i] < t[i]) break;
    int a = n, b = n;
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == 'Z') a = i;
        else break;
    }
    for (int i = n - 1; i >= 0; i--){
        if (s[i] == 'A') b = i;
        else break;
    }

    for (int i = 0; i < n; i++){
        if (s[i] < t[i]){
            if (a == i + 1) {
                putchar(s[i++] + 1);
                while (i < n) i++, putchar('A');
            }
            else {
                putchar(s[i++]);
                while (i < n) i++, putchar('Z');
            }
            return 0;
        }
        else putchar(s[i]);
    }
    return 0;
}