#include <gtest/gtest.h>
#include "ListSequence.hpp"

class ListSequenceTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ListSequenceTest, DefaultConstructor) {
    ListSequence<int> seq;
    EXPECT_EQ(seq.GetLength(), 0) 
        << "ListSequence(): длина должна быть 0, получено " << seq.GetLength();
    
    EXPECT_THROW(seq.GetFirst(), EmptyContainerError) 
        << "ListSequence(): GetFirst() на пустой последовательности должно выбрасывать EmptyContainerError";
}

TEST_F(ListSequenceTest, ConstructorFromArray) {
    int data[] = {1, 2, 3, 4, 5};
    int count = 5;
    ListSequence<int> seq(data, count);
    
    EXPECT_EQ(seq.GetLength(), count) 
        << "ListSequence(data, " << count << "): ожидалась длина " << count 
        << ", получено " << seq.GetLength();
    
    EXPECT_EQ(seq.GetFirst(), data[0]) 
        << "ListSequence(data, " << count << "): GetFirst() ожидался " << data[0] 
        << ", получено " << seq.GetFirst();
    
    EXPECT_EQ(seq.GetLast(), data[count - 1]) 
        << "ListSequence(data, " << count << "): GetLast() ожидался " << data[count - 1] 
        << ", получено " << seq.GetLast();
    
    for (int i = 0; i < count; ++i) {
        EXPECT_EQ(seq.Get(i), data[i]) 
            << "ListSequence(data, " << count << "): Get(" << i << ") ожидался " << data[i] 
            << ", получено " << seq.Get(i);
    }
}

TEST_F(ListSequenceTest, Append) {
    ListSequence<int> seq;
    int testValues[] = {10, 20, 30};
    int count = 3;
    
    for (int i = 0; i < count; ++i) {
        seq.Append(testValues[i]);
        EXPECT_EQ(seq.GetLength(), i + 1) 
            << "Append(" << testValues[i] << "): после добавления длина должна быть " << (i + 1) 
            << ", получено " << seq.GetLength();
        EXPECT_EQ(seq.Get(i), testValues[i]) 
            << "Append(" << testValues[i] << "): элемент [" << i << "] должен быть " << testValues[i] 
            << ", получено " << seq.Get(i);
    }
}

TEST_F(ListSequenceTest, Prepend) {
    ListSequence<int> seq;
    seq.Prepend(30);
    seq.Prepend(20);
    seq.Prepend(10);
    
    EXPECT_EQ(seq.GetLength(), 3) 
        << "Prepend: ожидалась длина 3, получено " << seq.GetLength();
    
    int expected[] = {10, 20, 30};
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(seq.Get(i), expected[i]) 
            << "Prepend: элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << seq.Get(i);
    }
}

TEST_F(ListSequenceTest, InsertAt) {
    ListSequence<int> seq;
    seq.Append(10);
    seq.Append(30);
    seq.Append(40);
    seq.InsertAt(20, 1);
    
    EXPECT_EQ(seq.GetLength(), 4) 
        << "InsertAt(20, 1): ожидалась длина 4, получено " << seq.GetLength();
    
    int expected[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(seq.Get(i), expected[i]) 
            << "InsertAt(20, 1): элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << seq.Get(i);
    }
}

TEST_F(ListSequenceTest, InsertAtInvalidIndex) {
    ListSequence<int> seq;
    seq.Append(10);
    seq.Append(20);
    
    int invalidIndex = 5;
    int value = 99;
    
    EXPECT_THROW({
        try {
            seq.InsertAt(value, invalidIndex);
        } catch (const IndexOutOfRange& e) {
            EXPECT_STREQ(e.what(), "")
                << "InsertAt(" << value << ", " << invalidIndex << "): ожидалось исключение 'ListSequence: insert index out of range'";
            throw;
        }
    }, IndexOutOfRange) << "InsertAt(" << value << ", " << invalidIndex << ") должно выбрасывать IndexOutOfRange";
}

TEST_F(ListSequenceTest, GetInvalidIndex) {
    int data[] = {1, 2, 3};
    ListSequence<int> seq(data, 3);
    int invalidIndex = 5;
    
    EXPECT_THROW({
        try {
            seq.Get(invalidIndex);
        } catch (const IndexOutOfRange& e) {
            EXPECT_STREQ(e.what(), "")
                << "Get(" << invalidIndex << "): ожидалось исключение 'ListSequence: index out of range'";
            throw;
        }
    }, IndexOutOfRange) << "Get(" << invalidIndex << ") должно выбрасывать IndexOutOfRange";
}

TEST_F(ListSequenceTest, GetSubsequence) {
    int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ListSequence<int> seq(data, 10);
    
    Sequence<int>* subseq = seq.GetSubsequence(2, 6);
    
    EXPECT_EQ(subseq->GetLength(), 5) 
        << "GetSubsequence(2,6): ожидалась длина 5, получено " << subseq->GetLength();
    
    int expected[] = {2, 3, 4, 5, 6};
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(subseq->Get(i), expected[i]) 
            << "GetSubsequence(2,6): элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << subseq->Get(i);
    }
    
    delete subseq;
}

TEST_F(ListSequenceTest, Concat) {
    int data1[] = {1, 2, 3};
    int data2[] = {4, 5, 6};
    ListSequence<int> seq1(data1, 3);
    ListSequence<int> seq2(data2, 3);
    
    Sequence<int>* result = seq1.Concat(seq2);
    
    EXPECT_EQ(result->GetLength(), 5) 
        << "Concat: ожидалась длина 6, получено " << result->GetLength();
    
    int expected[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < 6; ++i) {
        EXPECT_EQ(result->Get(i), expected[i]) 
            << "Concat: элемент [" << i << "] ожидался " << expected[i] 
            << ", получено " << result->Get(i);
    }
    
    delete result;
}

TEST_F(ListSequenceTest, GetFirstThrowsOnEmpty) {
    ListSequence<int> seq;
    
    EXPECT_THROW({
        try {
            seq.GetFirst();
        } catch (const EmptyContainerError& e) {
            EXPECT_STREQ(e.what(), "ListSequence::GetFirst: последовательность пуста")
                << "GetFirst(): ожидалось исключение 'ListSequence: последовательность пуста'";
            throw;
        }
    }, EmptyContainerError) << "GetFirst() на пустой последовательности должно выбрасывать EmptyContainerError";
}

TEST_F(ListSequenceTest, GetLastThrowsOnEmpty) {
    ListSequence<int> seq;
    
    EXPECT_THROW({
        try {
            seq.GetLast();
        } catch (const EmptyContainerError& e) {
            EXPECT_STREQ(e.what(), "ListSequence::GetFirst: последовательность пуста")
                << "GetLast(): ожидалось исключение 'ListSequence: последовательность пуста'";
            throw;
        }
    }, EmptyContainerError) << "GetLast() на пустой последовательности должно выбрасывать EmptyContainerError";
}