cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(project VERSION 1.0)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加 include 目录
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/lib/third_party/zstd/include)  # 如果有第三方库的头文件
include_directories(${CMAKE_SOURCE_DIR}/lib/third_party/)  # 如果有第三方库的头文件

# 查找所有源文件
file(GLOB_RECURSE SOURCES
    src/*.cpp
    lib/my_dependency/src/*.cpp  # 自己的依赖源文件
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

# 链接第三方库（如果有）
# set(CMAKE_PREFIX_PATH ${CMAKE_SOURCE_DIR}/lib/third_party/zstd)
# find_package(ZSTD REQUIRED)
# target_link_libraries(project ZSTD)
# # 链接第三方库（如果有）
find_library(ZSTD_LIB zstd PATHS ${CMAKE_SOURCE_DIR}/lib/third_party/zstd/lib)
target_link_libraries(${PROJECT_NAME} ${ZSTD_LIB})
# 添加测试支持
enable_testing()
# add_subdirectory(tests)  # 如果有测试模块
