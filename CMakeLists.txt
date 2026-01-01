cmake_minimum_required(VERSION 3.0)

project(wsjcpp-jsonrpc20 C CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/src.wsjcpp/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${wsjcpp-jsonrpc20_SOURCE_DIR})

# include header dirs
list (APPEND WSJCPP_INCLUDE_DIRS "src")
list (APPEND WSJCPP_INCLUDE_DIRS "src/app")
list (APPEND WSJCPP_INCLUDE_DIRS "src.wsjcpp/nlohmann_json/nlohmann")

# package
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_base.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_base.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_python.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_python.cpp")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_webjs.h")
list (APPEND WSJCPP_SOURCES "src/wsjcpp_jsonrpc20_export_cli_webjs.cpp")

# app
list (APPEND WSJCPP_SOURCES "src/app/main.cpp")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_handler_game_create.h")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_handler_game_create.cpp")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_handler_auth.h")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_handler_auth.cpp")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_notification_chat.h")
list (APPEND WSJCPP_SOURCES "./src/app/wsjcpp_json_rpc20_notification_chat.cpp")

#### BEGIN_WSJCPP_APPEND
#### END_WSJCPP_APPEND

include_directories(${WSJCPP_INCLUDE_DIRS})

add_executable (wsjcpp-jsonrpc20 ${WSJCPP_SOURCES})

target_link_libraries(wsjcpp-jsonrpc20 ${WSJCPP_LIBRARIES})

install(
    TARGETS
        wsjcpp-jsonrpc20
    RUNTIME DESTINATION
        /usr/bin
)


