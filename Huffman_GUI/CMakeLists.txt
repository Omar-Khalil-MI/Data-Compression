cmake_minimum_required(VERSION 3.0)
project(NAppHello)
find_package(nappgui REQUIRED)
# Remove WIN32 in Linux and macOS
add_executable(naphello WIN32 main.c)
target_link_libraries(naphello ${NAPPGUI_LIBRARIES})