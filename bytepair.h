/******************************************************************************
 * File Name    : fusebyte.h
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Perfect Bit Sequence
 * Versiyon     : 1.0.0
 ******************************************************************************/

#ifndef BYTEPAIR_H
#define BYTEPAIR_H

#include <array>
#include <bitset>
#include <tuple>
#include <vector>

class BytePair final
{
public:
    explicit BytePair();
    ~BytePair();

    std::tuple<uint8_t, uint8_t> encodeBytes(const uint8_t &byteA, const uint8_t &byteB);
    std::tuple<uint8_t, uint8_t> decodeBytes(const uint8_t &byteA, const uint8_t &byteB);

public:
    std::array<std::array<uint8_t, 8>, 8> createByteTable();
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> createByteCubeX(
        std::array<std::array<uint8_t, 8>, 8> values);
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> createByteCubeY(
        std::array<std::array<uint8_t, 8>, 8> values);
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> findDimensionSet(
                const std::array<std::array<std::array<uint8_t, 8>, 8>, 8> &cube,
                const uint8_t &byte);
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> findMutualDimension(std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>
            setA,
            std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> setB);
    std::tuple<uint8_t, std::bitset<2>> sanitizeByte(const uint8_t &byte);
    uint8_t findAccurateByte(const uint8_t &byte, const std::bitset<2> &region);

private:
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> byteCubeX;
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> byteCubeY;
};

#endif // BYTEPAIR_H
