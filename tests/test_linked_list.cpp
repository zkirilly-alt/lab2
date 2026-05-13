#include <gtest/gtest.h>
#include "LinkedList.hpp"

TEST(LinkedListTest, DefaultConstructor) {
    LinkedList<int> list;
    EXPECT_EQ(list.GetLength(), 0);
}

TEST(LinkedListTest, ConstructorFromArray) {
    int items[] = {1, 2, 3, 4, 5};
    LinkedList<int> list(items, 5);
    
    EXPECT_EQ(list.GetLength(), 5);
    EXPECT_EQ(list.GetFirst(), 1);
    EXPECT_EQ(list.GetLast(), 5);
    EXPECT_EQ(list.Get(0), 1);
    EXPECT_EQ(list.Get(2), 3);
    EXPECT_EQ(list.Get(4), 5);
}

TEST(LinkedListTest, CopyConstructor) {
    int items[] = {10, 20, 30};
    LinkedList<int> list(items, 3);
    LinkedList<int> copy(list);
    
    EXPECT_EQ(copy.GetLength(), 3);
    EXPECT_EQ(copy.Get(0), 10);
    EXPECT_EQ(copy.Get(1), 20);
    EXPECT_EQ(copy.Get(2), 30);
}

TEST(LinkedListTest, Append) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.Append(30);
    
    EXPECT_EQ(list.GetLength(), 3);
    EXPECT_EQ(list.GetFirst(), 10);
    EXPECT_EQ(list.GetLast(), 30);
    EXPECT_EQ(list.Get(0), 10);
    EXPECT_EQ(list.Get(1), 20);
    EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, Prepend) {
    LinkedList<int> list;
    list.Prepend(30);
    list.Prepend(20);
    list.Prepend(10);
    
    EXPECT_EQ(list.GetLength(), 3);
    EXPECT_EQ(list.GetFirst(), 10);
    EXPECT_EQ(list.GetLast(), 30);
    EXPECT_EQ(list.Get(0), 10);
    EXPECT_EQ(list.Get(1), 20);
    EXPECT_EQ(list.Get(2), 30);
}

TEST(LinkedListTest, InsertAt) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(30);
    list.Append(40);
    list.InsertAt(20, 1);
    
    EXPECT_EQ(list.GetLength(), 4);
    EXPECT_EQ(list.Get(0), 10);
    EXPECT_EQ(list.Get(1), 20);
    EXPECT_EQ(list.Get(2), 30);
    EXPECT_EQ(list.Get(3), 40);
}

TEST(LinkedListTest, InsertAtBeginning) {
    LinkedList<int> list;
    list.Append(20);
    list.Append(30);
    list.InsertAt(10, 0);
    
    EXPECT_EQ(list.GetFirst(), 10);
    EXPECT_EQ(list.GetLength(), 3);
}

TEST(LinkedListTest, InsertAtEnd) {
    LinkedList<int> list;
    list.Append(10);
    list.Append(20);
    list.InsertAt(30, 2);
    
    EXPECT_EQ(list.GetLast(), 30);
    EXPECT_EQ(list.GetLength(), 3);
}

TEST(LinkedListTest, InsertAtThrowsOnInvalidIndex) {
    LinkedList<int> list;
    list.Append(10);
    EXPECT_THROW(list.InsertAt(20, 5), IndexOutOfRange);
}

TEST(LinkedListTest, GetSubList) {
    int items[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    LinkedList<int> list(items, 10);
    
    auto sublist = list.GetSubList(2, 6);
    EXPECT_EQ(sublist.GetLength(), 5);
    EXPECT_EQ(sublist.Get(0), 2);
    EXPECT_EQ(sublist.Get(1), 3);
    EXPECT_EQ(sublist.Get(2), 4);
    EXPECT_EQ(sublist.Get(3), 5);
    EXPECT_EQ(sublist.Get(4), 6);
}

TEST(LinkedListTest, GetSubListThrowsOnInvalidIndices) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    
    EXPECT_THROW(list.GetSubList(2, 1), IndexOutOfRange);  // start > end
    EXPECT_THROW(list.GetSubList(0, 3), IndexOutOfRange);  // end >= length
}

TEST(LinkedListTest, Concat) {
    int items1[] = {1, 2, 3};
    int items2[] = {4, 5, 6};
    LinkedList<int> list1(items1, 3);
    LinkedList<int> list2(items2, 3);
    
    auto result = list1.Concat(list2);
    EXPECT_EQ(result.GetLength(), 6);
    EXPECT_EQ(result.Get(0), 1);
    EXPECT_EQ(result.Get(2), 3);
    EXPECT_EQ(result.Get(3), 4);
    EXPECT_EQ(result.Get(5), 6);
}

TEST(LinkedListTest, GetFirstThrowsOnEmpty) {
    LinkedList<int> list;
    EXPECT_THROW(list.GetFirst(), EmptyContainerError);
}

TEST(LinkedListTest, GetLastThrowsOnEmpty) {
    LinkedList<int> list;
    EXPECT_THROW(list.GetLast(), EmptyContainerError);
}

TEST(LinkedListTest, GetThrowsOnInvalidIndex) {
    LinkedList<int> list;
    list.Append(10);
    EXPECT_THROW(list.Get(1), IndexOutOfRange);
    EXPECT_THROW(list.Get(5), IndexOutOfRange);
}

TEST(LinkedListTest, Clear) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    list.Clear();
    
    EXPECT_EQ(list.GetLength(), 0);
    EXPECT_THROW(list.GetFirst(), EmptyContainerError);
}

TEST(LinkedListTest, AssignmentOperator) {
    int items[] = {1, 2, 3};
    LinkedList<int> list(items, 3);
    LinkedList<int> list2;
    list2 = list;
    
    EXPECT_EQ(list2.GetLength(), 3);
    EXPECT_EQ(list2.Get(0), 1);
    EXPECT_EQ(list2.Get(1), 2);
    EXPECT_EQ(list2.Get(2), 3);
}