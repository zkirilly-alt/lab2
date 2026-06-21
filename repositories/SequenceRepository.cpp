#include "SequenceRepository.hpp"

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

Sequence<int>* SequenceRepository::getArraySeq() const { return arraySeq; }
Sequence<int>* SequenceRepository::getListSeq() const { return listSeq; }
Sequence<int>* SequenceRepository::getMutableSeq() const { return mutableSeq; }
Sequence<int>* SequenceRepository::getImmutableSeq() const { return immutableSeq; }
Sequence<bool>* SequenceRepository::getBitSeq() const { return bitSeq1; }
Sequence<int>* SequenceRepository::getSeq1() const { return seq1; }
Sequence<int>* SequenceRepository::getSeq2() const { return seq2; }

void SequenceRepository::replaceImmutableSeq(Sequence<int>* newSeq) {
    delete immutableSeq;
    immutableSeq = newSeq;
}