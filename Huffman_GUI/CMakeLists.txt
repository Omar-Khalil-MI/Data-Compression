cmake_minimum_required(VERSION 3.0)
project(NAppHello)
find_package(nappgui REQUIRED)
# Remove WIN32 in Linux and macOS
add_executable(naphello WIN32 main.c)
target_link_libraries(naphello ${NAPPGUI_LIBRARIES})

include(CPack)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Huffman-Compression")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Huffman Compression Application")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")

if(WIN32)
    set(CPACK_GENERATOR "NSIS")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
else()
    set(CPACK_GENERATOR "TGZ")
endif()

include(CPack)
