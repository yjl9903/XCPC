#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn = 64 + 5;

int N, img[maxn][maxn];
vector<int> path, res; 

void build(PII p1, PII p2, int t){
    int col[2] = {0, 0};
    if (t)  path.push_back(t);
    for (int i = p1.first; i <= p2.first; i++)
        for (int j = p1.second; j <= p2.second; j++){
            col[img[i][j]]++;
        }

    if (col[0] == 0){
        int ans = 0;
        for (int i = path.size() - 1; i >= 0; i--){
            ans = ans * 5 + path[i];
        }
        res.push_back(ans);
    }
    else if (col[1]){
        int mx = (p1.first + p2.first) / 2, my = (p1.second + p2.second) / 2;
        build(p1, make_pair(mx, my), 1);
        build(make_pair(p1.first, my + 1), make_pair(mx, p2.second), 2);
        build(make_pair(mx + 1, p1.second), make_pair(p2.first, my), 3);
        build(make_pair(mx + 1, my + 1), p2, 4);
    }
    if (t)  path.pop_back();
}

void rebuild(PII p1, PII p2, int t){
    if (t == 0){
        for (int i = p1.first; i <= p2.first; i++)
            for (int j = p1.second; j <= p2.second; j++){
                img[i][j] = 1;
            }
    }
    else{
        int mx = (p1.first + p2.first) / 2, my = (p1.second + p2.second) / 2;
        switch(t % 5){
            case 0:
                for (int i = p1.first; i <= p2.first; i++)
                    for (int j = p1.second; j <= p2.second; j++){
                        img[i][j] = 1;
                    }
                break;
            case 1:
                rebuild(p1, make_pair(mx, my), t / 5);
                break;
            case 2:
                rebuild(make_pair(p1.first, my + 1), make_pair(mx, p2.second), t / 5);
                break;
            case 3:
                rebuild(make_pair(mx + 1, p1.second), make_pair(p2.first, my), t / 5);
                break;
            case 4:
                rebuild(make_pair(mx + 1, my + 1), p2, t / 5);
                break;
        }
    }
}

int main(){
    int kase = 0;
    while (~scanf("%d", &N) && N){
        if (kase)   printf("\n");
        if (N > 0){
            char tt[70];
            for (int i = 0; i < N; i++){
                scanf("%s", tt);
                for (int j = 0; j < N; j++){
                    img[i][j] = tt[j] - '0';
                }
            }
                
            path.clear();   res.clear();
            build(make_pair(0, 0), make_pair(N - 1, N - 1), 0);
            sort(res.begin(), res.end());
            
            printf("Image %d\n", ++kase);
            for (int i = 0; i < res.size(); i++){
                if (i && i % 12 == 0)    printf("\n");
                else if (i) printf(" ");
                printf("%d", res[i]);
            }
            if (res.size()) printf("\n");
            printf("Total number of black nodes = %d\n", res.size());
        }
        else{
            N = -N;
            res.clear();    memset(img, 0, sizeof img);
            int tt;
            while (~scanf("%d", &tt) && tt != -1){
                rebuild(make_pair(0, 0), make_pair(N - 1, N - 1), tt);
            }

            printf("Image %d\n", ++kase);
            for (int i = 0; i < N; i++, printf("\n"))
                for (int j = 0; j < N; j++)
                    if (img[i][j])
                        printf("*");
                    else
                        printf(".");
            // printf("\n");
        }
    }
    return 0;
}