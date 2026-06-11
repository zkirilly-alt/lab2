add_library(data_structures
    BitSequence.cpp
)

target_include_directories(data_structures PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(data_structures PUBLIC
    -Wall -Wextra -Wpedantic -O2
)

add_executable(lab2_ui
    main.cpp
)

target_link_libraries(lab2_ui
    data_structures
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(lab2_gtk
    main_gtk.cpp
)

target_include_directories(lab2_gtk PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${GTKMM_INCLUDE_DIRS}
)

target_link_libraries(lab2_gtk PRIVATE
    data_structures
    ${GTKMM_LIBRARIES}
)

target_compile_options(lab2_gtk PRIVATE
    ${GTKMM_CFLAGS_OTHER}
    -Wall -Wextra -Wpedantic
)