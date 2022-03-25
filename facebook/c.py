T = int(input())

def check(exp):
    a = eval(exp.replace('x', '0').replace('X', '1'))
    b = eval(exp.replace('x', '1').replace('X', '0'))
    return a == b

for kase in range(1, T + 1):
    exp = input()

    a = eval(exp.replace('x', '0').replace('X', '1'))
    b = eval(exp.replace('x', '1').replace('X', '0'))

    print('Case #%d: ' % kase, end='')
    if a == b:
        print(0)
    else:
        print(1)
        f = False
        for i in range(len(exp)):
            if exp[i] == '1' or exp[i] == '0' or exp[i] == 'x' or exp[i] == 'X':
                f |= check(exp[:i] + '1' + exp[i + 1:])
                f |= check(exp[:i] + '0' + exp[i + 1:])
                f |= check(exp[:i] + 'x' + exp[i + 1:])
                f |= check(exp[:i] + 'X' + exp[i + 1:])
            elif exp[i] != '(' and exp[i] != ')':
                f |= check(exp[:i] + '&' + exp[i + 1:])
                f |= check(exp[:i] + '|' + exp[i + 1:])
                f |= check(exp[:i] + '^' + exp[i + 1:])
        if not f:
            print('Error')
            print(exp)
            exit(1)
            