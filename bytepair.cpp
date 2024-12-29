/******************************************************************************
 * File Name    : bytepair.cpp
 * Coder        : Aziz Gökhan NARİN
 * E-Mail       : azizgokhannarin@yahoo.com
 * Explanation  : Intersecting Byte Pairs
 * Versiyon     : 1.0.0
 ******************************************************************************/

#include "bytepair.h"

#include <iostream>
#include <algorithm>

BytePair::BytePair()
{
    byteCubeX = createByteCubeX(createByteTable());
    byteCubeY = createByteCubeY(createByteTable());
}

BytePair::~BytePair()
{

}

std::array<std::array<uint8_t, 8>, 8> BytePair::createByteTable()
{
    std::array<std::array<uint8_t, 8>, 8> table;

    for (size_t y = 0, counter = 0; y < 8; y++) {
        for (size_t x = 0; x < 8; x++, counter++) {
            table[x][y] = counter;
        }
    }

    return table;
}

std::array<std::array<std::array<uint8_t, 8>, 8>, 8>
BytePair::createByteCubeX(std::array<std::array<uint8_t, 8>, 8> values)
{
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> cube;

    for (size_t z = 0; z < 8; z++) {
        for (size_t y = 0; y < 8; y++) {
            for (size_t x = 0; x < 8; x++) {
                cube[x][(x + z) % 8][y] = values[x][y];
            }
        }
    }

    return cube;
}

std::array<std::array<std::array<uint8_t, 8>, 8>, 8>
BytePair::createByteCubeY(std::array<std::array<uint8_t, 8>, 8> values)
{
    std::array<std::array<std::array<uint8_t, 8>, 8>, 8> cube;

    for (size_t z = 0; z < 8; z++) {
        for (size_t y = 0; y < 8; y++) {
            for (size_t x = 0; x < 8; x++) {
                cube[z][x][(y + z) % 8] = values[y][x];
            }
        }
    }

    return cube;
}

std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>
        BytePair::findDimensionSet(const
                                   std::array<std::array<std::array<uint8_t, 8>, 8>, 8> &cube,
                                   const uint8_t &byte)
{
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> possibilities;

    for (size_t z = 0; z < 8; z++) {
        for (size_t y = 0; y < 8; y++) {
            for (size_t x = 0; x < 8; x++) {
                if (cube[z][x][y] == byte) {
                    possibilities.push_back(std::make_tuple(z, x, y));
                }
            }
        }
    }

    return possibilities;
}

std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> BytePair::findMutualDimension(
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>>
    setA, std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> setB)
{
    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> dimension;

    for (uint8_t i = 0; i < setA.size(); i++) {
        for (uint8_t j = 0; j < setB.size(); j++) {
            if (std::get<1>(setA[i]) == std::get<1>(setB[j]) && std::get<2>(setA[i]) == std::get<2>(setB[j])) {
                dimension = std::make_tuple(std::get<1>(setA[i]), std::get<2>(setA[i]),
                                            std::get<0>(setA[i]), std::get<0>(setB[j]));
                goto endloop;
                break;
            }
        }
    }

endloop:
    return dimension;
}

std::tuple<uint8_t, std::bitset<2>> BytePair::sanitizeByte(const uint8_t &byte)
{
    if (byte <= 63) {
        return std::make_tuple(byte, std::bitset<2>(0));
    } else if (64 <= byte && byte <= 127) {
        return std::make_tuple(byte - 64, std::bitset<2>(1));
    } else if (128 <= byte && byte <= 195) {
        return std::make_tuple(byte - 128, std::bitset<2>(2));
    } else {
        return std::make_tuple(byte - 196, std::bitset<2>(3));
    }
}

uint8_t BytePair::findAccurateByte(const uint8_t &byte, const std::bitset<2> &region)
{
    if (region.to_ulong() == 0) {
        return byte;
    } else if (region.to_ulong() == 1) {
        return byte + 64;
    } else if (region.to_ulong() == 2) {
        return byte + 128;
    } else {
        return byte + 196;
    }
}

std::tuple<uint8_t, uint8_t> BytePair::encodeBytes(const uint8_t &byteA, const uint8_t &byteB)
{
    std::tuple<uint8_t, std::bitset<2>> sanitizedByteA = sanitizeByte(byteA);
    std::tuple<uint8_t, std::bitset<2>> sanitizedByteB = sanitizeByte(byteB);

    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> setByteA = findDimensionSet(byteCubeX, std::get<0>(sanitizedByteA));
    std::vector<std::tuple<uint8_t, uint8_t, uint8_t>> setByteB = findDimensionSet(byteCubeY, std::get<0>(sanitizedByteB));

    std::tuple<uint8_t, uint8_t, uint8_t, uint8_t> mutualDimension = findMutualDimension(setByteA, setByteB);

    std::bitset<3> dimensionX(std::get<0>(mutualDimension));
    std::bitset<3> dimensionY(std::get<1>(mutualDimension));
    std::bitset<3> dimensionZ1(std::get<2>(mutualDimension));
    std::bitset<3> dimensionZ2(std::get<3>(mutualDimension));
    std::bitset<2> regionA = std::get<1>(sanitizedByteA);
    std::bitset<2> regionB = std::get<1>(sanitizedByteB);

    std::bitset<16> bitArray(dimensionX.to_ulong() << 13 | dimensionY.to_ulong() << 10 | dimensionZ1.to_ulong() << 7 |
                             dimensionZ2.to_ulong() << 4 | regionA.to_ulong() << 2 | regionB.to_ulong());
    return std::make_tuple(bitArray.to_ulong() >> 8, bitArray.to_ulong());
}

std::tuple<uint8_t, uint8_t> BytePair::decodeBytes(const uint8_t &byteA, const uint8_t &byteB)
{
    uint16_t merged = (static_cast<uint16_t>(byteA) << 8) | byteB;

    uint8_t dimensionX = (merged >> 13) & 0b00000111;
    uint8_t dimensionY = (merged >> 10) & 0b00000111;
    uint8_t dimensionZ1 = (merged >> 7) & 0b00000111;
    uint8_t dimensionZ2 = (merged >> 4) & 0b00000111;
    uint8_t regionA = (merged >> 2) & 0b00000011;
    uint8_t regionB = merged & 0b00000011;

    uint8_t accurateByteA = findAccurateByte(byteCubeX[dimensionZ1][dimensionX][dimensionY], regionA);
    uint8_t accurateByteB = findAccurateByte(byteCubeY[dimensionZ2][dimensionX][dimensionY], regionB);

    return std::make_tuple(accurateByteA, accurateByteB);
}
