#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

char x[300], cmd[300];
int flag;

struct node{
    int data = 0;
    bool check = false;
    node* left = NULL;
    node* right = NULL;
};

node* newNode()
{
    return new node();
}

node* root = NULL;
queue<node*> que;
vector<int> out;

int addNode(int num)
{
    //printf("%d %s\n", num, cmd);
    //if (cmd[0] == ')')
    //    root -> data = num, root -> check = true;
    int i = 0;
    node* p = root;
    while (cmd[i] != ')')
    {
        if (cmd[i] == 'L')
        {
            if(p -> left == NULL)
                p -> left = newNode();
            p = p-> left;
        }
        else 
        {
            if (p -> right == NULL)
                p -> right = newNode();
            p = p -> right; 
        }
        i++;
    }
    p -> data = num;
    if (p -> check)
        return 0;
    p -> check = true;

    //printf("%d %s\n", num, cmd);

    return 1;
}

void remove(node* p)
{
    if (p == NULL)  return;
    remove(p -> left);
    remove(p -> right);
    delete p;
}

int read()
{
    remove(root);
    flag = 0;
    root = new node();
    int num;
    while (scanf("%s", x) != EOF)
    {
        if (x[1] == ')')
            return 1;
        sscanf(x, "(%d,%s)", &num, cmd);
        flag = addNode(num);
    }
    return 0;
}

int main()
{
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    while (read())
    {
        out.clear();
        if (flag == 0)
        {
            printf("not complete\n");
        }
        else
        {
            node* p = root;
            que.push(root);

            while (!que.empty())
            {
                p = que.front();
                que.pop();
                if (p -> check)
                {
                    out.push_back(p -> data);
                    //printf("%d\n", p -> data);
                }
                else
                {
                    printf("not complete\n");
                    flag = 0;
                    break;
                }
                if (p -> left != NULL)
                    que.push(p -> left);
                if (p -> right != NULL)
                    que.push(p -> right);
            }
            if (flag)
            {
                printf("%d", out[0]);
                for (int i = 1; i < out.size(); i++)
                    printf(" %d", out[i]);
                printf("\n");
            }
        }
    }
    return 0;
}