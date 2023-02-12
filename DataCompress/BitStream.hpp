//
//  BitStream.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#ifndef BitStream_hpp
#define BitStream_hpp

#include <stdio.h>
#include <vector>

#include "Bits.hpp"


class BitStream {
public:
    BitStream() = default;
    ~BitStream() = default;
    BitStream(const BitStream&) = default;
    BitStream(BitStream&&) = default;
    BitStream& operator=(const BitStream&) = default;
    BitStream& operator=(BitStream&&) = default;

    int write(const Bits& bits);

    void rewind() {
        rd_pos = 0;
    }

    int read(Bits& outBit);

    int clear();

    int getBits() {
        return bits_size;
    }
private:
    int wr_pos = 0;
    int rd_pos = 0;
    int bits_size = 0;
    std::vector<uint8_t> mBuff = std::vector<uint8_t>(32);
};

#endif /* BitStream_hpp */
