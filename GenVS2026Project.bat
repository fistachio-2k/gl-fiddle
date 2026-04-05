@echo off
setlocal

if not exist build md build
cd build

if not exist .venv (
    echo Creating virtual environment for build dependencies...
    uv venv .venv
    call .venv\Scripts\activate.bat
    uv pip install jinja2
) else (
    call .venv\Scripts\activate.bat
)

cmake -G "Visual Studio 18 2026" -A x64 -S ..

pause

