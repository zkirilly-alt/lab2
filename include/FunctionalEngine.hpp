#pragma once
#include "Sequence.hpp"
#include <string>

class FunctionalEngine {
public:
    static std::string mapSeq1(Sequence<int>* seq1);
    static std::string whereSeq1(Sequence<int>* seq1);
    static std::string reduceSeq1(Sequence<int>* seq1);
    static std::string zipSeq1Seq2(Sequence<int>* seq1, Sequence<int>* seq2);
    static std::string splitSeq1(Sequence<int>* seq1);
    static std::string unzipSeq1Seq2(Sequence<int>* seq1, Sequence<int>* seq2);
    static std::string demoIterators(Sequence<int>* seq1); 

private:
    static std::string intSequenceToString(const Sequence<int>* seq);
};