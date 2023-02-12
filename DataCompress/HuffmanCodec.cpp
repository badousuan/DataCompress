//
//  HuffmanCodec.cpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#include "HuffmanCodec.hpp"

#include "Statistic.hpp"
#include "BitStream.hpp"

int HuffmanCodec::encode(const std::vector<char>& in, BitStream& out) {
    out.clear();
    std::vector<std::pair<char, uint32_t>> dist;
    calculateDistribution(in, dist);

    mVlcTable = VLCTable::createVLCTableFromDistribution(dist, in.size());
    mVlcTable.dump();

    for (auto &p : dist) {
        auto c = mVlcTable.getCode(p.first);
        Bits b = c.encodeBits; // todo Bits to uint64
        decodeTable[b] = c.src;
    }


    for (const auto& chr: in) {
        auto e_code = mVlcTable.getCode(chr);
        if(chr == 'd') {
            printf("");
        }
        out.write(e_code.encodeBits);
    }

    return 0;

}

int HuffmanCodec::decode(BitStream& in, std::vector<char>& out) {
    in.rewind();
    Bits bits;
    while (true) {
        Bits oneBit(0,1);
        in.read(oneBit);
        if(oneBit.bitLen != 1) {
            break;
        }
        bits.byte = (bits.byte << 1) | oneBit.byte;
        bits.bitLen ++;
        if(decodeTable.count(bits) > 0) {
            out.push_back(decodeTable[bits]);
            bits.bitLen = bits.byte = 0;
        }
    }
    return 0;
}
