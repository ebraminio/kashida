project (kashida)

set(HB_HAVE_DIRECTWRITE ON CACHE STRING "" FORCE)
add_subdirectory(harfbuzz)

add_executable(kashida kashida.cc)
target_link_libraries(kashida harfbuzz)
