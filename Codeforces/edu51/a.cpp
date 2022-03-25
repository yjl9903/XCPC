#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

char s[maxn];

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%s", s);
        int len = strlen(s);
        int a = 0, b = 0, c = 0;
        for (int i = 0; i < len; i++){
            if (s[i] >= 'a' && s[i] <= 'z') a++;
            if (s[i] >= 'A' && s[i] <= 'Z') b++;
            if (s[i] >= '0' && s[i] <= '9') c++;
        }
        if (a && b && c) {
            printf("%s\n", s);
        }
        else {
            int flag = 0;
            if (a > 1){
                for (int i = 0; i < len && a > 1; i++){
                    if (s[i] >= 'a' && s[i] <= 'z') {
                        if (b == 0) {
                            s[i] = 'A'; b++; a--;
                        }
                        else if (c == 0){
                            s[i] = '0'; c++; a--;
                        }
                    }
                    if (a && b && c) {printf("%s\n", s); flag = 1; break;}
                }
            }
            if (flag) continue;

            if (b > 1){
                for (int i = 0; i < len && b > 1; i++){
                    if (s[i] >= 'A' && s[i] <= 'Z') {
                        if (a == 0) {
                            s[i] = 'a'; a++; b--;
                        }
                        else if (c == 0){
                            s[i] = '0'; c++; b--;
                        }
                    }
                    if (a && b && c) {printf("%s\n", s); flag = 1; break;}
                }
            }
            if (flag) continue;

            if (c > 1){
                for (int i = 0; i < len && c > 1; i++){
                    if (s[i] >= '0' && s[i] <= '9') {
                        if (b == 0) {
                            s[i] = 'A'; b++; c--;
                        }
                        else if (a == 0){
                            s[i] = 'a'; a++; c--;
                        }
                    }
                    if (a && b && c) break;
                }
            }
            printf("%s\n", s);
        }
    }
    return 0;
}