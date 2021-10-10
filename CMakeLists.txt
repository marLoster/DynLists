cmake_minimum_required(VERSION 3.0.0)
project(dynlists VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(${PROJECT_SOURCE_DIR})
add_executable(dynlists main.c dynlists.c)  # be sure there's exactly one main() function in the source files

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
