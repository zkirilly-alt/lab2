#include <iostream>
#include <string>
#include <limits>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include "Functional.hpp"

using namespace std;

int safeInput() {
    int value;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите число: ";
    }
    return value;
}

void printMenu() {
    cout << "\n===== Лабораторная работа 2 =====\n";
    cout << "1. Работа с ArraySequence\n";
    cout << "2. Работа с ListSequence\n";
    cout << "3. Работа с MutableArraySequence\n";
    cout << "4. Работа с ImmutableArraySequence\n";
    cout << "5. Работа с BitSequence\n";
    cout << "6. Map операция\n";
    cout << "7. Where операция\n";
    cout << "8. Reduce операция\n";
    cout << "9. Zip операция\n";
    cout << "10. Побитовые операции AND OR XOR NOT\n";
    cout << "0. Выход\n";
    cout << "Выберите: ";
}

void printSequence(Sequence<int>* seq) {
    cout << "[";
    for (int i = 0; i < seq->GetLength(); ++i) {
        cout << seq->Get(i);
        if (i < seq->GetLength() - 1) cout << ", ";
    }
    cout << "]";
}

void arraySequenceMenu() {
    MutableArraySequence<int> seq;
    int choice, index, value;
    
    do {
        cout << "\n--- ArraySequence ---\n";
        cout << "1. Добавить в конец\n";
        cout << "2. Добавить в начало\n";
        cout << "3. Вставить по индексу\n";
        cout << "4. Получить элемент\n";
        cout << "5. Показать всю последовательность\n";
        cout << "6. Показать длину\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        choice = safeInput();
        
        switch(choice) {
            case 1:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Append(value);
                cout << "Добавлено\n";
                break;
            case 2:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Prepend(value);
                cout << "Добавлено\n";
                break;
            case 3:
                cout << "Введите индекс: ";
                index = safeInput();
                cout << "Введите значение: ";
                value = safeInput();
                try {
                    seq.InsertAt(value, index);
                    cout << "Вставлено\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 4:
                cout << "Введите индекс: ";
                index = safeInput();
                try {
                    cout << "Значение: " << seq.Get(index) << "\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 5:
                cout << "Последовательность: ";
                printSequence(&seq);
                cout << "\n";
                break;
            case 6:
                cout << "Длина: " << seq.GetLength() << "\n";
                break;
        }
    } while (choice != 0);
}

void listSequenceMenu() {
    ListSequence<int> seq;
    int choice, index, value;
    
    do {
        cout << "\n--- ListSequence ---\n";
        cout << "1. Добавить в конец\n";
        cout << "2. Добавить в начало\n";
        cout << "3. Вставить по индексу\n";
        cout << "4. Получить элемент\n";
        cout << "5. Показать всю последовательность\n";
        cout << "6. Показать длину\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        choice = safeInput();
        
        switch(choice) {
            case 1:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Append(value);
                cout << "Добавлено\n";
                break;
            case 2:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Prepend(value);
                cout << "Добавлено\n";
                break;
            case 3:
                cout << "Введите индекс: ";
                index = safeInput();
                cout << "Введите значение: ";
                value = safeInput();
                try {
                    seq.InsertAt(value, index);
                    cout << "Вставлено\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 4:
                cout << "Введите индекс: ";
                index = safeInput();
                try {
                    cout << "Значение: " << seq.Get(index) << "\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 5:
                cout << "Последовательность: ";
                printSequence(&seq);
                cout << "\n";
                break;
            case 6:
                cout << "Длина: " << seq.GetLength() << "\n";
                break;
        }
    } while (choice != 0);
}

void mutableArraySequenceMenu() {
    MutableArraySequence<int> seq;
    int choice, index, value;
    
    do {
        cout << "\n--- MutableArraySequence ---\n";
        cout << "1. Добавить в конец (Append)\n";
        cout << "2. Добавить в начало (Prepend)\n";
        cout << "3. Вставить по индексу (InsertAt)\n";
        cout << "4. Добавить mutable (AppendMutable)\n";
        cout << "5. Добавить в начало mutable (PrependMutable)\n";
        cout << "6. Показать всю последовательность\n";
        cout << "7. Показать длину\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        choice = safeInput();
        
        switch(choice) {
            case 1:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Append(value);
                cout << "Добавлено\n";
                break;
            case 2:
                cout << "Введите значение: ";
                value = safeInput();
                seq.Prepend(value);
                cout << "Добавлено\n";
                break;
            case 3:
                cout << "Введите индекс: ";
                index = safeInput();
                cout << "Введите значение: ";
                value = safeInput();
                try {
                    seq.InsertAt(value, index);
                    cout << "Вставлено\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 4:
                cout << "Введите значение: ";
                value = safeInput();
                seq.AppendMutable(value);
                cout << "Добавлено\n";
                break;
            case 5:
                cout << "Введите значение: ";
                value = safeInput();
                seq.PrependMutable(value);
                cout << "Добавлено\n";
                break;
            case 6:
                cout << "Последовательность: ";
                printSequence(&seq);
                cout << "\n";
                break;
            case 7:
                cout << "Длина: " << seq.GetLength() << "\n";
                break;
        }
    } while (choice != 0);
}

void immutableArraySequenceMenu() {
    ImmutableArraySequence<int> seq1;
    ImmutableArraySequence<int>* current = &seq1;
    int choice, index, value;
    bool needDelete = false;
    
    do {
        cout << "\n--- ImmutableArraySequence ---\n";
        cout << "1. Добавить в конец (AppendImmutable)\n";
        cout << "2. Добавить в начало (PrependImmutable)\n";
        cout << "3. Вставить по индексу (InsertAtImmutable)\n";
        cout << "4. Показать текущую последовательность\n";
        cout << "5. Показать длину\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        choice = safeInput();
        
        switch(choice) {
            case 1:
                cout << "Введите значение: ";
                value = safeInput();
                if (needDelete) delete current;
                current = current->AppendImmutable(value);
                needDelete = true;
                cout << "Добавлено. Создана новая последовательность\n";
                break;
            case 2:
                cout << "Введите значение: ";
                value = safeInput();
                if (needDelete) delete current;
                current = current->PrependImmutable(value);
                needDelete = true;
                cout << "Добавлено. Создана новая последовательность\n";
                break;
            case 3:
                cout << "Введите индекс: ";
                index = safeInput();
                cout << "Введите значение: ";
                value = safeInput();
                try {
                    if (needDelete) delete current;
                    current = current->InsertAtImmutable(value, index);
                    needDelete = true;
                    cout << "Вставлено. Создана новая последовательность\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 4:
                cout << "Последовательность: ";
                printSequence(current);
                cout << "\n";
                break;
            case 5:
                cout << "Длина: " << current->GetLength() << "\n";
                break;
        }
    } while (choice != 0);
    
    if (needDelete) delete current;
}

void bitSequenceMenu() {
    BitSequence bits;
    int choice, index;
    int bitValue;
    int size;
    
    do {
        cout << "\n--- BitSequence ---\n";
        cout << "1. Создать битовую последовательность\n";
        cout << "2. Установить бит\n";
        cout << "3. Получить бит\n";
        cout << "4. Добавить бит в конец\n";
        cout << "5. Добавить бит в начало\n";
        cout << "6. Показать всю последовательность\n";
        cout << "7. Показать длину\n";
        cout << "0. Назад\n";
        cout << "Выберите: ";
        choice = safeInput();
        
        switch(choice) {
            case 1:
                cout << "Введите размер: ";
                size = safeInput();
                bits = BitSequence(size);
                cout << "Создана битовая последовательность размером " << size << "\n";
                break;
            case 2:
                cout << "Введите индекс: ";
                index = safeInput();
                cout << "Введите значение (0 или 1): ";
                bitValue = safeInput();
                try {
                    bits.Set(index, bitValue == 1);
                    cout << "Установлено\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 3:
                cout << "Введите индекс: ";
                index = safeInput();
                try {
                    cout << "Значение: " << bits.Get(index) << "\n";
                } catch (const exception& e) {
                    cout << "Ошибка: " << e.what() << "\n";
                }
                break;
            case 4:
                cout << "Введите значение (0 или 1): ";
                bitValue = safeInput();
                bits.Append(bitValue == 1);
                cout << "Добавлено\n";
                break;
            case 5:
                cout << "Введите значение (0 или 1): ";
                bitValue = safeInput();
                bits.Prepend(bitValue == 1);
                cout << "Добавлено\n";
                break;
            case 6:
                cout << "Битовая последовательность: ";
                for (int i = 0; i < bits.GetLength(); ++i) {
                    cout << (bits.Get(i) ? "1" : "0");
                }
                cout << "\n";
                break;
            case 7:
                cout << "Длина: " << bits.GetLength() << "\n";
                break;
        }
    } while (choice != 0);
}

void demoMap() {
    int n, value;
    cout << "Введите количество элементов: ";
    n = safeInput();
    
    ArraySequence<int> seq;
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        value = safeInput();
        seq.Append(value);
    }
    
    cout << "Исходная последовательность: ";
    printSequence(&seq);
    cout << "\n";
    
    Sequence<int>* result = Functional<int, int>::Map(&seq, [](int x) { return x * x; });
    cout << "После возведения в квадрат: ";
    printSequence(result);
    cout << "\n";
    
    delete result;
}

void demoWhere() {
    int n, value;
    cout << "Введите количество элементов: ";
    n = safeInput();
    
    ArraySequence<int> seq;
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        value = safeInput();
        seq.Append(value);
    }
    
    cout << "Исходная последовательность: ";
    printSequence(&seq);
    cout << "\n";
    
    Sequence<int>* result = Functional<int, int>::Where(&seq, [](int x) { return x % 2 == 0; });
    cout << "Четные числа: ";
    printSequence(result);
    cout << "\n";
    
    delete result;
}

void demoReduce() {
    int n, value;
    cout << "Введите количество элементов: ";
    n = safeInput();
    
    ArraySequence<int> seq;
    cout << "Введите " << n << " чисел: ";
    for (int i = 0; i < n; ++i) {
        value = safeInput();
        seq.Append(value);
    }
    
    cout << "Последовательность: ";
    printSequence(&seq);
    cout << "\n";
    
    int sum = Functional<int, int>::Reduce(&seq, [](int acc, int x) { return acc + x; }, 0);
    cout << "Сумма: " << sum << "\n";
    
    int product = Functional<int, int>::Reduce(&seq, [](int acc, int x) { return acc * x; }, 1);
    cout << "Произведение: " << product << "\n";
}

void demoZip() {
    int n1, n2, value;
    
    cout << "Введите размер первой последовательности: ";
    n1 = safeInput();
    ArraySequence<int> seq1;
    cout << "Введите " << n1 << " чисел: ";
    for (int i = 0; i < n1; ++i) {
        value = safeInput();
        seq1.Append(value);
    }
    
    cout << "Введите размер второй последовательности: ";
    n2 = safeInput();
    ArraySequence<int> seq2;
    cout << "Введите " << n2 << " чисел: ";
    for (int i = 0; i < n2; ++i) {
        value = safeInput();
        seq2.Append(value);
    }
    
    cout << "Первая: ";
    printSequence(&seq1);
    cout << "\n";
    cout << "Вторая: ";
    printSequence(&seq2);
    cout << "\n";
    
    Sequence<pair<int, int>>* result = Functional<int, int>::Zip(&seq1, &seq2);
    cout << "Zip: [";
    for (int i = 0; i < result->GetLength(); ++i) {
        cout << "(" << result->Get(i).first << "," << result->Get(i).second << ")";
        if (i < result->GetLength() - 1) cout << ", ";
    }
    cout << "]\n";
    
    delete result;
}

void demoBitwiseOperations() {
    int size;
    cout << "Введите размер битовых последовательностей: ";
    size = safeInput();
    
    BitSequence a(size);
    BitSequence b(size);
    
    cout << "Введите первую битовую последовательность (" << size << " бит через пробел 0 или 1): ";
    for (int i = 0; i < size; ++i) {
        int bit = safeInput();
        a.Set(i, bit == 1);
    }
    
    cout << "Введите вторую битовую последовательность (" << size << " бит через пробел 0 или 1): ";
    for (int i = 0; i < size; ++i) {
        int bit = safeInput();
        b.Set(i, bit == 1);
    }
    
    cout << "a: ";
    for (int i = 0; i < size; ++i) cout << (a.Get(i) ? "1" : "0");
    cout << "\nb: ";
    for (int i = 0; i < size; ++i) cout << (b.Get(i) ? "1" : "0");
    
    BitSequence andResult = a & b;
    cout << "\na AND b: ";
    for (int i = 0; i < size; ++i) cout << (andResult.Get(i) ? "1" : "0");
    
    BitSequence orResult = a | b;
    cout << "\na OR b: ";
    for (int i = 0; i < size; ++i) cout << (orResult.Get(i) ? "1" : "0");
    
    BitSequence xorResult = a ^ b;
    cout << "\na XOR b: ";
    for (int i = 0; i < size; ++i) cout << (xorResult.Get(i) ? "1" : "0");
    
    BitSequence notResult = ~a;
    cout << "\nNOT a: ";
    for (int i = 0; i < size; ++i) cout << (notResult.Get(i) ? "1" : "0");
    cout << "\n";
}

int main() {
    int choice;
    
    cout << "Лабораторная работа 2\n";
    
    do {
        printMenu();
        choice = safeInput();
        
        switch(choice) {
            case 1:
                arraySequenceMenu();
                break;
            case 2:
                listSequenceMenu();
                break;
            case 3:
                mutableArraySequenceMenu();
                break;
            case 4:
                immutableArraySequenceMenu();
                break;
            case 5:
                bitSequenceMenu();
                break;
            case 6:
                demoMap();
                break;
            case 7:
                demoWhere();
                break;
            case 8:
                demoReduce();
                break;
            case 9:
                demoZip();
                break;
            case 10:
                demoBitwiseOperations();
                break;
            case 0:
                cout << "Выход\n";
                break;
            default:
                cout << "Неверный выбор\n";
                break;
        }
    } while (choice != 0);
    
    return 0;
}