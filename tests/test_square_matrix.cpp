#include <gtest/gtest.h>
#include "SquareMatrix.hpp"

TEST(SquareMatrixTest, ConstructorAndGetSet) {
    SquareMatrix<int> m(2);
    EXPECT_EQ(m.GetSize(), 2);
    EXPECT_EQ(m.Get(0,0), 0);
    m.Set(0,0,5);
    EXPECT_EQ(m.Get(0,0), 5);
}

TEST(SquareMatrixTest, Add) {
    SquareMatrix<int> a(2);
    a.Set(0,0,1); a.Set(0,1,2);
    a.Set(1,0,3); a.Set(1,1,4);
    SquareMatrix<int> b(2);
    b.Set(0,0,5); b.Set(0,1,6);
    b.Set(1,0,7); b.Set(1,1,8);
    SquareMatrix<int> c = a.Add(b);
    EXPECT_EQ(c.Get(0,0), 6);
    EXPECT_EQ(c.Get(0,1), 8);
    EXPECT_EQ(c.Get(1,0), 10);
    EXPECT_EQ(c.Get(1,1), 12);
}

TEST(SquareMatrixTest, MultiplyByScalar) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    SquareMatrix<int> r = m.MultiplyByScalar(2);
    EXPECT_EQ(r.Get(0,0), 2);
    EXPECT_EQ(r.Get(0,1), 4);
    EXPECT_EQ(r.Get(1,0), 6);
    EXPECT_EQ(r.Get(1,1), 8);
}

TEST(SquareMatrixTest, Norm) {
    SquareMatrix<int> m(2);
    m.Set(0,0,3); m.Set(0,1,0);
    m.Set(1,0,0); m.Set(1,1,4);
    double n = m.Norm();
    EXPECT_DOUBLE_EQ(n, 5.0);
}

TEST(SquareMatrixTest, SwapRows) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.SwapRows(0,1);
    EXPECT_EQ(m.Get(0,0), 3);
    EXPECT_EQ(m.Get(0,1), 4);
    EXPECT_EQ(m.Get(1,0), 1);
    EXPECT_EQ(m.Get(1,1), 2);
}

TEST(SquareMatrixTest, MultiplyRow) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.MultiplyRow(0, 2);
    EXPECT_EQ(m.Get(0,0), 2);
    EXPECT_EQ(m.Get(0,1), 4);
    EXPECT_EQ(m.Get(1,0), 3);
    EXPECT_EQ(m.Get(1,1), 4);
}

TEST(SquareMatrixTest, AddRow) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.AddRow(1, 0, 2);
    EXPECT_EQ(m.Get(1,0), 5);
    EXPECT_EQ(m.Get(1,1), 8);
}

TEST(SquareMatrixTest, SwapCols) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.SwapCols(0,1);
    EXPECT_EQ(m.Get(0,0), 2);
    EXPECT_EQ(m.Get(0,1), 1);
    EXPECT_EQ(m.Get(1,0), 4);
    EXPECT_EQ(m.Get(1,1), 3);
}

TEST(SquareMatrixTest, MultiplyCol) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.MultiplyCol(0, 2);
    EXPECT_EQ(m.Get(0,0), 2);
    EXPECT_EQ(m.Get(1,0), 6);
    EXPECT_EQ(m.Get(0,1), 2);
    EXPECT_EQ(m.Get(1,1), 4);
}

TEST(SquareMatrixTest, AddCol) {
    SquareMatrix<int> m(2);
    m.Set(0,0,1); m.Set(0,1,2);
    m.Set(1,0,3); m.Set(1,1,4);
    m.AddCol(1, 0, 2);
    EXPECT_EQ(m.Get(0,1), 4);
    EXPECT_EQ(m.Get(1,1), 10);
}

TEST(SquareMatrixTest, MultiplyMatrices) {
    SquareMatrix<int> a(2);
    a.Set(0,0,1); a.Set(0,1,2);
    a.Set(1,0,3); a.Set(1,1,4);
    SquareMatrix<int> b(2);
    b.Set(0,0,2); b.Set(0,1,0);
    b.Set(1,0,1); b.Set(1,1,2);
    SquareMatrix<int> c = a.Multiply(b);
    EXPECT_EQ(c.Get(0,0), 4);
    EXPECT_EQ(c.Get(0,1), 4);
    EXPECT_EQ(c.Get(1,0), 10);
    EXPECT_EQ(c.Get(1,1), 8);
}

TEST(SquareMatrixTest, Exceptions) {
    SquareMatrix<int> m(2);
    EXPECT_THROW(m.Get(-1,0), IndexOutOfRange);
    EXPECT_THROW(m.Get(2,0), IndexOutOfRange);
    EXPECT_THROW(m.Set(0,2,5), IndexOutOfRange);
    EXPECT_THROW(m.SwapRows(0,2), IndexOutOfRange);
    EXPECT_THROW(m.MultiplyRow(2,2), IndexOutOfRange);
    EXPECT_THROW(m.AddRow(0,2,1), IndexOutOfRange);
    EXPECT_THROW(m.SwapCols(0,2), IndexOutOfRange);
    EXPECT_THROW(m.MultiplyCol(2,2), IndexOutOfRange);
    EXPECT_THROW(m.AddCol(0,2,1), IndexOutOfRange);
}