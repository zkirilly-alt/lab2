add_executable(lab2_gtk main_gtk.cpp)

target_include_directories(lab2_gtk PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

target_include_directories(lab2_gtk PRIVATE ${GTKMM_INCLUDE_DIRS})

target_link_libraries(lab2_gtk PRIVATE ${GTKMM_LIBRARIES})

target_compile_options(lab2_gtk PRIVATE -Wall -Wextra -Wpedantic ${GTKMM_CFLAGS_OTHER})