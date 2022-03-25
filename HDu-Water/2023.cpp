#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 50 + 5;

int a[maxn][maxn], n, m;
double stu[maxn], sub[maxn];

int main(){
    while (~scanf("%d%d", &n, &m)){
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) scanf("%d", &a[i][j]);
        for (int i = 0; i < n; i++){
            int s = 0;
            for (int j = 0; j < m; j++) s += a[i][j];
            stu[i] = double(s) / double(m);
        }
        for (int i = 0; i < m; i++){
            int s = 0;
            for (int j = 0; j < n; j++) s += a[j][i];
            sub[i] = double(s) / double(n);
        }
        for (int i = 0; i < n; i++){
            if (i) printf(" ");
            printf("%.2f", stu[i]);
        }
        printf("\n");
        for (int i = 0; i < m; i++){
            if (i) printf(" ");
            printf("%.2f", sub[i]);
        }
        printf("\n");
        int cnt = 0;
        for (int i = 0; i < n; i++){
            int flag = 1;
            for (int j = 0; j < m; j++) if (a[i][j] < sub[j]) flag = 0;
            if (flag) cnt++;
        }
        printf("%d\n\n", cnt);

    }
    return 0;
}