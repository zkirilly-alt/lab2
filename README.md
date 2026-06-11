# lab2

Перегрузка оператора []	include/DynamicArray.hpp	40-48

Option<T> и try-семантика	include/Option.hpp	1-35

TryGetFirst/TryGetLast	include/Sequence.hpp	25-38

Итераторы 	include/DynamicArray.hpp, include/LinkedList.hpp	112-155



cd /home/zx/Documents/progi/lab2
rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build .



static_cast почему индекс такого типа   


        LinkedList<T> newList;
        for (size_t i = 0; i < items->GetLength(); ++i) {
            if (static_cast<int>(i) != index) {
                newList.Append(items->Get(i));
            }


патерн mvc mvvm