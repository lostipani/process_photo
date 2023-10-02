## Compilation
Tested on a `x86_64 GNU/Linux, 20.04.1-Ubuntu` machine. 
1. You would like to write your own `src/main.cpp` or leave as it is.
1. See `CMakeLists.txt` for details on library import.
1. `cmake [-DCMAKE_CXX_FLAGS="-g"] .`
1. `make`

## Execution
Tested on a `x86_64 GNU/Linux, 20.04.1-Ubuntu` machine. 
1. `./process --options [args]` or write yours and run `./run_process.sh`

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

