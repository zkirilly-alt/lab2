#pragma once
#include "Sequence.hpp"
#include "Exception.hpp"
#include <cstddef>
#include <cstring>
#include <cstdint>

class BitSequence : public Sequence<bool> {
private:
    uint8_t* data;
    size_t numBits;
    size_t numBytes;

    void allocate(size_t bits);
    void copyFrom(const BitSequence& other);
    void free();
    void checkIndex(int index) const;
    void setBit(size_t index, bool value);
    bool getBit(size_t index) const;
    void setBitInArray(uint8_t* arr, size_t index, bool value) const;

public:
    BitSequence();
    explicit BitSequence(size_t size);
    BitSequence(const bool* items, int count);
    BitSequence(const BitSequence& other);
    BitSequence(BitSequence&& other) noexcept;
    ~BitSequence();
    BitSequence& operator=(const BitSequence& other);
    BitSequence& operator=(BitSequence&& other) noexcept;

    bool GetFirst() const override;
    bool GetLast() const override;
    bool Get(int index) const override;
    Sequence<bool>* GetSubsequence(int startIndex, int endIndex) const override;
    int GetLength() const override;
    void Append(const bool& item) override;
    void Prepend(const bool& item) override;
    void InsertAt(const bool& item, int index) override;
    Sequence<bool>* Concat(const Sequence<bool>& other) const override;
    void RemoveAt(int index) override;
    void Clear() override;

    void Set(size_t index, bool value);
    bool Get(size_t index) const;

    BitSequence operator&(const BitSequence& other) const;
    BitSequence operator|(const BitSequence& other) const;
    BitSequence operator^(const BitSequence& other) const;
    BitSequence operator~() const;
    void operator&=(const BitSequence& other);
    void operator|=(const BitSequence& other);
    void operator^=(const BitSequence& other);
};