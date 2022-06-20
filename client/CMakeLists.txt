cmake_minimum_required(VERSION 3.5)
project(
    chat_client
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

set(SOURCES
    main.cpp
    src/Client.cpp
    src/Message.cpp)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED serialization)

# Target
add_executable(client ${SOURCES})
target_compile_features(client PRIVATE cxx_std_20)
include_directories(${INCLUDE_DIR})
target_link_libraries(client
    PRIVATE Threads::Threads
    PRIVATE Boost::serialization)