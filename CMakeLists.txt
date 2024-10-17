cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(my_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 获取所有 .cpp 文件
file(GLOB SOURCES "*.cpp")

# 添加可执行文件
add_executable(my_project main.cpp ${SOURCES})

find_package(Boost REQUIRED COMPONENTS system thread)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(my_project PRIVATE Boost::system Boost::thread)
    #target_link_libraries(my_project PRIVATE ${Boost_LIBRARIES})
endif()
# # 指定 JsonCpp 的头文件路径
# include_directories(/usr/local/include/boost)

# # 指定 JsonCpp 的库路径
# link_directories(/usr/local/lib)
# #这个路径一定要确认好

# 链接 JsonCpp 库

#target_link_libraries(my_project PRIVATE Boost::asio Boost::Beast)
