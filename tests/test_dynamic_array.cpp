#include <gtest/gtest.h>
#include "DynamicArray.hpp"

class DynamicArrayTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.GetSize(), 0) << "DynamicArray(): размер должен быть 0, получено " << arr.GetSize();
}

TEST_F(DynamicArrayTest, ConstructorWithSize) {
    size_t expectedSize = 5;
    DynamicArray<int> arr(expectedSize);
    EXPECT_EQ(arr.GetSize(), expectedSize)
        << "DynamicArray(" << expectedSize << "): ожидался размер " << expectedSize
        << ", получено " << arr.GetSize();
    for (size_t i = 0; i < expectedSize; ++i) {
        EXPECT_EQ(arr[i], 0)
            << "DynamicArray(" << expectedSize << "): элемент [" << i << "] ожидался 0, получено " << arr[i];
    }
}

TEST_F(DynamicArrayTest, ConstructorFromArray) {
    int items[] = {1, 2, 3, 4, 5};
    size_t count = 5;
    DynamicArray<int> arr(items, count);
    EXPECT_EQ(arr.GetSize(), count)
        << "DynamicArray(items, " << count << "): ожидался размер " << count
        << ", получено " << arr.GetSize();
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(arr[i], items[i])
            << "DynamicArray(items, " << count << "): элемент [" << i << "] ожидался " << items[i]
            << ", получено " << arr[i];
    }
}

TEST_F(DynamicArrayTest, CopyConstructor) {
    int items[] = {10, 20, 30};
    size_t count = 3;
    DynamicArray<int> arr(items, count);
    DynamicArray<int> copy(arr);
    EXPECT_EQ(copy.GetSize(), arr.GetSize())
        << "CopyConstructor: ожидался размер " << arr.GetSize()
        << ", получено " << copy.GetSize();
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(copy[i], items[i])
            << "CopyConstructor: элемент [" << i << "] ожидался " << items[i]
            << ", получено " << copy[i];
    }
    copy[0] = 999;
    EXPECT_EQ(arr[0], items[0])
        << "CopyConstructor: изменение копии не должно влиять на оригинал. Оригинал[0]="
        << arr[0] << ", ожидался " << items[0];
}

TEST_F(DynamicArrayTest, GetAndSet) {
    DynamicArray<int> arr(3);
    int testValues[] = {100, 200, 300};
    for (size_t i = 0; i < 3; ++i) {
        arr.Set(i, testValues[i]);
        EXPECT_EQ(arr.Get(i), testValues[i])
            << "Set/Get: после Set(" << i << ", " << testValues[i]
            << "), Get(" << i << ") вернул " << arr.Get(i);
    }
}

TEST_F(DynamicArrayTest, GetThrowsOnInvalidIndex) {
    DynamicArray<int> arr(3);
    size_t invalidIndex = 5;
    EXPECT_THROW(arr.Get(invalidIndex), IndexOutOfRange)
        << "Get(" << invalidIndex << "): должно выбрасывать IndexOutOfRange";
}

TEST_F(DynamicArrayTest, SetThrowsOnInvalidIndex) {
    DynamicArray<int> arr(3);
    size_t invalidIndex = 5;
    int value = 42;
    EXPECT_THROW(arr.Set(invalidIndex, value), IndexOutOfRange)
        << "Set(" << invalidIndex << ", " << value << "): должно выбрасывать IndexOutOfRange";
}

TEST_F(DynamicArrayTest, Append) {
    DynamicArray<int> arr;
    int testValues[] = {10, 20, 30};
    size_t count = 3;
    for (size_t i = 0; i < count; ++i) {
        arr.Append(testValues[i]);
        EXPECT_EQ(arr.GetSize(), i + 1)
            << "Append(" << testValues[i] << "): после добавления размер должен быть " << (i + 1)
            << ", получено " << arr.GetSize();
        EXPECT_EQ(arr[i], testValues[i])
            << "Append(" << testValues[i] << "): элемент [" << i << "] должен быть " << testValues[i]
            << ", получено " << arr[i];
    }
}

TEST_F(DynamicArrayTest, ResizeToLarger) {
    DynamicArray<int> arr(3);
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    size_t newSize = 5;
    arr.Resize(newSize);
    EXPECT_EQ(arr.GetSize(), newSize)
        << "Resize(" << newSize << "): ожидался размер " << newSize
        << ", получено " << arr.GetSize();
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(arr[i], i + 1)
            << "Resize(" << newSize << "): элемент [" << i << "] должен быть " << (i + 1)
            << ", получено " << arr[i];
    }
}

TEST_F(DynamicArrayTest, ResizeToSmaller) {
    DynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i * 10;
    size_t newSize = 3;
    arr.Resize(newSize);
    EXPECT_EQ(arr.GetSize(), newSize)
        << "Resize(" << newSize << "): ожидался размер " << newSize
        << ", получено " << arr.GetSize();
    for (size_t i = 0; i < newSize; ++i) {
        int expected = i * 10;
        EXPECT_EQ(arr[i], expected)
            << "Resize(" << newSize << "): элемент [" << i << "] должен быть " << expected
            << ", получено " << arr[i];
    }
    EXPECT_THROW(arr.Get(3), IndexOutOfRange)
        << "Resize(" << newSize << "): доступ к элементу [3] должен выбрасывать IndexOutOfRange";
}

TEST_F(DynamicArrayTest, Clear) {
    DynamicArray<int> arr(5);
    arr.Clear();
    EXPECT_EQ(arr.GetSize(), 0) << "Clear: размер должен быть 0, получено " << arr.GetSize();
}

TEST_F(DynamicArrayTest, AssignmentOperator) {
    int items[] = {1, 2, 3};
    size_t count = 3;
    DynamicArray<int> arr(items, count);
    DynamicArray<int> arr2;
    arr2 = arr;
    EXPECT_EQ(arr2.GetSize(), count)
        << "AssignmentOperator: ожидался размер " << count
        << ", получено " << arr2.GetSize();
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(arr2[i], items[i])
            << "AssignmentOperator: элемент [" << i << "] ожидался " << items[i]
            << ", получено " << arr2[i];
    }
}

TEST_F(DynamicArrayTest, SelfAssignment) {
    DynamicArray<int> arr(5);
    arr = arr;
    EXPECT_EQ(arr.GetSize(), 5) << "SelfAssignment: размер должен остаться 5, получено " << arr.GetSize();
}