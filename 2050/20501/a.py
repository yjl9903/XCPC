maxn = 10

for i in range(maxn):
    temp = '''
#include <cstdio>
int main() {
    return puts("%d"), 0;
}
''' % i
    print(temp)   
    