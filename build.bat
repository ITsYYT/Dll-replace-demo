@REM call clean.bat
if exist build rd /s /q build

mkdir build
cd build
@REM cmake -G "Visual Studio 16 2019" ..
cmake .. -A Win32 -G "Visual Studio 16 2019"
cmake --build . --verbose