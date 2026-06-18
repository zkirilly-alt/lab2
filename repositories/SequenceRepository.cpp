#include "SequenceRepository.hpp"
#include <sstream>

SequenceRepository::SequenceRepository()
    : arraySeq(new MutableArraySequence<int>())
    , listSeq(new ListSequence<int>())
    , mutableSeq(new MutableArraySequence<int>())
    , immutableSeq(new ImmutableArraySequence<int>(new int[5]{10,20,30,40,50}, 5))
    , bitSeq1(new BitSequence())
    , seq1(new ArraySequence<int>())
    , seq2(new ArraySequence<int>())
{}

SequenceRepository::~SequenceRepository() {
    delete arraySeq;
    delete listSeq;
    delete mutableSeq;
    delete immutableSeq;
    delete bitSeq1;
    delete seq1;
    delete seq2;
}

std::string SequenceRepository::intSequenceToString(const Sequence<int>* seq) const {
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

std::string SequenceRepository::boolSequenceToString(const Sequence<bool>* seq) const {
    if (!seq) return "";
    std::ostringstream oss;
    for (int i = 0; i < seq->GetLength(); ++i)
        oss << (seq->Get(i) ? "1" : "0");
    return oss.str();
}


void SequenceRepository::arrayAppend(int value) { arraySeq->Append(value); }
void SequenceRepository::arrayPrepend(int value) { arraySeq->Prepend(value); }
void SequenceRepository::arrayInsertAt(int index, int value) { arraySeq->InsertAt(value, index); }
int SequenceRepository::arrayGet(int index) const { return arraySeq->Get(index); }
void SequenceRepository::arrayClear() { arraySeq->Clear(); }
std::string SequenceRepository::arrayToString() const { return intSequenceToString(arraySeq); }
Sequence<int>* SequenceRepository::getArraySeq() const { return arraySeq; }


void SequenceRepository::listAppend(int value) { listSeq->Append(value); }
void SequenceRepository::listPrepend(int value) { listSeq->Prepend(value); }
void SequenceRepository::listInsertAt(int index, int value) { listSeq->InsertAt(value, index); }
int SequenceRepository::listGet(int index) const { return listSeq->Get(index); }
void SequenceRepository::listClear() { listSeq->Clear(); }
std::string SequenceRepository::listToString() const { return intSequenceToString(listSeq); }
Sequence<int>* SequenceRepository::getListSeq() const { return listSeq; }


void SequenceRepository::mutableAppend(int value) { mutableSeq->Append(value); }
void SequenceRepository::mutablePrepend(int value) { mutableSeq->Prepend(value); }
void SequenceRepository::mutableInsertAt(int index, int value) { mutableSeq->InsertAt(value, index); }
std::string SequenceRepository::mutableToString() const { return intSequenceToString(mutableSeq); }
Sequence<int>* SequenceRepository::getMutableSeq() const { return mutableSeq; }


void SequenceRepository::immutableAppend(int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->AppendImmutable(value);
    delete immutableSeq;
    immutableSeq = newSeq;
}
void SequenceRepository::immutablePrepend(int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->PrependImmutable(value);
    delete immutableSeq;
    immutableSeq = newSeq;
}
void SequenceRepository::immutableInsertAt(int index, int value) {
    ImmutableArraySequence<int>* newSeq =
        static_cast<ImmutableArraySequence<int>*>(immutableSeq)->InsertAtImmutable(value, index);
    delete immutableSeq;
    immutableSeq = newSeq;
}
std::string SequenceRepository::immutableToString() const { return intSequenceToString(immutableSeq); }
Sequence<int>* SequenceRepository::getImmutableSeq() const { return immutableSeq; }


void SequenceRepository::bitSet(size_t index, bool value) {
    if (static_cast<int>(index) >= bitSeq1->GetLength()) {
        BitSequence* ns = new BitSequence(index + 1);
        for (int i = 0; i < bitSeq1->GetLength(); ++i)
            ns->Set(i, bitSeq1->Get(i));
        delete bitSeq1;
        bitSeq1 = ns;
    }
    static_cast<BitSequence*>(bitSeq1)->Set(index, value);
}
void SequenceRepository::bitClear() { bitSeq1->Clear(); }
std::string SequenceRepository::bitToString() const { return boolSequenceToString(bitSeq1); }
Sequence<bool>* SequenceRepository::getBitSeq() const { return bitSeq1; }


Sequence<int>* SequenceRepository::getSeq1() const { return seq1; }
Sequence<int>* SequenceRepository::getSeq2() const { return seq2; }

void SequenceRepository::addToSeq1(const int* values, int count) {
    for (int i = 0; i < count; ++i)
        seq1->Append(values[i]);
}
void SequenceRepository::clearSeq1() { seq1->Clear(); }
void SequenceRepository::addToSeq2(const int* values, int count) {
    for (int i = 0; i < count; ++i)
        seq2->Append(values[i]);
}
void SequenceRepository::clearSeq2() { seq2->Clear(); }
std::string SequenceRepository::seq1ToString() const { return intSequenceToString(seq1); }
std::string SequenceRepository::seq2ToString() const { return intSequenceToString(seq2); }