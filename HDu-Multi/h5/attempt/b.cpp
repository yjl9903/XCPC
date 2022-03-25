#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 10 + 5;

int n, m, k, a[maxn], b[maxn], vis[maxn];

void small(){
    ms(vis, 0);
    int c = 0, t = b[0], flag = 0;
    for (int i = m - 1; i > 0; i--){
        if (b[i] < t && b[i]) t = b[i], flag = i;
    }
    if (flag){
        swap(b[0], b[flag]); c++;
    }
    for (int i = 1; i < m && c < k; i++){
        t = b[i], flag = 0;
        for (int j = m - 1; j > i; j--){
            if (b[j] < t) t = b[j], flag = j;
        }
        if (flag){
            swap(b[i], b[flag]);
            c++;
        }
    }
    for (int i = 0; i < m; i++) printf("%d", b[i]);
    putchar(' ');
}
void big(){
    ms(vis, 0);
    int c = 0;
    for (int i = 0; i < m && c < k; i++){
        // printf("%d", a[i]);
        int t = a[i], flag = 0;
        for (int j = m - 1; j > i; j--){
            if (a[j] > t) t = a[j], flag = j;
        }
        if (flag){
            swap(a[i], a[flag]);
            c++;
        }
    }
    for (int i = 0; i < m; i++) printf("%d", a[i]);
    puts("");
}

int main(){
    int T; scanf("%d", &T);
    while (T--){
        scanf("%d%d", &n, &k);
        int x = n; m = 0;
        while (x){
            a[m++] = x % 10;
            x /= 10;
        }
        reverse(a, a + m); 
        for (int i = 0; i < m; i++) b[i] = a[i];
        // memcpy(b, a, sizeof a);
        small(); 
        big();
    }
    return 0;
}