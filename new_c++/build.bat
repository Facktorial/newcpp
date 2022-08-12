if not exist %~dp0\build mkdir %~dp0\build
cd build

@echo off
cmake ../ -DCMAKE_BUILD_TYPE=Debug

msbuild Algorithm_Project.sln

.\Debug\TEST