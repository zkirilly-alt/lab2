#include "ApplicationModel.hpp"
#include <sstream>
#include <algorithm>
#include <cmath>

std::string ApplicationModel::intSequenceToString(const Sequence<int>* seq) const {
    if (!seq) return "[]";
    std::ostringstream oss;
    oss << "[";
    int len = seq->GetLength();
    for (int i = 0; i < len; ++i) {
        oss << seq->Get(i);
        if (i < len - 1) oss << ", ";
    }
    oss << "]";
    return oss.str();
}

std::string ApplicationModel::boolSequenceToString(const Sequence<bool>* seq) const {
    if (!seq) return "";
    std::ostringstream oss;
    for (int i = 0; i < seq->GetLength(); ++i)
        oss << (seq->Get(i) ? "1" : "0");
    return oss.str();
}
ApplicationModel::ApplicationModel()
    : arraySeq(new MutableArraySequence<int>())
    , listSeq(new ListSequence<int>())
    , mutableSeq(new MutableArraySequence<int>())
    , immutableSeq(new ImmutableArraySequence<int>(new int[5]{10,20,30,40,50}, 5))
    , bitSeq1(new BitSequence())
    , seq1(new ArraySequence<int>())
    , seq2(new ArraySequence<int>())
    , currentMatrix(0)
{}


ApplicationModel::ApplicationModel(const ApplicationModel& other)
    : arraySeq(other.arraySeq ? other.arraySeq->Clone() : nullptr)
    , listSeq(other.listSeq ? other.listSeq->Clone() : nullptr)
    , mutableSeq(other.mutableSeq ? other.mutableSeq->Clone() : nullptr)
    , immutableSeq(other.immutableSeq ? other.immutableSeq->Clone() : nullptr)
    , bitSeq1(other.bitSeq1 ? other.bitSeq1->Clone() : nullptr)
    , seq1(other.seq1 ? other.seq1->Clone() : nullptr)
    , seq2(other.seq2 ? other.seq2->Clone() : nullptr)
    , currentMatrix(other.currentMatrix)
{}


ApplicationModel& ApplicationModel::operator=(const ApplicationModel& other) {
    if (this != &other) {
        
        delete arraySeq;
        delete listSeq;
        delete mutableSeq;
        delete immutableSeq;
        delete bitSeq1;
        delete seq1;
        delete seq2;
        
        
        arraySeq = other.arraySeq ? other.arraySeq->Clone() : nullptr;
        listSeq = other.listSeq ? other.listSeq->Clone() : nullptr;
        mutableSeq = other.mutableSeq ? other.mutableSeq->Clone() : nullptr;
        immutableSeq = other.immutableSeq ? other.immutableSeq->Clone() : nullptr;
        bitSeq1 = other.bitSeq1 ? other.bitSeq1->Clone() : nullptr;
        seq1 = other.seq1 ? other.seq1->Clone() : nullptr;
        seq2 = other.seq2 ? other.seq2->Clone() : nullptr;
        currentMatrix = other.currentMatrix;
    }
    return *this;
}


ApplicationModel::ApplicationModel(ApplicationModel&& other) noexcept
    : arraySeq(other.arraySeq)
    , listSeq(other.listSeq)
    , mutableSeq(other.mutableSeq)
    , immutableSeq(other.immutableSeq)
    , bitSeq1(other.bitSeq1)
    , seq1(other.seq1)
    , seq2(other.seq2)
    , currentMatrix(std::move(other.currentMatrix))
{
    other.arraySeq = nullptr;
    other.listSeq = nullptr;
    other.mutableSeq = nullptr;
    other.immutableSeq = nullptr;
    other.bitSeq1 = nullptr;
    other.seq1 = nullptr;
    other.seq2 = nullptr;
}


ApplicationModel& ApplicationModel::operator=(ApplicationModel&& other) noexcept {
    if (this != &other) {
        
        delete arraySeq;
        delete listSeq;
        delete mutableSeq;
        delete immutableSeq;
        delete bitSeq1;
        delete seq1;
        delete seq2;
        
        
        arraySeq = other.arraySeq;
        listSeq = other.listSeq;
        mutableSeq = other.mutableSeq;
        immutableSeq = other.immutableSeq;
        bitSeq1 = other.bitSeq1;
        seq1 = other.seq1;
        seq2 = other.seq2;
        currentMatrix = std::move(other.currentMatrix);
        
        other.arraySeq = nullptr;
        other.listSeq = nullptr;
        other.mutableSeq = nullptr;
        other.immutableSeq = nullptr;
        other.bitSeq1 = nullptr;
        other.seq1 = nullptr;
        other.seq2 = nullptr;
    }
    return *this;
}

