#pragma once
#include "ArraySequence.hpp"
#include "Exception.hpp"
#include "Complex.hpp"
#include <cmath>
#include <type_traits>
#include <sstream>

template<typename T>
class SquareMatrix {
private:
    ArraySequence<T> data;
    int size;

public:
    SquareMatrix(int n = 0) : size(n) {
        for (int i = 0; i < n * n; ++i) data.Append(T(0));
    }

    SquareMatrix(const SquareMatrix& other) : data(other.data), size(other.size) {}

    SquareMatrix(SquareMatrix&& other) noexcept
        : data(std::move(other.data)), size(other.size) {
        other.size = 0;
    }

    SquareMatrix& operator=(const SquareMatrix& other) {
        if (this != &other) {
            data = other.data;
            size = other.size;
        }
        return *this;
    }

    SquareMatrix& operator=(SquareMatrix&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            size = other.size;
            other.size = 0;
        }
        return *this;
    }

    int GetSize() const { return size; }

    T Get(int row, int col) const {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw IndexOutOfRange(row, size);
        }
        return data.Get(row * size + col);
    }

    void Set(int row, int col, T value) {
        if (row < 0 || row >= size || col < 0 || col >= size) {
            throw IndexOutOfRange(row, size);
        }
        data.Set(row * size + col, value);
    }

    SquareMatrix<T> Add(const SquareMatrix<T>& other) const {
        if (size != other.size) throw LengthMismatchException("SquareMatrix::Add: размеры матриц не совпадают");
        SquareMatrix<T> result(size);
        for (int i = 0; i < size * size; ++i) result.data.Set(i, data.Get(i) + other.data.Get(i));
        return result;
    }

    SquareMatrix<T> MultiplyByScalar(T scalar) const {
        SquareMatrix<T> result(size);
        for (int i = 0; i < size * size; ++i) result.data.Set(i, data.Get(i) * scalar);
        return result;
    }

    double Norm() const {
        double sum = 0.0;
        for (int i = 0; i < size * size; ++i) {
            T val = data.Get(i);
            if constexpr (std::is_same_v<T, Complex>) {
                sum += val.norm();
            } else {
                sum += val * val;
            }
        }
        return std::sqrt(sum);
    }

    void SwapRows(int i, int j) {
        if (i < 0 || i >= size || j < 0 || j >= size) throw IndexOutOfRange(i, size);
        for (int col = 0; col < size; ++col) {
            T tmp = Get(i, col);
            Set(i, col, Get(j, col));
            Set(j, col, tmp);
        }
    }

    void MultiplyRow(int i, T factor) {
        if (i < 0 || i >= size) throw IndexOutOfRange(i, size);
        for (int col = 0; col < size; ++col) Set(i, col, Get(i, col) * factor);
    }

    void AddRow(int target, int source, T factor) {
        if (target < 0 || target >= size || source < 0 || source >= size) throw IndexOutOfRange(target, size);
        for (int col = 0; col < size; ++col) Set(target, col, Get(target, col) + Get(source, col) * factor);
    }

    void SwapCols(int i, int j) {
        if (i < 0 || i >= size || j < 0 || j >= size) throw IndexOutOfRange(i, size);
        for (int row = 0; row < size; ++row) {
            T tmp = Get(row, i);
            Set(row, i, Get(row, j));
            Set(row, j, tmp);
        }
    }

    void MultiplyCol(int j, T factor) {
        if (j < 0 || j >= size) throw IndexOutOfRange(j, size);
        for (int row = 0; row < size; ++row) Set(row, j, Get(row, j) * factor);
    }

    void AddCol(int target, int source, T factor) {
        if (target < 0 || target >= size || source < 0 || source >= size) throw IndexOutOfRange(target, size);
        for (int row = 0; row < size; ++row) Set(row, target, Get(row, target) + Get(row, source) * factor);
    }

    SquareMatrix<T> Multiply(const SquareMatrix<T>& other) const {
        if (size != other.size) throw LengthMismatchException("SquareMatrix::Multiply: размеры матриц не совпадают");
        SquareMatrix<T> result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                T sum = T(0);
                for (int k = 0; k < size; ++k) sum = sum + Get(i, k) * other.Get(k, j);
                result.Set(i, j, sum);
            }
        }
        return result;
    }

    std::string ToString() const {
        std::ostringstream oss;
        for (int i = 0; i < size; ++i) {
            oss << "[";
            for (int j = 0; j < size; ++j) {
                oss << Get(i, j);
                if (j < size - 1) oss << ", ";
            }
            oss << "]";
            if (i < size - 1) oss << "\n";
        }
        return oss.str();
    }
};