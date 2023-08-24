@REM call clean.bat
if exist build rd /s /q build

mkdir build
cd build
cmake ..
cmake --build . --verbose