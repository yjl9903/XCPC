#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 100 + 5;

int n, s[maxn], cnt[maxn], kind[maxn];

int main(){
    scanf("%d", &n); 
    for (int i = 0; i < n; i++){
        scanf("%d", s + i);
        cnt[s[i]]++;
    }
    int s1 = 0, s2 = 0, s3 = 0;
    for (int i = 1; i <= 100; i++){
        if (cnt[i] == 1) s1++;
        if (cnt[i] >= 3) s2++;
    }
    if (s1 % 2 == 0){
        puts("YES"); int a = s1 / 2;
        for (int i = 0; i < n; i++){
            if (cnt[s[i]] == 1) {
                if (a) putchar('A'), a--;
                else putchar('B');
            }
            else putchar('B');
        }
    }
    else {
        int a = s1 / 2, flag = 1;
        if (s2){
            puts("YES"); 
            for (int i = 0; i < n; i++){
                if (cnt[s[i]] == 1) {
                    if (a) putchar('A'), a--;
                    else putchar('B');
                }
                else if (cnt[s[i]] == 3 && flag){
                    putchar('A'); flag = 0;
                }
                else putchar('B');
            }
        }
        else puts("NO");
    }
    return 0;
}