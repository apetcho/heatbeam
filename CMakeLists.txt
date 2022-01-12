cmake_minimum_required(VERSION 3.14)
project(heatbeam LANGUAGES C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(X11)

if(X11_FOUND)
    set(HEATSRC src)
    add_library(heatbeam 
        ${HEATSRC}/heatbeam.cpp ${HEATSRC}/heatbeam.hpp)
    add_executable(XHeat ${HEATSRC}/main.cpp ${HEATSRC}/heatbeam.hpp)
    target_include_directories(heatbeam INTERFACE /opt/X11/include)
    target_include_directories(heatbeam PRIVATE ${X11_INCLUDE_DIR})
    target_link_libraries(heatbeam PRIVATE ${X11_LIBRARIES})
    target_link_libraries(XHeat PRIVATE heatbeam ${X11_LIBRARIES})
else(X11_FOUND)
    message("Cannot locate X11 on this system.")
endif(X11_FOUND)


