#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;



int main(){
    int T; scanf("%d", &T); getchar();
    while (T--){
        int cnt = 0;
        char ch;
        while (true){
            ch = getchar(); 
            if (ch == '\n') break;
            if (ch < 0) cnt++;
        }
        printf("%d\n", cnt / 2);
    }    
    return 0;
}