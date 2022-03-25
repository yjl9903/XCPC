#include <iostream>
#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int, int> PII;
const int maxn = 1000000 + 5;

PII dq[maxn];
int head, tail;
int n, k, a[maxn], ans[2][maxn];

int main(){
    // ios::sync_with_stdio(false);
    while (~scanf("%d%d", &n, &k)){
        ms(ans, 0);
        for (int i = 0; i < n; scanf("%d", &a[i++]));
        // dq.clear();
        int l = 0, r = 0;
        head = 1; tail = 0;
        for (int i = 0; i < k - 1; i++){
            while (head <= tail && dq[tail].second <= a[i]) tail--;
            dq[++tail] = make_pair(i, a[i]);
        }
        for (int i = k - 1; i < n; i++){
            while (head <= tail && dq[tail].second <= a[i]) tail--;
            dq[++tail] = make_pair(i, a[i]);
            while (dq[head].first + k - 1 < i) head++;
            ans[1][i] = dq[head].second;
        }

        head = 1; tail = 0;
        for (int i = 0; i < k - 1; i++){
            while (head <= tail && dq[tail].second >= a[i]) tail--;
            dq[++tail] = make_pair(i, a[i]);
        }
        for (int i = k - 1; i < n; i++){
            while (head <= tail && dq[tail].second >= a[i]) tail--;
            dq[++tail] = make_pair(i, a[i]);
            while (dq[head].first + k - 1 < i) head++;
            ans[0][i] = dq[head].second;
        }

        for (int i = 0; i + k - 1 < n; i++){
            if (i) printf(" ");
            printf("%d", ans[0][i + k - 1]);
        }
        cout << endl;
        for (int i = 0; i + k - 1 < n; i++){
            if (i) printf(" ");
            printf("%d", ans[1][i + k - 1]);
        }
        cout << endl;
    }
    return 0;
}