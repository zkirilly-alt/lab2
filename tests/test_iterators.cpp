#include <gtest/gtest.h>
#include "ArraySequence.hpp"
#include "ListSequence.hpp"

TEST(IteratorTest, ArraySequenceRangeBasedFor) {
    int data[] = {1, 2, 3, 4, 5};
    ArraySequence<int> seq(data, 5);
    
    int sum = 0;
    for (int x : seq) {
        sum += x;
    }
    EXPECT_EQ(sum, 15);
}

TEST(IteratorTest, ListSequenceRangeBasedFor) {
    int data[] = {1, 2, 3, 4, 5};
    ListSequence<int> seq(data, 5);
    
    int sum = 0;
    for (int x : seq) {
        sum += x;
    }
    EXPECT_EQ(sum, 15);
}

TEST(IteratorTest, ArraySequenceModifyThroughIterator) {
    ArraySequence<int> seq;
    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    
    for (auto& x : seq) {
        x = x * 2;
    }
    
    EXPECT_EQ(seq.Get(0), 2);
    EXPECT_EQ(seq.Get(1), 4);
    EXPECT_EQ(seq.Get(2), 6);
}