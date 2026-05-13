#include <gtest/gtest.h>
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"

TEST(MutableArraySequenceTest, AppendModifiesOriginal) {
    MutableArraySequence<int> seq;
    seq.Append(10);
    seq.Append(20);
    
    EXPECT_EQ(seq.GetLength(), 2);
    EXPECT_EQ(seq.Get(0), 10);
    EXPECT_EQ(seq.Get(1), 20);
    
    seq.AppendMutable(30);
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.Get(2), 30);
}

TEST(MutableArraySequenceTest, PrependModifiesOriginal) {
    MutableArraySequence<int> seq;
    seq.Append(20);
    seq.Append(30);
    seq.PrependMutable(10);
    
    EXPECT_EQ(seq.GetLength(), 3);
    EXPECT_EQ(seq.GetFirst(), 10);
}

TEST(ImmutableArraySequenceTest, AppendReturnsNewSequence) {
    ImmutableArraySequence<int> seq1;
    seq1.Append(10);
    seq1.Append(20);
    
    ImmutableArraySequence<int>* seq2 = seq1.AppendImmutable(30);
    
    EXPECT_EQ(seq1.GetLength(), 2);
    EXPECT_EQ(seq1.Get(0), 10);
    EXPECT_EQ(seq1.Get(1), 20);
    
    EXPECT_EQ(seq2->GetLength(), 3);
    EXPECT_EQ(seq2->Get(0), 10);
    EXPECT_EQ(seq2->Get(1), 20);
    EXPECT_EQ(seq2->Get(2), 30);
    
    delete seq2;
}

TEST(ImmutableArraySequenceTest, PrependReturnsNewSequence) {
    ImmutableArraySequence<int> seq1;
    seq1.Append(20);
    seq1.Append(30);
    
    ImmutableArraySequence<int>* seq2 = seq1.PrependImmutable(10);
    
    EXPECT_EQ(seq1.GetLength(), 2);
    EXPECT_EQ(seq1.GetFirst(), 20);
    
    EXPECT_EQ(seq2->GetLength(), 3);
    EXPECT_EQ(seq2->GetFirst(), 10);
    
    delete seq2;
}

TEST(ImmutableArraySequenceTest, InsertAtReturnsNewSequence) {
    ImmutableArraySequence<int> seq1;
    seq1.Append(10);
    seq1.Append(30);
    
    ImmutableArraySequence<int>* seq2 = seq1.InsertAtImmutable(20, 1);
    
    EXPECT_EQ(seq1.GetLength(), 2);
    EXPECT_EQ(seq1.Get(0), 10);
    EXPECT_EQ(seq1.Get(1), 30);
    
    EXPECT_EQ(seq2->GetLength(), 3);
    EXPECT_EQ(seq2->Get(0), 10);
    EXPECT_EQ(seq2->Get(1), 20);
    EXPECT_EQ(seq2->Get(2), 30);
    
    delete seq2;
}

TEST(ImmutableArraySequenceTest, MultipleOperations) {
    ImmutableArraySequence<int> seq1;
    seq1.Append(10);
    
    ImmutableArraySequence<int>* seq2 = seq1.AppendImmutable(20);
    ImmutableArraySequence<int>* seq3 = seq2->PrependImmutable(5);
    ImmutableArraySequence<int>* seq4 = seq3->InsertAtImmutable(15, 2);
    
    EXPECT_EQ(seq1.GetLength(), 1);
    EXPECT_EQ(seq2->GetLength(), 2);
    EXPECT_EQ(seq3->GetLength(), 3);
    EXPECT_EQ(seq4->GetLength(), 4);
    
    EXPECT_EQ(seq4->Get(0), 5);
    EXPECT_EQ(seq4->Get(1), 10);
    EXPECT_EQ(seq4->Get(2), 15);
    EXPECT_EQ(seq4->Get(3), 20);
    
    delete seq2;
    delete seq3;
    delete seq4;
}