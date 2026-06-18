#include "DoubleMatrixRepository.hpp"
#include "Exception.hpp"
#include <sstream>

void DoubleMatrixRepository::create(int size) {
    currentMatrix = SquareMatrix<double>(size);
}

void DoubleMatrixRepository::initFromString(const std::string& values) {
    std::istringstream iss(values);
    double v;
    DynamicArray<double> vals;
    while (iss >> v) vals.Append(v);
    int n = currentMatrix.GetSize();
    if (vals.GetSize() != static_cast<size_t>(n * n))
        throw InvalidArgumentError("Неверное количество чисел");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            currentMatrix.Set(i, j, vals.Get(i * n + j));
}

void DoubleMatrixRepository::set(int row, int col, double value) {
    currentMatrix.Set(row, col, value);
}

double DoubleMatrixRepository::get(int row, int col) const {
    return currentMatrix.Get(row, col);
}

int DoubleMatrixRepository::size() const {
    return currentMatrix.GetSize();
}

std::string DoubleMatrixRepository::toString() const {
    return currentMatrix.ToString();
}

SquareMatrix<double>& DoubleMatrixRepository::getMatrix() {
    return currentMatrix;
}

const SquareMatrix<double>& DoubleMatrixRepository::getMatrix() const {
    return currentMatrix;
}