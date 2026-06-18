#pragma once
#include "SquareMatrix.hpp"
#include "Complex.hpp"
#include "DynamicArray.hpp"
#include <string>
#include <utility>

class ComplexMatrixRepository {
public:
    void create(int size);
    void initFromStrings(const std::string& reValues, const std::string& imValues);
    void set(int row, int col, const Complex& value);
    Complex get(int row, int col) const;
    int size() const;
    std::string toString() const;
    SquareMatrix<Complex>& getMatrix();
    const SquareMatrix<Complex>& getMatrix() const;

private:
    SquareMatrix<Complex> currentMatrix;
};