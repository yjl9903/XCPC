template<typename T>
struct KM {
    T dbx[maxn], dby[maxn], slack[maxn], C[maxn][maxn];
    int linky[maxn], pre[maxn];
    bool vis[maxn];
    int nx, ny;

    void bfs(int k) {
        int px, py = 0, yy = 0; T d;
        memset(pre, 0, sizeof pre);
        for (int i = 0; i <= ny; i++) slack[i] = inf;
        linky[py] = k;
        do {
            px = linky[py]; d = inf; vis[py] = 1;
            for (int i = 1; i <= ny; i++) {
                if (vis[i] == 0) {
                    if (slack[i] > dbx[px] + dby[i] - C[px][i]) {
                        slack[i] = dbx[px] + dby[i] - C[px][i];
                        pre[i]=py;
                    }
                    if (slack[i] < d) {
                        d = slack[i], yy = i;
                    }
                }
            }
            for (int i = 0; i <= ny; i++) {
                if (vis[i]) dbx[linky[i]] -= d, dby[i] += d;
                else slack[i] -= d;
            }
            py = yy;
        } while (linky[py] != 0);
        while (py) linky[py] = linky[pre[py]], py = pre[py];
    }

    T km(int n, int m) {
        nx = n; ny = m;
        memset(dbx, 0, sizeof dbx);
        memset(dby, 0, sizeof dby);
        memset(linky, 0, sizeof linky);
        for (int i = 1; i <= nx; i++) {
            memset(vis, 0, sizeof vis); bfs(i);
        }
        T ans = 0;
        for (int i = 1; i <= ny; i++) {
            if (linky[i]) ans += dbx[linky[i]] + dby[i];
        }
        return ans;
    }
};

KM<float> f;

int main() {
    int n;
    scanf("%d",&n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%f", &f.C[i][j]);
            f.C[i][j] = log(f.C[i][j]);
        }
    }
    f.km(n, n);
    for (int i = 1; i <= n; i++) {
        printf("%d%c", f.linky[i], i == n ? '\n' : ' ');
    }
}