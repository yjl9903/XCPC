#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

vector<char> dic;
int map[205][205], res[1000], cnt1 = 2, cnt2 = -1, r, c, flag;
int dir[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
char f[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"};
char letter[7] = "WAKJSD";

void show()
{
    for (int i = 0; i < r + 2; i++)
        {
            for (int j = 0; j < c + 2; j++)
                cout << setw(2) << map[i][j];
            cout << endl;
        }
}

void dfs(int x, int y, int k)
{
    if (x < 0 || y < 0 || x >= r + 2|| y >= c + 2)
        return;
    if (map[x][y] != k)
        return;
    if (k)
        map[x][y] = cnt1;
    else
        map[x][y] = cnt2;
    for (int i = 0; i < 4; i++)
        dfs(x + dir[i][0], y + dir[i][1], k);
}

void dfs2(int x, int y)
{
    if (x < 0 || y < 0 || x >= r + 2|| y >= c + 2)
        return;
    if (map[x][y] > 0 && flag)
    {
        res[map[x][y]]++;
        flag = 0;
    }
    if (map[x][y] < -1)
    {
        map[x][y] = 0;
        for (int i = 0; i < 4; i++)
            dfs2(x + dir[i][0], y + dir[i][1]);
    }
    
}

int main()
{
    int kase = 1;
    while (cin >> r >> c && r && c)
    {
        memset(map, 0, sizeof map);
        memset(res, 0, sizeof res);
        dic.clear();
        cnt1 = 2, cnt2 = -1;
        c *= 4;
        char x;
        for (int i = 1; i <= r; i++)
        {
            int j;
            for (j = 1; j < c; j += 4)
            {
                cin >> x;
                if (x <= '9')
                {
                    for (int k = 0; k < 4; k++)
                    {
                        map[i][j + k] = f[x - '0'][k] - '0';
                    }
                }
                else
                {
                    for (int k = 0; k < 4; k++)
                    {
                        map[i][j + k] = f[x - 'a' + 10][k] - '0';
                    }
                }
            }
            map[i][j] = 0;
        }
        //show(r, c);
        
        dfs(0, 0, 0);
        cnt2--;

        for (int i = 0; i < r + 2; i++)
            for (int j = 0; j < c + 2; j++)
                if (map[i][j] == 1)
                    dfs(i, j, 1), cnt1++;
                else if (!map[i][j])
                    dfs(i, j, 0), cnt2--;
        
        //show();

        for (int i = 0; i < r + 2; i++)
            for (int j = 0; j < c + 2; j++)
                if (map[i][j] < -1)
                    flag = 1, dfs2(i, j);
        for (int i = 2; i < cnt1; i++)
        {
            dic.push_back(letter[res[i]]);
        }
        sort(dic.begin(), dic.end());
        cout << "Case " << kase++ << ": ";
        for (int i = 0; i < dic.size(); i++)
        {
            cout << dic[i];
        }
        cout << endl;
        //show(r, c);
    }
    return 0;
}