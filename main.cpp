#include <iostream>
#include <algorithm>
#include <unordered_map>

#include "bytepair.h"


int main()
{
    BytePair bytePair;


    for (size_t i = 0; i < 256; i++) {
        for (size_t j = 0; j < 256; j++) {
            std::tuple<uint8_t, uint8_t> encodedBytePairs = bytePair.encodeBytes(i, j);
            std::tuple<uint8_t, uint8_t> decodedBytePairs = bytePair.decodeBytes(std::get<0>(encodedBytePairs),
                    std::get<1>(encodedBytePairs));

            std::cout << " Byte 1 = " << i << "  Byte 2 = " << j << " ";
            std::cout << " Encoded Byte 1 = " << static_cast<int>(std::get<0>(encodedBytePairs)) << " ";
            std::cout << " Encoded Byte 2 = " << static_cast<int>(std::get<1>(encodedBytePairs)) << " ";
            std::cout << " Decoded Byte 1 = " << static_cast<int>(std::get<0>(decodedBytePairs)) << " ";
            std::cout << " Decoded Byte 2 = " << static_cast<int>(std::get<1>(decodedBytePairs)) << " ";
            std::cout << std::endl;
        }
    }

    return 0;
}
