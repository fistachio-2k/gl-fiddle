@echo off
setlocal

if not exist Build md Build
cd Build

cmake -G "Visual Studio 18 2026" -A x64 -S ..

pause

