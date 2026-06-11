#include <gtest/gtest.h>
#include "LinkedList.hpp"

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(LinkedListTest, DefaultConstructor) {
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0) 
        << "LinkedList(): длина должна быть 0, получено " << list.GetLength();
}

TEST_F(LinkedListTest, ConstructorFromArray) {
    int items[] = {1, 2, 3, 4, 5};
    size_t count = 5;
    LinkedList<int> list(items, count);
    
    EXPECT_EQ(list.GetLength(), count) 
        << "LinkedList(items, " << count << "): ожидалась длина " << count 
        << ", получено " << list.GetLength();
    
    EXPECT_EQ(list.GetFirst(), items[0]) 
        << "LinkedList(items, " << count << "): GetFirst() ожидался " << items[0] 
        << ", получено " << list.GetFirst();
    
    EXPECT_EQ(list.GetLast(), items[count - 1]) 
        << "LinkedList(items, " << count << "): GetLast() ожидался " << items[count - 1] 
        << ", получено " << list.GetLast();
    
    for (size_t i = 0; i < count; ++i) {
        EXPECT_EQ(list.Get(i), items[i]) 
            << "LinkedList(items, " << count << "): Get(" << i << ") ожидался " << items[i] 
            << ", получено " << list.Get(i);
    }
}

TEST_F(LinkedListTest, Append) {
    LinkedList<int> list;
    int testValues[] = {10, 20, 30};
    size_t count = 3;
    
    for (size_t i = 0; i < count; ++i) {
        list.Append(testValues[i]);
        EXPECT_EQ(list.GetLength(), i + 1) 
            << "Append(" << testValues[i] << "): после добавления длина должна быть " << (i + 1) 
            << ", получено " << list.GetLength();
        EXPECT_EQ(list.Get(i), testValues[i]) 
            << "Append(" << testValues[i] << "): элемент [" << i << "] должен быть " << testValues[i] 
            << ", получено " << list.Get(i);
    }
    
    EXPECT_EQ(list.GetFirst(), testValues[0]) 
        << "Append: GetFirst() ожидался " << testValues[0] 
        << ", получено " << list.GetFirst();
    
    EXPECT_EQ(list.GetLast(), testValues[count - 1]) 
        << "Append: GetLast() ожидался " << testValues[count - 1] 
        << ", получено " << list.GetLast();
}

TEST_F(LinkedListTest, Prepend) {
    LinkedList<int> list;
    list.Prepend(30);
    list.Prepend(20);
    list.Prepend(10);
    
    EXPECT_EQ(list.GetLength(), 3) 
        << "Prepend: ожидалась длина 3, получено " << list.GetLength();
    
    int expected[] = {10, 20, 30};
    for (size_t i = 0; i < 3; ++i) {
        EXPECT_EQ(list.Get(i), expected[i]) 
            << "Prepend: элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << list.Get(i);
    }
}

TEST_F(LinkedListTest, InsertAt) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.Append(40);
    
    list.InsertAt(20, 1);
    
    EXPECT_EQ(list.GetLength(), 4) 
        << "InsertAt(20, 1): ожидалась длина 4, получено " << list.GetLength();
    
    int expected[] = {10, 20, 30, 40};
    for (size_t i = 0; i < 4; ++i) {
        EXPECT_EQ(list.Get(i), expected[i]) 
            << "InsertAt(20, 1): элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << list.Get(i);
    }
}

TEST_F(LinkedListTest, GetFirstThrowsOnEmpty) {
    LinkedList<int> list;
    
    EXPECT_THROW({
        try {
            list.GetFirst();
        } catch (const EmptyContainerError& e) {
            EXPECT_STREQ(e.what(), "LinkedList::GetFirst: list is empty")
                << "GetFirst(): ожидалось исключение с сообщением 'LinkedList::GetFirst: list is empty'";
            throw;
        }
    }, EmptyContainerError) << "GetFirst() на пустом списке должно выбрасывать EmptyContainerError";
}

TEST_F(LinkedListTest, GetLastThrowsOnEmpty) {
    LinkedList<int> list;
    
    EXPECT_THROW({
        try {
            list.GetLast();
        } catch (const EmptyContainerError& e) {
            EXPECT_STREQ(e.what(), "LinkedList::GetLast: list is empty")
                << "GetLast(): ожидалось исключение с сообщением 'LinkedList::GetLast: list is empty'";
            throw;
        }
    }, EmptyContainerError) << "GetLast() на пустом списке должно выбрасывать EmptyContainerError";
}

TEST_F(LinkedListTest, GetThrowsOnInvalidIndex) {
    LinkedList<int> list;
    list.Append(10);
    size_t invalidIndex = 5;
    
    EXPECT_THROW({
        try {
            list.Get(invalidIndex);
        } catch (const IndexOutOfRange& e) {
            EXPECT_STREQ(e.what(), "LinkedList::getNode: index out of range")
                << "Get(" << invalidIndex << "): ожидалось исключение с сообщением 'LinkedList::getNode: index out of range'";
            throw;
        }
    }, IndexOutOfRange) << "Get(" << invalidIndex << ") должно выбрасывать IndexOutOfRange";
}