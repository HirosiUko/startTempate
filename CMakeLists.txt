cmake_minimum_required(VERSION 3.10)
project(PEPS_CLIENT VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Poco REQUIRED Foundation Net JSON NetSSL )

set( SOURCES
    main.cpp
    network/PEPS_Networking.cpp
    hj_template/HJ_Template.cpp
)

add_executable(peps_client ${SOURCES})

# Include directories
target_include_directories(peps_client PRIVATE ${CMAKE_SOURCE_DIR}/hj_template ${CMAKE_SOURCE_DIR}/utility)

# Poco library link
target_link_libraries(peps_client PRIVATE Poco::Foundation Poco::Net Poco::JSON Poco::NetSSL)