cmake_minimum_required(VERSION 3.0)
project(NAppHello)
find_package(nappgui REQUIRED)
include("${NAPPGUI_ROOT_PATH}/prj/NAppProject.cmake")
nap_project_desktop_app(Huffman-Compression huffman)

install(TARGETS Huffman-Compression
        RUNTIME DESTINATION .
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/README.md
        DESTINATION share/Huffman-Compression)
