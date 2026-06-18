add_library(data_structures
    BitSequence.cpp
    LinkedList.cpp
    ../repositories/SequenceRepository.cpp
    ../repositories/DoubleMatrixRepository.cpp
    ../repositories/ComplexMatrixRepository.cpp
    FunctionalEngine.cpp
)

target_include_directories(data_structures PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/repositories  
)

target_compile_options(data_structures PUBLIC
    -Wall -Wextra -Wpedantic -O2
)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

add_executable(lab2_gtk
    main_gtk.cpp
)

target_include_directories(lab2_gtk PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/repositories  
    ${GTKMM_INCLUDE_DIRS}
)

target_link_libraries(lab2_gtk PRIVATE
    data_structures
    ${GTKMM_LIBRARIES}
)

target_compile_options(lab2_gtk PRIVATE
    ${GTKMM_CFLAGS_OTHER}
    -Wall -Wextra -Wpedantic -Wno-reorder
)