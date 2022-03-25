# coding = utf-8

import os
import sys

if len(sys.argv) == 1:
    print("Error")
    exit()

str = sys.argv[1]

if str[0] == 'h':
    str = "HDu"
if str[0] == 'p':
    str = "PKu"
if str[0] == 'm':
    str = "Model"

if str[0] == 'h' and str[1] == 'd' and str[2] == 'u':
    str = "HDu" + str[3:]
if str[0] == 'p' and str[1] == 'k' and str[2] == 'u':
    str = "PKu"
if str[0] == 'u' and str[1] == 'v' and str[2] == 'a':
    str = "UVa"
if str[0] == 'c' and str[1] == 'f':
    str = "CodeForces\\" + sys.argv[2]
if str[0] == 'a' and str[1] == 't':
    str = "AtCoder\\" + sys.argv[2]
if str[0] == 'c' and str[1] == 'a':
    str = "WannaflyCamp\\" + sys.argv[2]
if str[0] == 'b':
    os.system("code D:\\blog")
    exit()

os.system("code D:\\3-ACM\\" + str)