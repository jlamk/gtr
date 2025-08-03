cmake_minimum_required(VERSION 3.10)
project(gtr C)

include_directories(include)

add_library(gtr STATIC
    gtr.c
)

target_link_libraries( gtr jansson )

install(FILES gtr.h DESTINATION include)

install(TARGETS gtr
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)