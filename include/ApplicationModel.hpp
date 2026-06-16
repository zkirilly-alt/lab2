#pragma once

#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include "SquareMatrix.hpp"
#include "Complex.hpp"
#include "Functional.hpp"
#include "DynamicArray.hpp"
#include <string>

class ApplicationModel {
public:
    ApplicationModel();
    ~ApplicationModel();

    ApplicationModel(const ApplicationModel&) = delete;
    ApplicationModel& operator=(const ApplicationModel&) = delete;
    ApplicationModel(ApplicationModel&&) = delete;
    ApplicationModel& operator=(ApplicationModel&&) = delete;

    void arrayAppend(int value);
    void arrayPrepend(int value);
    void arrayInsertAt(int index, int value);
    int arrayGet(int index) const;
    void arrayConcatWithDemo();      
    void arraySubsequence(int startIndex);
    void arrayClear();
    std::string arrayToString() const;

    
    void listAppend(int value);
    void listPrepend(int value);
    void listInsertAt(int index, int value);
    int listGet(int index) const;
    void listConcatWithDemo();
    void listSubsequence(int startIndex);
    void listClear();
    std::string listToString() const;

    
    void mutableAppend(int value);
    void mutablePrepend(int value);
    void mutableInsertAt(int index, int value);
    std::string mutableToString() const;

    
    void immutableAppend(int value);
    void immutablePrepend(int value);
    void immutableInsertAt(int index, int value);
    std::string immutableToString() const;

    
    void bitSet(size_t index, bool value);
    void bitAndWithSize(int size);   
    void bitOrWithSize(int size);
    void bitXorWithSize(int size);
    void bitNot();
    std::string bitToString() const;

    
    void addToSeq1(const int* values, int count);
    void clearSeq1();
    void addToSeq2(const int* values, int count);
    void clearSeq2();
    std::string seq1ToString() const;
    std::string seq2ToString() const;

    
    std::string mapSeq1() const;
    std::string whereSeq1() const;
    std::string reduceSeq1() const;
    std::string zipSeq1Seq2() const;
    std::string splitSeq1() const;
    std::string unzipSeq1Seq2() const;
    std::string demoIterators() const;   

    
    void matrixCreate(int size);
    void matrixInitFromString(const std::string& values); 
    void matrixAddFromUI(const DynamicArray<DynamicArray<double>>& uiValues); 
    void matrixMultiplyByScalar(double scalar);
    double matrixNorm() const;
    void matrixSwapRows(int i, int j);
    void matrixMultiplyRow(int i, double factor);
    void matrixAddRow(int target, int source, double factor);
    void matrixSwapCols(int i, int j);
    void matrixMultiplyCol(int j, double factor);
    void matrixAddCol(int target, int source, double factor);
    void matrixMultiplyMatrices(const DynamicArray<DynamicArray<double>>& uiValues);
    int matrixSize() const;
    double matrixGet(int row, int col) const;
    void matrixSet(int row, int col, double value);
    std::string matrixToString() const;

    void complexMatrixCreate(int size);
    void complexMatrixInitFromString(const std::string& reValues, const std::string& imValues);
    void complexMatrixAddFromUI(const DynamicArray<DynamicArray<std::pair<double, double>>>& uiValues);
    void complexMatrixMultiplyByScalar(double scalar);
    double complexMatrixNorm() const;
    void complexMatrixSwapRows(int i, int j);
    void complexMatrixMultiplyRow(int i, double factor);
    void complexMatrixAddRow(int target, int source, double factor);
    void complexMatrixSwapCols(int i, int j);
    void complexMatrixMultiplyCol(int j, double factor);
    void complexMatrixAddCol(int target, int source, double factor);
    void complexMatrixMultiplyMatrices(const DynamicArray<DynamicArray<std::pair<double, double>>>& uiValues);
    int complexMatrixSize() const;
    Complex complexMatrixGet(int row, int col) const;
    void complexMatrixSet(int row, int col, const Complex& value);
    std::string complexMatrixToString() const;

private:
    Sequence<int>* arraySeq;
    Sequence<int>* listSeq;
    Sequence<int>* mutableSeq;
    Sequence<int>* immutableSeq;
    Sequence<bool>* bitSeq1;
    Sequence<int>* seq1;
    Sequence<int>* seq2;
    SquareMatrix<double> currentMatrix;
    SquareMatrix<Complex> currentComplexMatrix;

    std::string intSequenceToString(const Sequence<int>* seq) const;
    std::string boolSequenceToString(const Sequence<bool>* seq) const;
};