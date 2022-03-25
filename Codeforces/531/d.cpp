#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int maxn = 300000 + 5;

int n; char s[maxn];

int main(){
    scanf("%d%s", &n, s + 1);
    int sum[3] = {0, 0, 0};
    for (int i = 1; i <= n; i++) sum[s[i] - '0']++;
    int nd = n / 3, pre[3] = {0, 0, 0};
    for (int i = 1; i <= n; i++) {
        if (sum[0] < nd) {
            if (s[i] == '1' && sum[1] > nd) {
                s[i] = '0';
                sum[0]++; sum[1]--;
            } else if (s[i] == '2' && sum[2] > nd) {
                s[i] = '0';
                sum[0]++; sum[2]--;
            }
        } else if (sum[1] < nd) {
            if (s[i] == '0' && sum[0] > nd && pre[0] == nd) {
                s[i] = '1';
                sum[0]--; sum[1]++;
            } else if (s[i] == '2' && sum[2] > nd) {
                s[i] = '1';
                sum[1]++; sum[2]--;
            }
        } else if (sum[2] < nd) {
            if (s[i] == '0' && sum[0] > nd && pre[0] == nd) {
                s[i] = '2';
                sum[0]--; sum[2]++;
            } else if (s[i] == '1' && sum[1] > nd && pre[1] == nd) {
                s[i] = '2';
                sum[1]--; sum[2]++;
            }
        }
        pre[s[i] - '0']++;
    }
    cout << s + 1;
    return 0;
}