Compilation steps

# CMakeLists.txt with following:
    ```
    cmake_minimum_required(VERSION 2.8)
    project(process)
    find_package(OpenCV REQUIRED)
    include_directories(include ${OpenCV_INCLUDE_DIRS})
    file(GLOB SRCS "./src/*.cpp")
    add_executable(process SRCS)
    target_link_libraries(process ${OpenCV_LIBS})
    ```
# `cmake [-DCMAKE_CXX_FLAGS="-g"] .`
# `make`
# `./process [args]`
