#pragma once
#include "Sequence.hpp"
#include <vector>
#include <cstddef>

class BitSequence : public Sequence<bool> {
private:
    std::vector<bool> bits;
    
    void checkIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= bits.size()) {
            throw IndexOutOfRange("BitSequence: index out of range");
        }
    }

public:
    BitSequence() {}
    
    explicit BitSequence(size_t size) : bits(size, false) {}
    
    BitSequence(const bool* items, int count) {
        for (int i = 0; i < count; ++i) {
            bits.push_back(items[i]);
        }
    }
    
    BitSequence(const BitSequence& other) : bits(other.bits) {}
    
    ~BitSequence() {}
    
    BitSequence& operator=(const BitSequence& other) {
        if (this != &other) {
            bits = other.bits;
        }
        return *this;
    }
    
    bool GetFirst() const override {
        if (bits.empty()) {
            throw EmptyContainerError("BitSequence: sequence is empty");
        }
        return bits[0];
    }
    
    bool GetLast() const override {
        if (bits.empty()) {
            throw EmptyContainerError("BitSequence: sequence is empty");
        }
        return bits[bits.size() - 1];
    }
    
    bool Get(int index) const override {
        checkIndex(index);
        return bits[static_cast<size_t>(index)];
    }
    
    Sequence<bool>* GetSubsequence(int startIndex, int endIndex) const override {
        checkIndex(startIndex);
        checkIndex(endIndex);
        if (startIndex > endIndex) {
            throw InvalidArgumentError("BitSequence: start index > end index");
        }
        
        BitSequence* result = new BitSequence();
        for (int i = startIndex; i <= endIndex; ++i) {
            result->Append(bits[static_cast<size_t>(i)]);
        }
        return result;
    }
    
    int GetLength() const override {
        return static_cast<int>(bits.size());
    }
    
    void Append(const bool& item) override {
        bits.push_back(item);
    }
    
    void Prepend(const bool& item) override {
        bits.insert(bits.begin(), item);
    }
    
    void InsertAt(const bool& item, int index) override {
        if (index < 0 || static_cast<size_t>(index) > bits.size()) {
            throw IndexOutOfRange("BitSequence: insert index out of range");
        }
        bits.insert(bits.begin() + index, item);
    }
    
    Sequence<bool>* Concat(const Sequence<bool>& other) const override {
        BitSequence* result = new BitSequence(*this);
        for (int i = 0; i < other.GetLength(); ++i) {
            result->Append(other.Get(i));
        }
        return result;
    }
    
    void Set(size_t index, bool value) {
        if (index >= bits.size()) {
            throw IndexOutOfRange("BitSequence: index out of range");
        }
        bits[index] = value;
    }
    
    bool Get(size_t index) const {
        if (index >= bits.size()) {
            throw IndexOutOfRange("BitSequence: index out of range");
        }
        return bits[index];
    }
    
    BitSequence operator&(const BitSequence& other) const {
        if (bits.size() != other.bits.size()) {
            throw InvalidArgumentError("BitSequence AND: size mismatch");
        }
        
        BitSequence result;
        for (size_t i = 0; i < bits.size(); ++i) {
            result.Append(bits[i] && other.bits[i]);
        }
        return result;
    }
    
    BitSequence operator|(const BitSequence& other) const {
        if (bits.size() != other.bits.size()) {
            throw InvalidArgumentError("BitSequence OR: size mismatch");
        }
        
        BitSequence result;
        for (size_t i = 0; i < bits.size(); ++i) {
            result.Append(bits[i] || other.bits[i]);
        }
        return result;
    }
    
    BitSequence operator^(const BitSequence& other) const {
        if (bits.size() != other.bits.size()) {
            throw InvalidArgumentError("BitSequence XOR: size mismatch");
        }
        
        BitSequence result;
        for (size_t i = 0; i < bits.size(); ++i) {
            result.Append(bits[i] != other.bits[i]);
        }
        return result;
    }
    
    BitSequence operator~() const {
        BitSequence result;
        for (size_t i = 0; i < bits.size(); ++i) {
            result.Append(!bits[i]);
        }
        return result;
    }
    
    void operator&=(const BitSequence& other) {
        *this = *this & other;
    }
    
    void operator|=(const BitSequence& other) {
        *this = *this | other;
    }
    
    void operator^=(const BitSequence& other) {
        *this = *this ^ other;
    }
};