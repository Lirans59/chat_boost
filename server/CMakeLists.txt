cmake_minimum_required(VERSION 3.5)
project(
    chat_server
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

set(SOURCES
    main.cpp
    src/Server.cpp
    src/Session.cpp
    src/Message.cpp
    src/UserDB.cpp)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Threads REQUIRED)

# Target
add_executable(server ${SOURCES})
target_compile_features(server PRIVATE cxx_std_20)
include_directories(${INCLUDE_DIR} ${Boost_INCLUDE_DIR})
target_link_libraries(server
    PRIVATE Threads::Threads)