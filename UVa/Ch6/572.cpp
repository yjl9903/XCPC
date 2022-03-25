#include <iostream>
#include <cstring>
using namespace std;
int map[105][105], check[105][105] = {0}, row, col, cnt = 0;
int dir[8][2] = {{1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}};

void bfs(int x, int y)
{
    if (!map[x][y] || check[x][y] || x >= row || y >= col || x < 0 || y < 0) return;
    check[x][y] = 1;
    for (int i = 0; i < 8; i++)
        bfs(x + dir[i][0], y + dir[i][1]);
}
int main()
{
    while (cin >> row >> col)
    {
        if (!row) break;
        char xx;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
            {
                cin >> xx;
                if (xx == '*')
                    map[i][j] = 0;
                else 
                    map[i][j] = 1;
            }
        memset(check, 0, sizeof check);
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (!check[i][j] && map[i][j])
                {
                    bfs(i, j);
                    cnt++;
                }
        cout << cnt << endl;
        cnt = 0;
        
    }
    return 0;
}