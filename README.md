Compilation steps and execution on Linux machine. Write your main accordingly to the input.

1. CMakeLists.txt with following:
    ```
    cmake_minimum_required(VERSION 2.8)
    project(process)
    find_package(OpenCV REQUIRED)
    include_directories(include ${OpenCV_INCLUDE_DIRS})
    file(GLOB SRC "./src/*.cpp")
    add_executable(process SRC)
    target_link_libraries(process ${OpenCV_LIBS})
    ```
1. `cmake [-DCMAKE_CXX_FLAGS="-g"] .`
1. `make`
1. `./process [args]`
