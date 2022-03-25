@echo off
mkdir %1
cd %1
mkdir .vscode
mkdir debug
mkdir attempt
mkdir input
mkdir hack
copy D:\cpp\.vscode .vscode >nul
copy D:\cpp\debug\file.bat debug\ >nul
copy D:\cpp\debug\in.bat debug\ >nul
copy D:\cpp\init.cpp >nul
type nul>a.cpp
type nul>b.cpp
type nul>c.cpp
type nul>d.cpp
type nul>e.cpp
type nul>note.md
cd input
type nul>in.txt
type nul>out.txt
cd ..
cd ..
code %1
exit
exit
