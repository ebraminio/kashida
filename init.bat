@echo off
if not exist harfbuzz git clone --depth=1 https://github.com/behdad/harfbuzz
for %%f in (harfbuzz) do cd %%f & git pull & cd ..

"C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\devenv.exe" .