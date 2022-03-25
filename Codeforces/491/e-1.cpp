#include <iostream>
#include <vector>
using namespace std;

long long n, d[10], f[20];
long long cnt = 0;
vector<int> v;

// 每个数字至少出现一次，dfs枚举所有出现数字次数的排列
// 计算一共取出了数字个数s，每个数字孤立开来看一共有 s！种方案，如果每个数字出现了多次 s! / (该数字出现次数)! 
void Rec(int c)
{
    if (v.size() == 10)
    {
        int br = 0;
        for (int i = 0; i < v.size(); ++i)
        {
            br += v[i];
        }
        long long rs = f[br];
        for (int i = 0; i < v.size(); ++i)
        {
            rs /= f[v[i]];
        }
        cnt += rs;
    }
    else
    {
        if (d[v.size()] == 0)
        {
            v.push_back(0);
            Rec(c);
            v.pop_back();
        }
        else
        {
            int start = 1;
            if (c == v.size())
                start = 0;
            for (int i = start; i <= d[v.size()]; ++i)
            {
                v.push_back(i);
                Rec(c);
                v.pop_back();
            }
        }
    }
}

int main()
{
    cin >> n;
    while (n != 0)
    {
        d[n % 10]++;
        n /= 10;
    }

    f[0] = 1;
    for (int i = 1; i < 20; ++i)
    {
        f[i] = f[i - 1] * i;
    }

    for (int i = 1; i < 10; ++i)
    {
        if (d[i] == 0)
            continue;
        d[i]--;

        Rec(i);
        // 枚举以每个数字为开头的情况数
        d[i]++;
    }

    cout << cnt << endl;
    return 0;
}