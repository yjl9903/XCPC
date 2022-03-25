#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int maxn = 1000000 + 5;

int pre[maxn], N, K, res = 0, kind[maxn];
void init(){
    for (int i = 0; i < maxn; i++)
        pre[i] = i;
}
int find(int x){return pre[x] == x ? x : pre[x] = find(pre[x]);}
void join(int x, int y){
    x = find(x); y = find(y);
    pre[x] = y;
}

int main(){
    init(); int cmd, x, y;
    memset(kind, 0, sizeof kind);
    scanf("%d%d", &N, &K);
    while (K--){
        scanf("%d%d%d", &cmd, &x, &y);
        if (x > N || y > N){
            res++;
            continue;
        }
        if (cmd == 1){
            if (kind[x] && kind[y] && kind[x] != kind[y]){
                res++;
                continue;
            }
            if (kind[x])
                kind[y] = kind[x];
            else if (kind[y])
                kind[x] = kind[y];
            else
                kind[x] = kind[y] = 1;
        }
        if (cmd == 2){
            if (x == y || (kind[x] == kind[y] && kind[x])){
                res++;
                continue;
            }
            if (kind[x] && kind[y]){
                int flag = 0;
                if (kind[x] == 1 && kind[y] == 3) flag = 1;
                if (kind[x] == 2 && kind[y] == 1) flag = 1;
                if (kind[x] == 3 && kind[y] == 2) flag = 1;
                if (flag){
                    res++;
                    continue;
                }
            }
            else if (kind[x]){
                switch(kind[x]){
                    case 1: kind[y] = 2; break;
                    case 2: kind[y] = 3; break;
                    case 3: kind[y] = 1; break;
                }
            }
            else if (kind[y]){
                switch(kind[y]){
                    case 1: kind[x] = 3; break;
                    case 2: kind[x] = 1; break;
                    case 3: kind[x] = 2; break;
                }
            }
            else{
                kind[x] = 1;
                kind[y] = 2;
            }
        }
    }
    printf("%d", res);
    return 0;
} 