#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int root = 1, flag = 0, content[300], check[300], left[300], right[300], cnt = 1;
char x[300], cmd[300];
vector<int> out;

int newNode()
{
    cnt++;
    left[cnt] = 0;
    right[cnt] = 0;
    return cnt;
}

int addNode(int num)
{
    int p = 1, i = 0;
    while (cmd[i] != ')')
    {
        //printf("%d\n", cmd[i]);
        if (cmd[i] == 'L')
        {
            if (left[p] == 0)
            {
                left[p] = newNode();
            }
            p = left[p];
        }
        else
        {
            if (right[p] == 0)
            {
                right[p] = newNode();
            }
            p = right[p];
        }
        i++;

        //printf("%d %d %d\n", p, left[p], right[p]);

    }
    if (check[p])
        return 1;
    content[p] = num;
    check[p] = 1;
    return 0;
}

int read()
{
    memset(content, 0, sizeof content);
    memset(left, 0, sizeof left);
    memset(right, 0, sizeof right);
    memset(check, 0, sizeof check);
    root = 1;
    cnt = 1;
    flag = 0;               //flag为1，表示错误
    int num;
    while (scanf("%s", x) != EOF)
    {
        if (x[1] == ')')
            return 1;
        sscanf(x, "(%d,%s)", &num, cmd);
        //printf("%d %s", num, cmd);
        if(addNode(num))
            flag = 1;
    }
    return 0;
}
void bfs()
{
    out.clear();
    queue<int> que;
    int p = 1;
    que.push(p);
    while (!que.empty())
    {
        p = que.front();
        que.pop();

        //printf("%d %d %d %d \n", content[p], check[p], left[p], right[p]);

        if(check[p])
        {
            out.push_back(content[p]);
        }
        else
        {
            flag = 1;
            return;
        }
        if (left[p])
            que.push(left[p]);
        if (right[p])
            que.push(right[p]);
    }
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    while (read())
    {
        bfs();
        if (flag)
            printf("not complete");
        else
        {
            printf("%d", out[0]);
            for (int i = 1; i < out.size(); i++)
            {
                printf(" %d", out[i]);
            }
        }
        printf("\n");
    }
    return 0;
}