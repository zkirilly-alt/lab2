#include <gtest/gtest.h>
#include "ListSequence.hpp"

TEST(ListSequenceTest, DefaultConstructor) {
    ListSequence<int> seq;
    EXPECT_EQ(seq.GetLength(), 0);
    EXPECT_THROW(seq.GetFirst(), EmptyContainerError);
}

TEST(ListSequenceTest, ConstructorFromArray) {
    int data[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(data, 5);
    
    EXPECT_EQ(seq.GetLength(), 5);
    EXPECT_EQ(seq.GetFirst(), 1);
    EXPECT_EQ(seq.GetLast(), 5);
    EXPECT_EQ(seq.Get(0), 1);
    EXPECT_EQ(seq.Get(2), 3);
}

TEST(ListSequenceTest, CopyConstructor) {
    int data[] = {10, 20, 30};
    ListSequence<int> seq1(data, 3);
    ListSequence<int> seq2(seq1);
    
    EXPECT_EQ(seq2.GetLength(), 3);
    EXPECT_EQ(seq2.Get(0), 10);
    EXPECT_EQ(seq2.Get(1), 20);
    EXPECT_EQ(seq2.Get(2), 30);
}

TEST(ListSequenceTest, Append) {
    ListSequence<int> seq;
    seq.Append(10);
    seq.Append(20);
    seq.Append(30);
    
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 10);
    EXPECT_EQ(seq.GetLast(), 30);
    EXPECT_EQ(seq.Get(1), 20);
}

TEST(ListSequenceTest, Prepend) {
    ListSequence<int> seq;
    seq.Prepend(30);
    seq.Prepend(20);
    seq.Prepend(10);
    
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 10);
    EXPECT_EQ(seq.GetLast(), 30);
    EXPECT_EQ(seq.Get(1), 20);
}

TEST(ListSequenceTest, InsertAt) {
    ListSequence<int> seq;
    seq.Append(10);
    seq.Append(30);
    seq.Append(40);
    seq.InsertAt(20, 1);
    
    EXPECT_EQ(seq.GetLength(), 4);
    EXPECT_EQ(seq.Get(0), 10);
    EXPECT_EQ(seq.Get(1), 20);
    EXPECT_EQ(seq.Get(2), 30);
    EXPECT_EQ(seq.Get(3), 40);
}

TEST(ListSequenceTest, InsertAtBeginning) {
    ListSequence<int> seq;
    seq.Append(20);
    seq.Append(30);
    seq.InsertAt(10, 0);
    
    EXPECT_EQ(seq.GetFirst(), 10);
    EXPECT_EQ(seq.GetLength(), 3);
}

TEST(ListSequenceTest, InsertAtEnd) {
    ListSequence<int> seq;
    seq.Append(10);
    seq.Append(20);
    seq.InsertAt(30, 2);
    
    EXPECT_EQ(seq.GetLast(), 30);
    EXPECT_EQ(seq.GetLength(), 3);
}

TEST(ListSequenceTest, InsertAtThrowsOnInvalidIndex) {
    ListSequence<int> seq;
    seq.Append(10);
    EXPECT_THROW(seq.InsertAt(20, 5), IndexOutOfRange);
    EXPECT_THROW(seq.InsertAt(20, -1), IndexOutOfRange);
}

TEST(ListSequenceTest, GetSubsequence) {
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ListSequence<int> seq(data, 10);
    
    Sequence<int>* subseq = seq.GetSubsequence(2, 6);
    
    EXPECT_EQ(subseq->GetLength(), 5);
    EXPECT_EQ(subseq->Get(0), 2);
    EXPECT_EQ(subseq->Get(1), 3);
    EXPECT_EQ(subseq->Get(2), 4);
    EXPECT_EQ(subseq->Get(3), 5);
    EXPECT_EQ(subseq->Get(4), 6);
    
    delete subseq;
}

TEST(ListSequenceTest, GetSubsequenceThrowsOnInvalidIndices) {
    int data[] = {1, 2, 3};
    ListSequence<int> seq(data, 3);
    
    EXPECT_THROW(seq.GetSubsequence(2, 1), InvalidArgumentError);
    EXPECT_THROW(seq.GetSubsequence(0, 3), IndexOutOfRange);
    EXPECT_THROW(seq.GetSubsequence(-1, 2), IndexOutOfRange);
}

TEST(ListSequenceTest, Concat) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    ListSequence<int> seq1(data1, 3);
    ListSequence<int> seq2(data2, 3);
    
    Sequence<int>* result = seq1.Concat(seq2);
    
    EXPECT_EQ(result->GetLength(), 6);
    EXPECT_EQ(result->Get(0), 1);
    EXPECT_EQ(result->Get(2), 3);
    EXPECT_EQ(result->Get(3), 4);
    EXPECT_EQ(result->Get(5), 6);
    
    delete result;
}

TEST(ListSequenceTest, GetThrowsOnInvalidIndex) {
    int data[] = {1, 2, 3};
    ListSequence<int> seq(data, 3);
    
    EXPECT_THROW(seq.Get(3), IndexOutOfRange);
    EXPECT_THROW(seq.Get(-1), IndexOutOfRange);
}