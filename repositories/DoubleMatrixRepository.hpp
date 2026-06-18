#pragma once
#include "SquareMatrix.hpp"
#include "DynamicArray.hpp"
#include <string>

class DoubleMatrixRepository {
public:
    void create(int size);
    void initFromString(const std::string& values);
    void set(int row, int col, double value);
    double get(int row, int col) const;
    int size() const;
    std::string toString() const;
    SquareMatrix<double>& getMatrix();
    const SquareMatrix<double>& getMatrix() const;

private:
    SquareMatrix<double> currentMatrix;
};