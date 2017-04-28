@echo off
if not exist harfbuzz git clone --depth=1 https://github.com/behdad/harfbuzz
for %%f in (harfbuzz) do cd %%f & git pull & cd ..

rmdir /s /q build 2>NUL
mkdir build
cd build
cmake ..
start kashida.sln
cd..