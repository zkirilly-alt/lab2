#include "FunctionalEngine.hpp"
#include "Functional.hpp"
#include "ArraySequence.hpp"
#include <sstream>

std::string FunctionalEngine::intSequenceToString(const Sequence<int>* seq) {
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

std::string FunctionalEngine::mapSeq1(Sequence<int>* seq1) {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    Sequence<int>* res = Functional<int,int>::Map(seq1, [](int x){ return x*x; });
    std::string s = "Map " + intSequenceToString(seq1) + " -> квадраты: " + intSequenceToString(res);
    delete res;
    return s;
}

std::string FunctionalEngine::whereSeq1(Sequence<int>* seq1) {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    Sequence<int>* res = Functional<int,int>::Where(seq1, [](int x){ return x%2==0; });
    std::string s = "Where " + intSequenceToString(seq1) + " -> четные: " + intSequenceToString(res);
    delete res;
    return s;
}

std::string FunctionalEngine::reduceSeq1(Sequence<int>* seq1) {
    if (seq1->GetLength() == 0) return "Ошибка: первая последовательность пуста";
    int sum = Functional<int,int>::Reduce(seq1, [](int a,int b){ return a+b; }, 0);
    int prod = Functional<int,int>::Reduce(seq1, [](int a,int b){ return a*b; }, 1);
    std::ostringstream oss;
    oss << "Reduce " << intSequenceToString(seq1) << " -> сумма = " << sum << ", произведение = " << prod;
    return oss.str();
}

std::string FunctionalEngine::zipSeq1Seq2(Sequence<int>* seq1, Sequence<int>* seq2) {
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

std::string FunctionalEngine::splitSeq1(Sequence<int>* seq1) {
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

std::string FunctionalEngine::unzipSeq1Seq2(Sequence<int>* seq1, Sequence<int>* seq2) {
    if (seq1->GetLength() == 0 || seq2->GetLength() == 0) return "Ошибка: пустые";
    Sequence<std::pair<int,int>>* z = Functional<int,int>::Zip(seq1, seq2);
    auto u = Functional<int,int>::Unzip(z);
    std::string s = "Unzip: " + intSequenceToString(u.first) + " и " + intSequenceToString(u.second);
    delete z; delete u.first; delete u.second;
    return s;
}

std::string FunctionalEngine::demoIterators(Sequence<int>* seq1) {
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