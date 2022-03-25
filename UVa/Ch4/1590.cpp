#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int ip[maxn], n;

int main(){
    while (~scanf("%d", &n)){
        for (int i = 0, a, b, c, d; i < n; i++){
            scanf("%d.%d.%d.%d", &a, &b, &c, &d);
            int t = d + (c << 8) + (b << 16) + (a << 24);
            ip[i] = t;
        }
        //for (int i = 0; i < n; printf("%0xd ", ip[i++]));
        sort(ip, ip + n);
        int l = 0;
        for (int k = -1; l < 32; l++, k = k << 1){
            int flag = 1;
            for (int j = 1; j < n; j++){
                //printf("%d %d %0x: %0x  %0x\n", l, j, k, ip[j - 1] & k, ip[j] & k);
                if ((ip[j - 1] & k) != (ip[j] & k)){
                    flag = 0; break;
                }
            }
            if (flag)
                break;
        }
        int x = ip[0] & (0xFFFFFFFF << l), y = (0xFFFFFFFF << l);
        //printf("%0\nx", x);
        printf("%d.%d.%d.%d\n", (x & 0xFF000000) >> 24, (x & 0xFF0000) >> 16, (x & 0xFF00) >> 8, x & 0xFF);
        printf("%d.%d.%d.%d\n", (y & 0xFF000000) >> 24, (y & 0xFF0000) >> 16, (y & 0xFF00) >> 8, y & 0xFF);
    }
    return 0;
}