#pragma once
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "Exception.hpp"
#include <functional>
#include <utility>
#include <algorithm>

template<typename T, typename R>
class Functional {
public:
    template<typename Func>
    static Sequence<R>* Map(Sequence<T>* seq, Func func) {
        if (seq == nullptr) {
            throw NullPtrException("Functional::Map: нулевой указатель на последовательность");
        }
        Sequence<R>* result = new ArraySequence<R>();
        for (int i = 0; i < seq->GetLength(); ++i) {
            result->Append(func(seq->Get(i)));
        }
        return result;
    }
    
    template<typename Predicate>
    static Sequence<T>* Where(Sequence<T>* seq, Predicate predicate) {
        if (seq == nullptr) {
            throw NullPtrException("Functional::Where: нулевой указатель на последовательность");
        }
        Sequence<T>* result = new ArraySequence<T>();
        for (int i = 0; i < seq->GetLength(); ++i) {
            T item = seq->Get(i);
            if (predicate(item)) {
                result->Append(item);
            }
        }
        return result;
    }
    
    template<typename Acc, typename Func>
    static Acc Reduce(Sequence<T>* seq, Func func, Acc initial) {
        if (seq == nullptr) {
            throw NullPtrException("Functional::Reduce: нулевой указатель на последовательность");
        }
        Acc result = initial;
        for (int i = 0; i < seq->GetLength(); ++i) {
            result = func(result, seq->Get(i));
        }
        return result;
    }
    
    static Sequence<std::pair<T, R>>* Zip(Sequence<T>* seq1, Sequence<R>* seq2) {
        if (seq1 == nullptr || seq2 == nullptr) {
            throw NullPtrException("Functional::Zip: нулевой указатель на последовательность");
        }
        int minLength = std::min(seq1->GetLength(), seq2->GetLength());
        Sequence<std::pair<T, R>>* result = new ArraySequence<std::pair<T, R>>();
        
        for (int i = 0; i < minLength; ++i) {
            result->Append(std::make_pair(seq1->Get(i), seq2->Get(i)));
        }
        return result;
    }
    
    static std::pair<Sequence<T>*, Sequence<R>*> Unzip(Sequence<std::pair<T, R>>* seq) {
        if (seq == nullptr) {
            throw NullPtrException("Functional::Unzip: нулевой указатель на последовательность");
        }
        Sequence<T>* first = new ArraySequence<T>();
        Sequence<R>* second = new ArraySequence<R>();
        
        for (int i = 0; i < seq->GetLength(); ++i) {
            auto pair = seq->Get(i);
            first->Append(pair.first);
            second->Append(pair.second);
        }
        
        return std::make_pair(first, second);
    }
    
    static Sequence<Sequence<T>*>* Split(Sequence<T>* seq, std::function<bool(T)> predicate) {
        if (seq == nullptr) {
            throw NullPtrException("Functional::Split: нулевой указатель на последовательность");
        }
        Sequence<Sequence<T>*>* result = new ArraySequence<Sequence<T>*>();
        Sequence<T>* current = new ArraySequence<T>();
        
        for (int i = 0; i < seq->GetLength(); ++i) {
            T item = seq->Get(i);
            if (predicate(item)) {
                if (current->GetLength() > 0) {
                    result->Append(current);
                    current = new ArraySequence<T>();
                }
            } else {
                current->Append(item);
            }
        }
        
        if (current->GetLength() > 0) {
            result->Append(current);
        } else {
            delete current;
        }
        
        return result;
    }
};
