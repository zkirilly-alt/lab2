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
    test)
        cd build
        ./tests/run_tests
        ;;
    clean)
        rm -rf build
        ;;
    *)
        echo "Использование: ./lab2.sh [build|run|test|clean]"
        ;;
esac