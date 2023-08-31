@REM call clean.bat
if exist build rd /s /q build

mkdir build
cd build
@REM cmake -G "Visual Studio 16 2019" ..
cmake .. -T host=x86 -A win32
cmake --build . --verbose --config Release