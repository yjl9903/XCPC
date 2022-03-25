#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

struct node
{
    char x[3][5];
}map[15][15];

queue<int> px, py;
queue<char> pd;
vector<int> rx, ry;
vector<char> rd;
int sx, sy, ex, ey;
char sdir;
bool map2[30][30] = {0};

void move(int& x, int& y, char cmd)
{
    if (cmd == 'N')
        x--;
    else if (cmd == 'S')
        x++;
    else if (cmd == 'E')
        y++;
    else
        y--;
}

char turn(char d, char t)
{
    char f[5] = "NESW";
    int i = 0;
    while (f[i] != d)   i++;
    if (t == 'F')
        return f[i];
    else if (t == 'R')
        return f[(i + 1) % 4];
    else 
        return f[(i + 3) % 4];
}

bool bfs()
{
    int x = sx, y = sy, i, flag = 0;
    char ndir = sdir;
    move(x, y, sdir);
    px.push(x); py.push(y); pd.push(sdir);
    rx.push_back(x);    ry.push_back(y);    rd.push_back(sdir);

    while (!px.empty())
    {
        x = px.front();   y = py.front();   ndir = pd.front();
        if (x == ex && y == ey)
            return true;
        px.pop();   py.pop();   pd.pop();

        //cout << rx.size() << ' ' << x << ' ' << y << endl;

        for (int k = 0; k < rx.size() && k < ry.size() && k < rd.size(); k++)
            if (x == rx[k] && y == ry[k] && ndir == rd[k])
                flag = 1;
        if (flag)
        {
            flag = 0;
            continue;
        }
        //cout << x << ' ' << y << ' ' << ndir << endl;
        i = 0;
        while (map[x][y].x[i][0] != '*')
        {
            if (map[x][y].x[i][0] == ndir)
            {
                int len = strlen(map[x][y].x[i]);
                for (int j = 1; j < len; j++)
                {
                    char cmd = map[x][y].x[i][j];
                    
                    int tx = x, ty = y;
                    char td = turn(ndir, cmd);
                    move(tx, ty, td);
                    px.push(tx);    py.push(ty);    pd.push(td);
                    rx.push_back(tx);   rx.push_back(ty);   rd.push_back(td);
                }
            }
            i++;
        }
    }
    return false;
}

void path()
{
    rx.clear(); ry.clear(); rd.clear();
    int x = ex, y = ey;
    while (x != sx && y != sy)
    {
        rx.push_back(x);    ry.push_back(y);

    }
}

int main()
{
    int r, c;
    char name[30];
    while (cin >> name && strcmp(name, "END"))
    {
        rx.clear(); ry.clear(); rd.clear();
        memset(map2, 0, sizeof map2);
        char cmd[5];
        cin >> sx >> sy >> sdir >> ex >> ey;
        while (cin >> r && r)
        {
            cin >> c;
            int i = 0;
            while (cin >> map[r][c].x[i] && map[r][c].x[i][0] != '*')
            {
                i++;
            }
        }
        bool flag = bfs();
        cout << name << endl << "  ";
        if (flag)
        {
            path();
        }
        else 
            cout << "No Solution Possible" << endl;
    }
    return 0;
}