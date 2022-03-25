#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int a[3];

int main(){
    for (int i = 0; i < 3; i++) scanf("%d", a + i);
    sort(a, a + 3);
    if (a[0] + a[1] > a[2]) return puts("0"), 0;
    printf("%d", a[2] - a[0] - a[1] + 1);
    return 0;
}