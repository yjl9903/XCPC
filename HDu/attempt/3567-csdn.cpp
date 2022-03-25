#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <map>
#define ll long long
#define pi acos(-1)
#define inf 0x3f3f3f3f
using namespace std;
typedef pair<int, int> P;
int factorial[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
int go[4][2] = {1, 0, 0, -1, 0, 1, -1, 0};
bool book[500000];
int pre[10][500000];
char res[10][500000];
char dir[5] = "dlru";
struct node
{
    int mp[3][3];
    int r, c; //'x'的坐标
} st, en;
int Hash(node t)
{
    int s[10];
    int cnt = 0, sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            s[i * 3 + j] = t.mp[i][j];
            cnt = 0;
            for (int k = 0; k < i * 3 + j; k++)
            {
                if (s[k] > s[i * 3 + j])
                    cnt++;
            }
            sum += factorial[i * 3 + j] * cnt;
        }
    }
    return sum;
}
void bfs(int k)
{
    memset(book, 0, sizeof(book));
    memset(pre[k], -1, sizeof(pre[k]));
    queue<node> q;
    while (!q.empty())
        q.pop();
    q.push(st);
    book[Hash(st)] = 1;
    while (!q.empty())
    {
        node t = q.front(), a;
        q.pop();
        int head = Hash(t);
        for (int i = 0; i < 4; i++)
        {
            a = t;
            a.r += go[i][0];
            a.c += go[i][1];
            if (a.c < 0 || a.r < 0 || a.r > 2 || a.c > 2)
                continue;
            a.mp[t.r][t.c] = t.mp[a.r][a.c];
            a.mp[a.r][a.c] = 9;
            int x = Hash(a);
            if (book[x])
                continue;
            book[x] = 1;
            q.push(a);
            pre[k][x] = head;
            res[k][x] = dir[i];
        }
    }
}
node make_node(char s[])
{
    node k;
    int len = strlen(s), r = 0, c = 0;
    for (int i = 0; i < len; i++)
    {
        if ('0' <= s[i] && s[i] <= '9')
            k.mp[r][c] = s[i] - '0';
        else if (s[i] == 'X')
        {
            k.mp[r][c] = 9;
            k.r = r;
            k.c = c;
        }
        else
            continue;
        c++;
        r += c / 3;
        c %= 3;
    }
    return k;
}
void init()
{
    st = make_node("X12345678");
    bfs(0);
    st = make_node("1X2345678");
    bfs(1);
    st = make_node("12X345678");
    bfs(2);
    st = make_node("123X45678");
    bfs(3);
    st = make_node("1234X5678");
    bfs(4);
    st = make_node("12345X678");
    bfs(5);
    st = make_node("123456X78");
    bfs(6);
    st = make_node("1234567X8");
    bfs(7);
    st = make_node("12345678X");
    bfs(8);
}
int main()
{
    init();
    char s[10] = {0};
    int cnt = 0, t, num[10], k;
    scanf("%d", &t);
    while (t--)
    {
        scanf("%s", s);
        int len = strlen(s), j = 0;
        for (int i = 0; i < len; i++)
            if (s[i] == 'X')
                k = i;
            else
                num[s[i] - '0'] = j++; //记录映射关系，即每个数字的位置
        scanf("%s", s);
        len = strlen(s);
        for (int i = 0; i < len; i++)
            if (s[i] == 'X')
                continue;
            else
                s[i] = num[s[i] - '0'] + '1'; //将终态按照相同映射关系映射
        //puts(s);
        printf("Case %d: ", ++cnt);
        st = make_node(s);
        int rear = Hash(st), ans = 0;
        stack<char> ss;
        while (!ss.empty())
            ss.pop();
        while (rear != -1)
        {
            ans++;
            ss.push(res[k][rear]);
            rear = pre[k][rear];
        }
        ss.pop();
        printf("%d\n", ans - 1);
        while (!ss.empty())
            printf("%c", ss.top()), ss.pop();
        puts("");
    }
    return 0;
}