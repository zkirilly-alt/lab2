#include "ComplexMatrixRepository.hpp"
#include "Exception.hpp"
#include <sstream>

void ComplexMatrixRepository::create(int size) {
    currentMatrix = SquareMatrix<Complex>(size);
}

void ComplexMatrixRepository::initFromStrings(const std::string& reValues, const std::string& imValues) {
    std::istringstream issRe(reValues);
    std::istringstream issIm(imValues);
    double re, im;
    DynamicArray<std::pair<double, double>> vals;
    while (issRe >> re && issIm >> im) {
        vals.Append({re, im});
    }
    int n = currentMatrix.GetSize();
    if (vals.GetSize() != static_cast<size_t>(n * n))
        throw InvalidArgumentError("Неверное количество чисел");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            auto p = vals.Get(i * n + j);
            currentMatrix.Set(i, j, Complex(p.first, p.second));
        }
}

void ComplexMatrixRepository::set(int row, int col, const Complex& value) {
    currentMatrix.Set(row, col, value);
}

Complex ComplexMatrixRepository::get(int row, int col) const {
    return currentMatrix.Get(row, col);
}

int ComplexMatrixRepository::size() const {
    return currentMatrix.GetSize();
}

std::string ComplexMatrixRepository::toString() const {
    return currentMatrix.ToString();
}

SquareMatrix<Complex>& ComplexMatrixRepository::getMatrix() {
    return currentMatrix;
}

const SquareMatrix<Complex>& ComplexMatrixRepository::getMatrix() const {
    return currentMatrix;
}