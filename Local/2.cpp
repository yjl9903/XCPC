#include <cstdio>
#include <cstring>
#include <algorithm>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
const int maxn = 1000 + 5;

int n;
int a,b,c,Max = 0;


int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d %d",&a,&b);
        if(a==0){
            if(b==0){
                c=0;
            }
            else{
                printf("-1\n");
                break;
            }
        }
        else{
            if(b%a!=0)c=b/a+1;
            else c=b/a;
        }
        if(Max<c)Max=c;
    }
    printf("%d\n",Max);
   
    return 0;
}