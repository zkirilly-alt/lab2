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




Использование копии по умолчанию или перемещения для класса в иерархии обычно Катастрофа: давая только указатель на базу, мы просто не знаем, что членов производного класса есть, поэтому мы не можем знать, как копировать Они. Итак, лучшее, что можно сделать, это удалить копию по умолчанию и перемещать операции, то есть устранять определения по умолчанию Эти две операции:

class Shape {
public:
  Shape(const Shape&) =delete; // no copy operations
  Shape& operator=(const Shape&) =delete;

  Shape(Shape&&) =delete; // no move operations
  Shape& operator=(Shape&&) =delete;
  ˜Shape();
    // ...
};

Теперь попытка скопировать Форму будет поймана компилятором.

The =deleteмеханизм общий, то есть его можно использовать для подавления любой операции







 57

This excerpt from The C++ Programming Language [4th Edition] - Bjarne Stroustrup book talks about the real purpose behind using =delete:

    3.3.4 Suppressing Operations

    Using the default copy or move for a class in a hierarchy is typically a disaster: given only a pointer to a base, we simply don’t know what members the derived class has, so we can’t know how to copy them. So, the best thing to do is usually to delete the default copy and move operations, that is, to eliminate the default definitions of those two operations:

    class Shape {
    public:
      Shape(const Shape&) =delete; // no copy operations
      Shape& operator=(const Shape&) =delete;

      Shape(Shape&&) =delete; // no move operations
      Shape& operator=(Shape&&) =delete;
      ˜Shape();
        // ...
    };

    Now an attempt to copy a Shape will be caught by the compiler.

    The =delete mechanism is general, that is, it can be used to suppress any operation




