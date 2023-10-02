cmake_minimum_required(VERSION 3.1)
project(process_photo_mumi23)
#set(BOOST_ROOT /usr/local/boost_1_83_0)

find_package(OpenCV REQUIRED)
find_package(Boost 1.83 COMPONENTS program_options REQUIRED)

include_directories(include ${OpenCV_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

file(GLOB SRC "src/*.cpp")
add_executable(process ${SRC})
#add_executable(process src/main.cpp src/utils.cpp src/canvas.cpp src/frame.cpp)

target_link_libraries(process ${Boost_LIBRARIES} ${OpenCV_LIBS})


