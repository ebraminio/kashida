cmake_minimum_required(VERSION 3.0)
project(kashida)

set(HB_HAVE_DIRECTWRITE ON CACHE STRING "" FORCE)
add_subdirectory(harfbuzz)
include_directories(harfbuzz/src ${PROJECT_BINARY_DIR}/harfbuzz/src)

add_executable(kashida kashida.cc)
target_link_libraries(kashida harfbuzz)
