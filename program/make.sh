#!/bin/bash

# chmod +x make.sh

# 设置变量
BUILD_DIR="build"
CMAKE_OPTIONS=""

# 清理之前的构建
if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning up previous build..."
    rm -rf "$BUILD_DIR"
fi

# 创建构建目录
echo "Creating build directory..."
mkdir "$BUILD_DIR"
cd "$BUILD_DIR" || exit

# 运行 CMake
echo "Running CMake..."
cmake .. $CMAKE_OPTIONS

# 编译项目
echo "Building the project..."
make

# 可选：运行测试
# echo "Running tests..."
# make test
./project

# # 返回到原目录
# cd ..

# echo "Build completed."


