#!/bin/bash

# path=$(pwd)
# echo "Actual pwd: $path"
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

echo -n "Please enter a project name: "
read project_name

echo -n "Please enter a project subname: "
read project_sub_name

echo -n "Please enter a short description: "
read short_desc

### README creation

echo "# $project_name" >> README.md
echo "## $project_sub_name" >> README.md
echo -e "\n$short_desc \n" >> README.md
echo "## Overview" >> README.md
echo -e "\n\n" >> README.md
echo "## Purpose" >> README.md
echo -e "\n\n" >> README.md
echo "## Features" >> README.md
echo " -[\`cmake\`](https://cmake.org/) for building project" >> README.md
echo -e "\n\n" >> README.md
echo "## Installation" >> README.md
echo -e "\n\n" >> README.md
echo "## Installation" >> README.md
echo -e "\`\`\`bash\nsudo apt install cmake\n\`\`\`" >> README.md
echo -e "\n\n" >> README.md
echo "## Run" >> README.md
echo -e "\`\`\`bash\ncd build\n\`\`\`" >> README.md
echo -e "\`\`\`bash\ncmake -DCMAKE_CXX=Clang -DCMAKE_BUILD_TYPE=Debug ../\n\`\`\`" >> README.md

mkdir $project_name 

mkdir $project_name/src
mkdir $project_name/include
mkdir build

cp -r $SCRIPT_DIR/cmake .
cp -r $SCRIPT_DIR/docs .
cp -r $SCRIPT_DIR/tests .
cp -r $SCRIPT_DIR/Logger $project_name

cp $SCRIPT_DIR/LICENSE .
cp $SCRIPT_DIR/build.bat .
cp $SCRIPT_DIR/CMakePresets.json .
cp $SCRIPT_DIR/main.cpp ./$project_name/src/
cp $SCRIPT_DIR/include/example.h ./$project_name/include/
cp $SCRIPT_DIR/TODO .
cp $SCRIPT_DIR/../.gitignore .

echo "#include \"../$project_name/include/example.h\"" | cat - tests/tests.cpp > temp && mv temp tests/tests.cpp

echo -e "cmake_minimum_required(VERSION 3.14)\ninclude(cmake/Presets.cmake)\n" > CMakeLists.txt
echo "project($project_name CXX)" >> CMakeLists.txt
echo "project(\${CMAKE_PROJECT_NAME} DESCRIPTION \"$short_desc\")" >> CMakeLists.txt
cat $SCRIPT_DIR/CMakeLists.txt >> CMakeLists.txt

git init

