#include "BitSequence.hpp"
#include <cstring>

void BitSequence::allocate(size_t bits)
{
    numBits = bits;
    numBytes = (bits + 7) / 8;
    data = bits ? new uint8_t[numBytes]() : nullptr;
}

void BitSequence::copyFrom(const BitSequence &other)
{
    allocate(other.numBits);
    if (numBytes)
        std::memcpy(data, other.data, numBytes);
}

void BitSequence::free()
{
    delete[] data;
    data = nullptr;
    numBits = 0;
    numBytes = 0;
}

void BitSequence::checkIndex(int index) const
{
    if (index < 0 || static_cast<size_t>(index) >= numBits)
        throw IndexOutOfRange(index, numBits);
}

void BitSequence::setBit(size_t index, bool value)
{
    size_t byteIdx = index >> 3;
    size_t bitIdx = index & 7;
    uint8_t mask = uint8_t(1u << bitIdx);
    if (value)
        data[byteIdx] |= mask;
    else
        data[byteIdx] &= ~mask;
}

bool BitSequence::getBit(size_t index) const
{
    size_t byteIdx = index >> 3;
    size_t bitIdx = index & 7;
    return (data[byteIdx] >> bitIdx) & 1u;
}

void BitSequence::setBitInArray(uint8_t *arr, size_t index, bool value) const
{
    size_t byteIdx = index >> 3;
    size_t bitIdx = index & 7;
    uint8_t mask = uint8_t(1u << bitIdx);
    if (value)
        arr[byteIdx] |= mask;
    else
        arr[byteIdx] &= ~mask;
}

BitSequence::BitSequence() : data(nullptr), numBits(0), numBytes(0) {}
BitSequence::BitSequence(size_t size) { allocate(size); }

BitSequence::BitSequence(const bool *items, int count)
{
    allocate(count);
    for (int i = 0; i < count; ++i)
        setBit(i, items[i]);
}

BitSequence::BitSequence(const BitSequence &other)
{
    copyFrom(other);
}

BitSequence::BitSequence(BitSequence &&other) noexcept
    : data(other.data), numBits(other.numBits), numBytes(other.numBytes)
{
    other.data = nullptr;
    other.numBits = 0;
    other.numBytes = 0;
}

BitSequence::~BitSequence()
{
    free();
}

