cmake_minimum_required(VERSION 3.0)

project(wsjcpp-jsonrpc2 C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-jsonrpc2_SOURCE_DIR})

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")

list (APPEND WSJCPP_SOURCES "src/main.cpp")

#### BEGIN_WSJCPP_APPEND
#### END_WSJCPP_APPEND

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp-jsonrpc2 ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp-jsonrpc2 ${WSJCPP_LIBRARIES})

install(
    TARGETS
        wsjcpp-jsonrpc2
    RUNTIME DESTINATION
        /usr/bin
)

