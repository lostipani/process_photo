## Dependencies
[OpenCV](https://docs.opencv.org/4.8.0/d9/df8/tutorial_root.html)
[Boost::program_options](https://www.boost.org/doc/libs/1_83_0/doc/html/program_options.html)    

### Build Boost::program_options
1. Untar and move the `boost_1_xx_x/` folder to `/usr/local/`
1. Run bootstrap to prepare library building
    ```
    sudo ./bootstrap.sh --prefix=/usr/local --with-libraries=program_options
    sudo ./b2 install
    ls /usr/local/lib/libboost*
    ls /usr/local/include/boost/
    ```


## Compilation and execution

Compilation steps and execution on Linux machine. Write your `main.cpp` accordingly to the input.
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
1. `./process --options [args]`
