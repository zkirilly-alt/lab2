#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.GetSize(), 0);
    EXPECT_EQ(arr.GetCapacity(), 0);
}

TEST(DynamicArrayTest, ConstructorWithSize) {
    DynamicArray<int> arr(5);
    EXPECT_EQ(arr.GetSize(), 5);
    EXPECT_EQ(arr.GetCapacity(), 5);
    
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
}

TEST(DynamicArrayTest, ConstructorFromArray) {
    int items[] = {1, 2, 3, 4, 5};
    DynamicArray<int> arr(items, 5);
    
    EXPECT_EQ(arr.GetSize(), 5);
    for (size_t i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], items[i]);
    }
}

TEST(DynamicArrayTest, CopyConstructor) {
    int items[] = {10, 20, 30};
    DynamicArray<int> arr(items, 3);
    DynamicArray<int> copy(arr);
    
    EXPECT_EQ(copy.GetSize(), 3);
    EXPECT_EQ(copy[0], 10);
    EXPECT_EQ(copy[1], 20);
    EXPECT_EQ(copy[2], 30);
    
    copy[0] = 999;
    EXPECT_EQ(arr[0], 10);
}

TEST(DynamicArrayTest, GetAndSet) {
    DynamicArray<int> arr(3);
    arr.Set(0, 100);
    arr.Set(1, 200);
    arr.Set(2, 300);
    
    EXPECT_EQ(arr.Get(0), 100);
    EXPECT_EQ(arr.Get(1), 200);
    EXPECT_EQ(arr.Get(2), 300);
}

TEST(DynamicArrayTest, GetThrowsOnInvalidIndex) {
    DynamicArray<int> arr(3);
    EXPECT_THROW(arr.Get(5), IndexOutOfRange);
    EXPECT_THROW(arr.Get(3), IndexOutOfRange);
}

TEST(DynamicArrayTest, SetThrowsOnInvalidIndex) {
    DynamicArray<int> arr(3);
    EXPECT_THROW(arr.Set(5, 42), IndexOutOfRange);
}

TEST(DynamicArrayTest, Append) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    
    EXPECT_EQ(arr.GetSize(), 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(DynamicArrayTest, AppendExpandsCapacity) {
    DynamicArray<int> arr;
    size_t initialCapacity = arr.GetCapacity();
    
    for (int i = 0; i < 10; ++i) {
        arr.Append(i);
    }
    
    EXPECT_GE(arr.GetCapacity(), initialCapacity);
    EXPECT_EQ(arr.GetSize(), 10);
}

TEST(DynamicArrayTest, ResizeToLarger) {
    DynamicArray<int> arr(3);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    arr.Resize(5);
    EXPECT_EQ(arr.GetSize(), 5);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
}

TEST(DynamicArrayTest, ResizeToSmaller) {
    DynamicArray<int> arr(5);
    for (int i = 0; i < 5; ++i) arr[i] = i * 10;
    
    arr.Resize(3);
    EXPECT_EQ(arr.GetSize(), 3);
    EXPECT_EQ(arr[0], 0);
    EXPECT_EQ(arr[1], 10);
    EXPECT_EQ(arr[2], 20);
    
    EXPECT_THROW(arr.Get(3), IndexOutOfRange);
}

TEST(DynamicArrayTest, Clear) {
    DynamicArray<int> arr(5);
    arr.Clear();
    EXPECT_EQ(arr.GetSize(), 0);
}

TEST(DynamicArrayTest, AssignmentOperator) {
    int items[] = {1, 2, 3};
    DynamicArray<int> arr(items, 3);
    DynamicArray<int> arr2;
    arr2 = arr;
    
    EXPECT_EQ(arr2.GetSize(), 3);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
    EXPECT_EQ(arr2[2], 3);
}

TEST(DynamicArrayTest, SelfAssignment) {
    DynamicArray<int> arr(5);
    arr = arr;
    EXPECT_EQ(arr.GetSize(), 5);
}