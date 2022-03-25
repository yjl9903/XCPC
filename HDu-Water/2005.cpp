#include <cstdio>
#include <cstring>
using namespace std;
bool checkRunNian(int year){
    if (year % 100) return year % 4 == 0;
    else    return year % 400 == 0;
}
int getSum(int year, int month, int day){
    int flag = year > 0 && month > 0 && month < 13 && day > 0, res = 0;
    if (!flag)  return -1;
    int m[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (checkRunNian(year)) m[1]++;
    for (int i = 1; i < month; i++){
        res += m[i - 1];
    }
    if (day > m[month - 1]) return -1;
    return res + day;
}
int read(char* in, int* birth){
    int tot = 0, len = strlen(in);
    birth[0] = birth[1] = birth[2] = 0;
    for (int i = 0; i < len; i++){
        if (tot > 2)    return 0;
        if (in[i] >= '0' && in[i] <= '9'){
            birth[tot] = 10 * birth[tot] + in[i] - '0';
        }
        else if (in[i] == '-' || in[i] == '/' || in[i] == '\\' || in[i] == '.'){
            tot++;
        }
        else
            return 0;
    }
    if (getSum(birth[0], birth[1], birth[2]) == -1) return 0;
    return 1;
}

int main()
{
    int birth[3] = {0, 0, 0}, newDay[3] = {0};
    char in[20];
    while (~scanf("%s", in)){
        read(in, birth);
        printf("%d\n", getSum(birth[0], birth[1], birth[2]));
    }
    return 0;
}