#include <gtest/gtest.h>
#include "BitSequence.hpp"

TEST(BitSequenceTest, DefaultConstructor) {
    BitSequence bits;
    EXPECT_EQ(bits.GetLength(), 0);
    EXPECT_THROW(bits.GetFirst(), EmptyContainerError);
}

TEST(BitSequenceTest, ConstructorWithSize) {
    BitSequence bits(10);
    EXPECT_EQ(bits.GetLength(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(bits.Get(i), false);
    }
}

TEST(BitSequenceTest, ConstructorFromArray) {
    bool init[] = {true, false, true, false, true};
    BitSequence bits(init, 5);
    
    EXPECT_EQ(bits.GetLength(), 5);
    EXPECT_EQ(bits.Get(0), true);
    EXPECT_EQ(bits.Get(1), false);
    EXPECT_EQ(bits.Get(2), true);
    EXPECT_EQ(bits.Get(3), false);
    EXPECT_EQ(bits.Get(4), true);
}

TEST(BitSequenceTest, SetAndGet) {
    BitSequence bits(8);
    bits.Set(0, true);
    bits.Set(3, true);
    bits.Set(7, true);
    
    EXPECT_EQ(bits.Get(0), true);
    EXPECT_EQ(bits.Get(1), false);
    EXPECT_EQ(bits.Get(2), false);
    EXPECT_EQ(bits.Get(3), true);
    EXPECT_EQ(bits.Get(4), false);
    EXPECT_EQ(bits.Get(5), false);
    EXPECT_EQ(bits.Get(6), false);
    EXPECT_EQ(bits.Get(7), true);
}

TEST(BitSequenceTest, Append) {
    BitSequence bits;
    bits.Append(true);
    bits.Append(false);
    bits.Append(true);
    
    EXPECT_EQ(bits.GetLength(), 3);
    EXPECT_EQ(bits.Get(0), true);
    EXPECT_EQ(bits.Get(1), false);
    EXPECT_EQ(bits.Get(2), true);
}

TEST(BitSequenceTest, Prepend) {
    BitSequence bits;
    bits.Append(false);
    bits.Append(false);
    bits.Prepend(true);
    
    EXPECT_EQ(bits.GetLength(), 3);
    EXPECT_EQ(bits.Get(0), true);
    EXPECT_EQ(bits.Get(1), false);
    EXPECT_EQ(bits.Get(2), false);
}

TEST(BitSequenceTest, InsertAt) {
    BitSequence bits(3);
    bits.Set(0, true);
    bits.Set(1, false);
    bits.Set(2, true);
    
    bits.InsertAt(false, 2);
    
    EXPECT_EQ(bits.GetLength(), 4);
    EXPECT_EQ(bits.Get(0), true);
    EXPECT_EQ(bits.Get(1), false);
    EXPECT_EQ(bits.Get(2), false);
    EXPECT_EQ(bits.Get(3), true);
}

TEST(BitSequenceTest, AndOperation) {
    BitSequence a(5);
    BitSequence b(5);
    
    a.Set(0, true); a.Set(2, true); a.Set(4, true);
    b.Set(1, true); b.Set(2, true); b.Set(3, true);
    
    BitSequence result = a & b;
    
    EXPECT_EQ(result.Get(0), false);
    EXPECT_EQ(result.Get(1), false);
    EXPECT_EQ(result.Get(2), true);
    EXPECT_EQ(result.Get(3), false);
    EXPECT_EQ(result.Get(4), false);
}

TEST(BitSequenceTest, OrOperation) {
    BitSequence a(5);
    BitSequence b(5);
    
    a.Set(0, true);
    b.Set(4, true);
    
    BitSequence result = a | b;
    
    EXPECT_EQ(result.Get(0), true);
    EXPECT_EQ(result.Get(4), true);
}

TEST(BitSequenceTest, XorOperation) {
    BitSequence a(3);
    BitSequence b(3);
    
    a.Set(0, true); a.Set(1, true);
    b.Set(1, true); b.Set(2, true);
    
    BitSequence result = a ^ b;
    
    EXPECT_EQ(result.Get(0), true);
    EXPECT_EQ(result.Get(1), false);
    EXPECT_EQ(result.Get(2), true);
}

TEST(BitSequenceTest, NotOperation) {
    BitSequence a(4);
    a.Set(0, true);
    a.Set(2, true);
    
    BitSequence result = ~a;
    
    EXPECT_EQ(result.Get(0), false);
    EXPECT_EQ(result.Get(1), true);
    EXPECT_EQ(result.Get(2), false);
    EXPECT_EQ(result.Get(3), true);
}

TEST(BitSequenceTest, CompoundAssignment) {
    BitSequence a(4);
    BitSequence b(4);
    
    a.Set(0, true); a.Set(2, true);
    b.Set(1, true); b.Set(2, true);
    
    a &= b;
    
    EXPECT_EQ(a.Get(0), false);
    EXPECT_EQ(a.Get(1), false);
    EXPECT_EQ(a.Get(2), true);
    EXPECT_EQ(a.Get(3), false);
}

TEST(BitSequenceTest, AndThrowsOnSizeMismatch) {
    BitSequence a(5);
    BitSequence b(3);
    
    EXPECT_THROW(a & b, LengthMismatchException);
}

TEST(BitSequenceTest, GetSubsequence) {
    BitSequence bits(10);
    bits.Set(2, true);
    bits.Set(5, true);
    bits.Set(8, true);
    
    Sequence<bool>* subseq = bits.GetSubsequence(2, 6);
    
    EXPECT_EQ(subseq->GetLength(), 5);
    EXPECT_EQ(subseq->Get(0), true);
    EXPECT_EQ(subseq->Get(1), false);
    EXPECT_EQ(subseq->Get(2), false);
    EXPECT_EQ(subseq->Get(3), true);
    EXPECT_EQ(subseq->Get(4), false);
    
    delete subseq;
}

TEST(BitSequenceTest, Concat) {
    BitSequence a(2);
    BitSequence b(3);
    
    a.Set(0, true); a.Set(1, false);
    b.Set(0, true); b.Set(1, true); b.Set(2, false);
    
    Sequence<bool>* result = a.Concat(b);
    
    EXPECT_EQ(result->GetLength(), 5);
    EXPECT_EQ(result->Get(0), true);
    EXPECT_EQ(result->Get(1), false);
    EXPECT_EQ(result->Get(2), true);
    EXPECT_EQ(result->Get(3), true);
    EXPECT_EQ(result->Get(4), false);
    
    delete result;
}