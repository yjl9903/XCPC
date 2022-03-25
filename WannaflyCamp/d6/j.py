from mpmath import *

mp.dps=150

l=chop(taylor(lambda x: sec(x) + tan(x), 0, 26))

print([int(fac(i)*l[i]) for i in range(len(l))])