#include <gtest/gtest.h>
#include "ArraySequence.hpp"
#include "Functional.hpp"

int square(int x) {
    return x * x;
}

bool isEven(int x) {
    return x % 2 == 0;
}

int sum(int acc, int x) {
    return acc + x;
}

TEST(FunctionalTest, Map) {
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(data, 5);
    
    Sequence<int>* result = Functional<int, int>::Map(&seq, square);
    
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(1), 4);
    EXPECT_EQ(result->Get(2), 9);
    EXPECT_EQ(result->Get(3), 16);
    EXPECT_EQ(result->Get(4), 25);
    
    delete result;
}

TEST(FunctionalTest, Where) {
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ArraySequence<int> seq(data, 10);
    
    Sequence<int>* result = Functional<int, int>::Where(&seq, isEven);
    
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->Get(0), 2);
    EXPECT_EQ(result->Get(1), 4);
    EXPECT_EQ(result->Get(2), 6);
    EXPECT_EQ(result->Get(3), 8);
    EXPECT_EQ(result->Get(4), 10);
    
    delete result;
}

TEST(FunctionalTest, Reduce) {
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(data, 5);
    
    int result = Functional<int, int>::Reduce(&seq, sum, 0);
    
    EXPECT_EQ(result, 15);
}

TEST(FunctionalTest, Zip) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    ArraySequence<int> seq1(data1, 3);
    ArraySequence<int> seq2(data2, 3);
    
    Sequence<std::pair<int, int>>* result = Functional<int, int>::Zip(&seq1, &seq2);
    
    EXPECT_EQ(result->GetLength(), 3);
    EXPECT_EQ(result->Get(0).first, 1);
    EXPECT_EQ(result->Get(0).second, 4);
    EXPECT_EQ(result->Get(1).first, 2);
    EXPECT_EQ(result->Get(1).second, 5);
    EXPECT_EQ(result->Get(2).first, 3);
    EXPECT_EQ(result->Get(2).second, 6);
    
    delete result;
}

TEST(FunctionalTest, Unzip) {
    std::pair<int, int> data[] = {std::make_pair(1,4), std::make_pair(2,5), std::make_pair(3,6)};
    ArraySequence<std::pair<int, int>> seq(data, 3);
    
    auto result = Functional<int, int>::Unzip(&seq);
    
    EXPECT_EQ(result.first->GetLength(), 3);
    EXPECT_EQ(result.second->GetLength(), 3);
    EXPECT_EQ(result.first->Get(0), 1);
    EXPECT_EQ(result.first->Get(1), 2);
    EXPECT_EQ(result.first->Get(2), 3);
    EXPECT_EQ(result.second->Get(0), 4);
    EXPECT_EQ(result.second->Get(1), 5);
    EXPECT_EQ(result.second->Get(2), 6);
    
    delete result.first;
    delete result.second;
}

TEST(FunctionalTest, MapWithLambda) {
    int data[] = {1, 2, 3, 4};
    ArraySequence<int> seq(data, 4);
    
    Sequence<int>* result = Functional<int, int>::Map(&seq, [](int x) { return x * 3; });
    
    EXPECT_EQ(result->Get(0), 3);
    EXPECT_EQ(result->Get(1), 6);
    EXPECT_EQ(result->Get(2), 9);
    EXPECT_EQ(result->Get(3), 12);
    
    delete result;
}

TEST(FunctionalTest, WhereWithLambda) {
    int data[] = {1, 2, 3, 4, 5, 6};
    ArraySequence<int> seq(data, 6);
    
    Sequence<int>* result = Functional<int, int>::Where(&seq, [](int x) { return x > 3; });
    
    EXPECT_EQ(result->GetLength(), 3);
    EXPECT_EQ(result->Get(0), 4);
    EXPECT_EQ(result->Get(1), 5);
    EXPECT_EQ(result->Get(2), 6);
    
    delete result;
}

TEST(FunctionalTest, ReduceWithLambda) {
    int data[] = {1, 2, 3, 4};
    ArraySequence<int> seq(data, 4);
    
    int result = Functional<int, int>::Reduce(&seq, [](int acc, int x) { return acc * x; }, 1);
    
    EXPECT_EQ(result, 24);
}

