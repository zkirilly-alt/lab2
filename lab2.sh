
case $1 in
    build)
        rm -rf build
        mkdir build
        cd build
        cmake .. -DCMAKE_BUILD_TYPE=Debug
        cmake --build .
        ;;
    run)
        cd build
        ./src/lab2_ui
        ;;
    gtk)
        cd build
        ./src/lab2_gtk
        ;;
    test)
        cd build
        ./tests/run_tests
        ;;
    clean)
        rm -rf build
        ;;
    *)
        ;;
esac