ApplicationModel::~ApplicationModel() {
    delete arraySeq;
    delete listSeq;
    delete mutableSeq;
    delete immutableSeq;
    delete bitSeq1;
    delete seq1;
    delete seq2;
}


void ApplicationModel::arrayAppend(int value) { arraySeq->Append(value); }
void ApplicationModel::arrayPrepend(int value) { arraySeq->Prepend(value); }
void ApplicationModel::arrayInsertAt(int index, int value) { arraySeq->InsertAt(value, index); }
int ApplicationModel::arrayGet(int index) const { return arraySeq->Get(index); }
void ApplicationModel::arrayConcatWithDemo() {
    MutableArraySequence<int> tmp;
    tmp.Append(100); tmp.Append(200); tmp.Append(300);
    Sequence<int>* res = arraySeq->Concat(tmp);
    delete res;
}
void ApplicationModel::arraySubsequence(int startIndex) {
    Sequence<int>* sub = arraySeq->GetSubsequence(startIndex, arraySeq->GetLength() - 1);
    delete sub;
}
void ApplicationModel::arrayClear() { arraySeq->Clear(); }
std::string ApplicationModel::arrayToString() const { return intSequenceToString(arraySeq); }


void ApplicationModel::listAppend(int value) { listSeq->Append(value); }
void ApplicationModel::listPrepend(int value) { listSeq->Prepend(value); }
void ApplicationModel::listInsertAt(int index, int value) { listSeq->InsertAt(value, index); }
int ApplicationModel::listGet(int index) const { return listSeq->Get(index); }
void ApplicationModel::listConcatWithDemo() {
    ListSequence<int> tmp;
    tmp.Append(100); tmp.Append(200); tmp.Append(300);
    Sequence<int>* res = listSeq->Concat(tmp);
    delete res;
}
void ApplicationModel::listSubsequence(int startIndex) {
    Sequence<int>* sub = listSeq->GetSubsequence(startIndex, listSeq->GetLength() - 1);
    delete sub;
}
void ApplicationModel::listClear() { listSeq->Clear(); }
std::string ApplicationModel::listToString() const { return intSequenceToString(listSeq); }


void ApplicationModel::mutableAppend(int value) { mutableSeq->Append(value); }
void ApplicationModel::mutablePrepend(int value) { mutableSeq->Prepend(value); }
void ApplicationModel::mutableInsertAt(int index, int value) { mutableSeq->InsertAt(value, index); }
std::string ApplicationModel::mutableToString() const { return intSequenceToString(mutableSeq); }


void ApplicationModel::immutableAppend(int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->AppendImmutable(value);
    delete immutableSeq;
    immutableSeq = newSeq;
}
void ApplicationModel::immutablePrepend(int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->PrependImmutable(value);
    delete immutableSeq;
    immutableSeq = newSeq;
}
void ApplicationModel::immutableInsertAt(int index, int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->InsertAtImmutable(value, index);
    delete immutableSeq;
    immutableSeq = newSeq;
}
std::string ApplicationModel::immutableToString() const { return intSequenceToString(immutableSeq); }


void ApplicationModel::bitSet(size_t index, bool value) {
    if (static_cast<int>(index) >= bitSeq1->GetLength()) {
        BitSequence* ns = new BitSequence(index + 1);
        for (int i = 0; i < bitSeq1->GetLength(); ++i)
            ns->Set(i, bitSeq1->Get(i));
        delete bitSeq1;
        bitSeq1 = ns;
    }
    static_cast<BitSequence*>(bitSeq1)->Set(index, value);
}
void ApplicationModel::bitAndWithSize(int size) {
    BitSequence seq2(size);
    for (int i = 0; i < size && i < bitSeq1->GetLength(); ++i)
        seq2.Set(i, bitSeq1->Get(i));
    BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) & seq2;
    (void)res; 
}
void ApplicationModel::bitOrWithSize(int size) {
    BitSequence seq2(size);
    for (int i = 0; i < size && i < bitSeq1->GetLength(); ++i)
        seq2.Set(i, bitSeq1->Get(i));
    BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) | seq2;
    (void)res;
}
void ApplicationModel::bitXorWithSize(int size) {
    BitSequence seq2(size);
    for (int i = 0; i < size && i < bitSeq1->GetLength(); ++i)
        seq2.Set(i, bitSeq1->Get(i));
    BitSequence res = (*static_cast<BitSequence*>(bitSeq1)) ^ seq2;
    (void)res;
}
void ApplicationModel::bitNot() {
    BitSequence res = ~(*static_cast<BitSequence*>(bitSeq1));
    (void)res;
}
std::string ApplicationModel::bitToString() const {
    return boolSequenceToString(bitSeq1);
}


