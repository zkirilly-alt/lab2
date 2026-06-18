#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"
#include <string>

class SequenceRepository {
public:
    SequenceRepository();
    ~SequenceRepository();
    
    void arrayAppend(int value);
    void arrayPrepend(int value);
    void arrayInsertAt(int index, int value);
    int arrayGet(int index) const;
    void arrayClear();
    std::string arrayToString() const;
    Sequence<int>* getArraySeq() const;

    
    void listAppend(int value);
    void listPrepend(int value);
    void listInsertAt(int index, int value);
    int listGet(int index) const;
    void listClear();
    std::string listToString() const;
    Sequence<int>* getListSeq() const;

    
    void mutableAppend(int value);
    void mutablePrepend(int value);
    void mutableInsertAt(int index, int value);
    std::string mutableToString() const;
    Sequence<int>* getMutableSeq() const;

    
    void immutableAppend(int value);
    void immutablePrepend(int value);
    void immutableInsertAt(int index, int value);
    std::string immutableToString() const;
    Sequence<int>* getImmutableSeq() const;

    
    void bitSet(size_t index, bool value);
    void bitClear();
    std::string bitToString() const;
    Sequence<bool>* getBitSeq() const;

    
    Sequence<int>* getSeq1() const;
    Sequence<int>* getSeq2() const;
    void addToSeq1(const int* values, int count);
    void clearSeq1();
    void addToSeq2(const int* values, int count);
    void clearSeq2();
    std::string seq1ToString() const;
    std::string seq2ToString() const;

private:
    Sequence<int>* arraySeq;
    Sequence<int>* listSeq;
    Sequence<int>* mutableSeq;
    Sequence<int>* immutableSeq;
    Sequence<bool>* bitSeq1;
    Sequence<int>* seq1;
    Sequence<int>* seq2;

    std::string intSequenceToString(const Sequence<int>* seq) const;
    std::string boolSequenceToString(const Sequence<bool>* seq) const;
};