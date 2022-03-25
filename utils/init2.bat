@echo off
mkdir %1
cd %1
mkdir .vscode
mkdir debug
mkdir attempt
mkdir input
mkdir standard
copy D:\cpp\.vscode .vscode >nul
copy D:\cpp\debug\file.bat debug\ >nul
type nul>a.cpp
type nul>b.cpp
type nul>c.cpp
type nul>d.cpp
type nul>e.cpp
type nul>f.cpp
type nul>g.cpp
type nul>h.cpp
type nul>i.cpp
type nul>j.cpp
type nul>k.cpp
type nul>note.md
cd input
type nul>in.txt
type nul>out.txt
cd ..
cd ..
code %1
exit
