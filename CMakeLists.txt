cmake_minimum_required(VERSION 3.5)
project(
    chat
    VERSION 1.0
    LANGUAGES CXX
)
set(CMAKE_CXX_FLAGS_DEBUG  "-g")

set(SOURCES
    main.cpp
    src/Server.cpp
    src/Listener.cpp
    src/Session.cpp
    src/SessionManager.cpp
    src/Message.cpp)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(Threads REQUIRED)


# Target
add_executable(app ${SOURCES})
target_compile_features(app PRIVATE cxx_std_20)
include_directories(${INCLUDE_DIR})
target_link_libraries(app
    PRIVATE Threads::Threads
    PRIVATE ${Boost_INCLUDE_DIR})