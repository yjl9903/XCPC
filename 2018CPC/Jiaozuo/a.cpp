#include<iostream>
#include<cstdio>
using namespace std;
int T;
char c[20];
string s;
string s1="JESSIE";
string s2="jessie";
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf(" %s",c);
        s=c;
        if(s.size()!=6)printf("Dare you say that again?\n");
        else
        {
            bool flag=false;
            for(int i=0;i<s.size();i++)
            {
                if(s[i]!=s1[i]&&s[i]!=s2[i])
                {
                    printf("Dare you say that again?\n");
                    flag=true;
                    break;
                }
            }
            if(!flag)printf("Good guy!\n");
        }
    }
    return 0;
}