void ApplicationModel::addToSeq1(const int* values, int count) {
    for (int i = 0; i < count; ++i)
        seq1->Append(values[i]);
}
void ApplicationModel::clearSeq1() { seq1->Clear(); }
void ApplicationModel::addToSeq2(const int* values, int count) {
    for (int i = 0; i < count; ++i)
        seq2->Append(values[i]);
}
void ApplicationModel::clearSeq2() { seq2->Clear(); }
std::string ApplicationModel::seq1ToString() const { return intSequenceToString(seq1); }
std::string ApplicationModel::seq2ToString() const { return intSequenceToString(seq2); }


std::string ApplicationModel::mapSeq1() const {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    Sequence<int>* res = Functional<int,int>::Map(seq1, [](int x){ return x*x; });
    std::string s = "Map " + intSequenceToString(seq1) + " -> квадраты: " + intSequenceToString(res);
    delete res;
    return s;
}
std::string ApplicationModel::whereSeq1() const {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    Sequence<int>* res = Functional<int,int>::Where(seq1, [](int x){ return x%2==0; });
    std::string s = "Where " + intSequenceToString(seq1) + " -> четные: " + intSequenceToString(res);
    delete res;
    return s;
}
std::string ApplicationModel::reduceSeq1() const {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    int sum = Functional<int,int>::Reduce(seq1, [](int a,int b){ return a+b; }, 0);
    int prod = Functional<int,int>::Reduce(seq1, [](int a,int b){ return a*b; }, 1);
    std::ostringstream oss;
    oss << "Reduce " << intSequenceToString(seq1) << " -> сумма = " << sum << ", произведение = " << prod;
    return oss.str();
}
std::string ApplicationModel::zipSeq1Seq2() const {
    if (seq1->GetLength() == 0 || seq2->GetLength() == 0) return "Ошибка: пустые последовательности";
    Sequence<std::pair<int,int>>* z = Functional<int,int>::Zip(seq1, seq2);
    std::ostringstream oss;
    oss << "Zip " << intSequenceToString(seq1) << " и " << intSequenceToString(seq2) << " -> [";
    for (int i = 0; i < z->GetLength(); ++i) {
        oss << "(" << z->Get(i).first << "," << z->Get(i).second << ")";
        if (i < z->GetLength() - 1) oss << ", ";
    }
    oss << "]";
    delete z;
    return oss.str();
}
std::string ApplicationModel::splitSeq1() const {
    if (seq1->GetLength() == 0) return "Ошибка: Seq1 пуста";
    Sequence<Sequence<int>*>* res = Functional<int,int>::Split(seq1, [](int x){ return x==0; });
    std::ostringstream oss;
    oss << "Split по нулю: ";
    for (int i = 0; i < res->GetLength(); ++i)
        oss << intSequenceToString(res->Get(i)) << ", ";
    for (int i = 0; i < res->GetLength(); ++i) delete res->Get(i);
    delete res;
    return oss.str();
}
std::string ApplicationModel::unzipSeq1Seq2() const {
    if (seq1->GetLength() == 0 || seq2->GetLength() == 0) return "Ошибка: пустые";
    Sequence<std::pair<int,int>>* z = Functional<int,int>::Zip(seq1, seq2);
    auto u = Functional<int,int>::Unzip(z);
    std::string s = "Unzip: " + intSequenceToString(u.first) + " и " + intSequenceToString(u.second);
    delete z; delete u.first; delete u.second;
    return s;
}
std::string ApplicationModel::demoIterators() const {
    if (seq1->GetLength() == 0) return "Ошибка: Seq1 пуста";
    
    
    std::ostringstream oss;
    oss << "Итератор по Seq1: [";
    for (int x : *static_cast<ArraySequence<int>*>(seq1)) oss << x << " ";
    oss << "]";
    for (auto& x : *static_cast<ArraySequence<int>*>(seq1)) x *= 2;
    oss << "\nПосле умножения на 2: [";
    for (int x : *static_cast<ArraySequence<int>*>(seq1)) oss << x << " ";
    oss << "]";
    return oss.str();
}