BitSequence &BitSequence::operator=(const BitSequence &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

BitSequence &BitSequence::operator=(BitSequence &&other) noexcept
{
    if (this != &other)
    {
        free();
        data = other.data;
        numBits = other.numBits;
        numBytes = other.numBytes;
        other.data = nullptr;
        other.numBits = 0;
        other.numBytes = 0;
    }
    return *this;
}

bool BitSequence::GetFirst() const
{
    if (!numBits)
        throw EmptyContainerError("BitSequence::GetFirst: последовательность пуста");
    return getBit(0);
}

bool BitSequence::GetLast() const
{
    if (!numBits)
        throw EmptyContainerError("BitSequence::GetLast: последовательность пуста");
    return getBit(numBits - 1);
}

bool BitSequence::Get(int index) const
{
    checkIndex(index);
    return getBit(index);
}

Sequence<bool> *BitSequence::GetSubsequence(int startIndex, int endIndex) const
{
    checkIndex(startIndex);
    checkIndex(endIndex);
    if (startIndex > endIndex)
        throw InvalidArgumentError("BitSequence::GetSubsequence: начальный индекс больше конечного");

    int newSize = endIndex - startIndex + 1;
    BitSequence *result = new BitSequence(newSize);
    for (int i = 0; i < newSize; ++i)
        result->setBit(i, getBit(startIndex + i));
    return result;
}

int BitSequence::GetLength() const
{
    return int(numBits);
}

void BitSequence::Append(const bool &item)
{
    size_t newBits = numBits + 1;
    size_t newBytes = (newBits + 7) / 8;
    uint8_t *newData = new uint8_t[newBytes]();
    if (data)
        std::memcpy(newData, data, numBytes);
    delete[] data;
    data = newData;
    numBits = newBits;
    numBytes = newBytes;
    setBit(numBits - 1, item);
}

void BitSequence::Prepend(const bool &item)
{
    size_t newBits = numBits + 1;
    size_t newBytes = (newBits + 7) / 8;
    uint8_t *newData = new uint8_t[newBytes]();
    for (size_t i = 0; i < numBits; ++i)
        setBitInArray(newData, i + 1, getBit(i));
    setBitInArray(newData, 0, item);
    delete[] data;
    data = newData;
    numBits = newBits;
    numBytes = newBytes;
}

void BitSequence::InsertAt(const bool &item, int index)
{
    if (index < 0 || size_t(index) > numBits)
        throw IndexOutOfRange(index, numBits + 1);

    size_t newBits = numBits + 1;
    size_t newBytes = (newBits + 7) / 8;
    uint8_t *newData = new uint8_t[newBytes]();

    for (int i = 0; i < index; ++i)
        setBitInArray(newData, i, getBit(i));

    setBitInArray(newData, index, item);

    for (size_t i = index; i < numBits; ++i)
        setBitInArray(newData, i + 1, getBit(i));

    delete[] data;
    data = newData;
    numBits = newBits;
    numBytes = newBytes;
}

Sequence<bool> *BitSequence::Concat(const Sequence<bool> &other) const
{
    BitSequence *result = new BitSequence(*this);
    for (int i = 0; i < other.GetLength(); ++i)
        result->Append(other.Get(i));
    return result;
}

void BitSequence::RemoveAt(int index)
{
    checkIndex(index);
    BitSequence newSeq(numBits - 1);
    int pos = 0;
    for (size_t i = 0; i < numBits; ++i)
        if (i != size_t(index))
            newSeq.setBit(pos++, getBit(i));
    *this = std::move(newSeq);
}

void BitSequence::Clear()
{
    free();
}

void BitSequence::Set(size_t index, bool value)
{
    if (index >= numBits)
        throw IndexOutOfRange(index, numBits);
    setBit(index, value);
}

bool BitSequence::Get(size_t index) const
{
    if (index >= numBits)
        throw IndexOutOfRange(index, numBits);
    return getBit(index);
}

BitSequence BitSequence::operator&(const BitSequence &other) const
{
    if (numBits != other.numBits)
        throw LengthMismatchException("BitSequence::operator&: размеры не совпадают");
    BitSequence result(numBits);
    for (size_t i = 0; i < numBits; ++i)
        result.setBit(i, getBit(i) & other.getBit(i));
    return result;
}

BitSequence BitSequence::operator|(const BitSequence &other) const
{
    if (numBits != other.numBits)
        throw LengthMismatchException("BitSequence::operator|: размеры не совпадают");
    BitSequence result(numBits);
    for (size_t i = 0; i < numBits; ++i)
        result.setBit(i, getBit(i) | other.getBit(i));
    return result;
}

BitSequence BitSequence::operator^(const BitSequence &other) const
{
    if (numBits != other.numBits)
        throw LengthMismatchException("BitSequence::operator^: размеры не совпадают");
    BitSequence result(numBits);
    for (size_t i = 0; i < numBits; ++i)
        result.setBit(i, getBit(i) ^ other.getBit(i));
    return result;
}

BitSequence BitSequence::operator~() const
{
    BitSequence result(numBits);
    for (size_t i = 0; i < numBits; ++i)
        result.setBit(i, !getBit(i));
    return result;
}

void BitSequence::operator&=(const BitSequence &other)
{
    *this = *this & other;
}

void BitSequence::operator|=(const BitSequence &other)
{
    *this = *this | other;
}

void BitSequence::operator^=(const BitSequence &other)
{
    *this = *this ^ other;
}