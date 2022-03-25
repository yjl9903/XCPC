# coding = utf-8

import os
import sys
import shutil

def mkdir(path):
    folder = os.path.exists(path)
    if not folder:
        os.makedirs(path)

def mkfile(path, name):
    file = open(path + '\\' + name, "w")
    file.close()

path = "D:\\3-ACM\\"

if len(sys.argv) == 1:
    print('Error')
    exit()

n = 11
num = False
init = False
cf = False
choose = True
start = 2

if len(sys.argv) >= 3 and sys.argv[2] != '':
    if sys.argv[2][0] != '-':
        n = int(sys.argv[2])
        start = 3

for i in range(start, len(sys.argv)):
    s = sys.argv[i]
    if s[0] != '-':
        continue
    if s == '-num' or s == '-n':
        num = True
    if s == '-init' or s == '-i':
        init = True
    if s == '-cf' or s == '-c' and choose:
        path += "CodeForces\\"
        cf = True
        choose = False
    if s == '-at' or s == '-a' and choose:
        path += "AtCoder\\"
        cf = True
        choose = False
    if s == '-eoj' or s == '-e' and choose:
        path += "EOJ\\"
        cf = True
        choose = False
    if s == '-njust' or s == '-d' and choose:
        path += "NJUST\\"
        choose = False
    if s == '-hdu' or s == '-h' and choose:
        path += "HDu-Multi\\"
        choose = False
    if s == '-nowcoder' or s == '-nc' and choose:
        path += "NowCoder-Multi\\"
        choose = False
    if s == '-camp' or s == '-c' and choose:
        path += "WannaflyCamp\\"
        choose = False

path += sys.argv[1]

mkdir(path)
mkdir(path + "\\debug")
mkdir(path + "\\attempt")
mkdir(path + "\\input")
mkdir(path + "\\standard")
shutil.copytree("D:\\cpp\\.vscode", path + "\\.vscode")
shutil.copy("D:\\cpp\\debug\\file.bat", path + "\\debug")
shutil.copy("D:\\cpp\\debug\\in.bat", path + "\\debug")
mkfile(path + "\\input", "in.txt")
mkfile(path + "\\input", "out.txt")
mkfile(path, "note.md")

if cf:
    shutil.copy("D:\\cpp\\init.cpp", path)
    mkdir(path + "\\hack")
    for i in "abcde":
        mkfile(path, i + ".cpp")
    os.system("code " + path)
    exit()

if init:
    shutil.copy("D:\\cpp\\init.cpp", path)

if (num):
    for i in range(1, n + 1):
        mkfile(path, str(i) + ".cpp")
else:
    a = ord('a')
    for i in range(n):
        mkfile(path, chr(i + a) + ".cpp")

os.system("code " + path)