void ApplicationModel::matrixCreate(int size) {
    currentMatrix = SquareMatrix<double>(size);
}
void ApplicationModel::matrixInitFromString(const std::string& values) {
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
void ApplicationModel::matrixAddFromUI(const DynamicArray<DynamicArray<double>>& uiValues) {
    int n = currentMatrix.GetSize();
    SquareMatrix<double> other(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            other.Set(i, j, uiValues.Get(i).Get(j));
    SquareMatrix<double> res = currentMatrix.Add(other);
    currentMatrix = res; 
}
void ApplicationModel::matrixMultiplyByScalar(double scalar) {
    currentMatrix = currentMatrix.MultiplyByScalar(scalar);
}
double ApplicationModel::matrixNorm() const {
    return currentMatrix.Norm();
}
void ApplicationModel::matrixSwapRows(int i, int j) { currentMatrix.SwapRows(i, j); }
void ApplicationModel::matrixMultiplyRow(int i, double factor) { currentMatrix.MultiplyRow(i, factor); }
void ApplicationModel::matrixAddRow(int target, int source, double factor) { currentMatrix.AddRow(target, source, factor); }
void ApplicationModel::matrixSwapCols(int i, int j) { currentMatrix.SwapCols(i, j); }
void ApplicationModel::matrixMultiplyCol(int j, double factor) { currentMatrix.MultiplyCol(j, factor); }
void ApplicationModel::matrixAddCol(int target, int source, double factor) { currentMatrix.AddCol(target, source, factor); }
void ApplicationModel::matrixMultiplyMatrices(const DynamicArray<DynamicArray<double>>& uiValues) {
    int n = currentMatrix.GetSize();
    SquareMatrix<double> other(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            other.Set(i, j, uiValues.Get(i).Get(j));
    currentMatrix = currentMatrix.Multiply(other);
}
int ApplicationModel::matrixSize() const { return currentMatrix.GetSize(); }
double ApplicationModel::matrixGet(int row, int col) const { return currentMatrix.Get(row, col); }
void ApplicationModel::matrixSet(int row, int col, double value) { currentMatrix.Set(row, col, value); }
std::string ApplicationModel::matrixToString() const {
    return currentMatrix.ToString();
}
void ApplicationModel::complexMatrixCreate(int size) {
    currentComplexMatrix = SquareMatrix<Complex>(size);
}

void ApplicationModel::complexMatrixInitFromString(const std::string& reValues, const std::string& imValues) {
    std::istringstream issRe(reValues);
    std::istringstream issIm(imValues);
    double re, im;
    DynamicArray<std::pair<double, double>> vals;
    while (issRe >> re && issIm >> im) {
        vals.Append({re, im});
    }
    int n = currentComplexMatrix.GetSize();
    if (vals.GetSize() != static_cast<size_t>(n * n))
        throw InvalidArgumentError("Неверное количество чисел");
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            auto p = vals.Get(i * n + j);
            currentComplexMatrix.Set(i, j, Complex(p.first, p.second));
        }
}

void ApplicationModel::complexMatrixAddFromUI(const DynamicArray<DynamicArray<std::pair<double, double>>>& uiValues) {
    int n = currentComplexMatrix.GetSize();
    SquareMatrix<Complex> other(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            auto p = uiValues.Get(i).Get(j);
            other.Set(i, j, Complex(p.first, p.second));
        }
    currentComplexMatrix = currentComplexMatrix.Add(other);
}

void ApplicationModel::complexMatrixMultiplyByScalar(double scalar) {
    currentComplexMatrix = currentComplexMatrix.MultiplyByScalar(Complex(scalar, 0));
}

double ApplicationModel::complexMatrixNorm() const {
    return currentComplexMatrix.Norm();
}

void ApplicationModel::complexMatrixSwapRows(int i, int j) {
    currentComplexMatrix.SwapRows(i, j);
}

void ApplicationModel::complexMatrixMultiplyRow(int i, double factor) {
    currentComplexMatrix.MultiplyRow(i, Complex(factor, 0));
}

void ApplicationModel::complexMatrixAddRow(int target, int source, double factor) {
    currentComplexMatrix.AddRow(target, source, Complex(factor, 0));
}

void ApplicationModel::complexMatrixSwapCols(int i, int j) {
    currentComplexMatrix.SwapCols(i, j);
}

void ApplicationModel::complexMatrixMultiplyCol(int j, double factor) {
    currentComplexMatrix.MultiplyCol(j, Complex(factor, 0));
}

void ApplicationModel::complexMatrixAddCol(int target, int source, double factor) {
    currentComplexMatrix.AddCol(target, source, Complex(factor, 0));
}

void ApplicationModel::complexMatrixMultiplyMatrices(const DynamicArray<DynamicArray<std::pair<double, double>>>& uiValues) {
    int n = currentComplexMatrix.GetSize();
    SquareMatrix<Complex> other(n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            auto p = uiValues.Get(i).Get(j);
            other.Set(i, j, Complex(p.first, p.second));
        }
    currentComplexMatrix = currentComplexMatrix.Multiply(other);
}

int ApplicationModel::complexMatrixSize() const {
    return currentComplexMatrix.GetSize();
}

Complex ApplicationModel::complexMatrixGet(int row, int col) const {
    return currentComplexMatrix.Get(row, col);
}

void ApplicationModel::complexMatrixSet(int row, int col, const Complex& value) {
    currentComplexMatrix.Set(row, col, value);
}

std::string ApplicationModel::complexMatrixToString() const {
    return currentComplexMatrix.ToString();
}