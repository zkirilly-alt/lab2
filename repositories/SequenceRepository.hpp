#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MutableArraySequence.hpp"
#include "ImmutableArraySequence.hpp"
#include "BitSequence.hpp"

class SequenceRepository {
public:
    SequenceRepository();
    ~SequenceRepository();
    
    Sequence<int>* getArraySeq() const;
    Sequence<int>* getListSeq() const;
    Sequence<int>* getMutableSeq() const;
    Sequence<int>* getImmutableSeq() const;
    Sequence<bool>* getBitSeq() const;
    Sequence<int>* getSeq1() const;
    Sequence<int>* getSeq2() const;

    void replaceImmutableSeq(Sequence<int>* newSeq);

private:
    Sequence<int>* arraySeq;
    Sequence<int>* listSeq;
    Sequence<int>* mutableSeq;
    Sequence<int>* immutableSeq;
    Sequence<bool>* bitSeq1;
    Sequence<int>* seq1;
    Sequence<int>* seq2;
};