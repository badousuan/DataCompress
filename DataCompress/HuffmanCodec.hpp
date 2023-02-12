//
//  HuffmanCodec.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#ifndef HuffmanCodec_hpp
#define HuffmanCodec_hpp

#include <stdio.h>
#include <vector>
#include <map>

#include "VLCTable.hpp"

class BitStream;
struct Bits;
class HuffmanCodec {
public:
    HuffmanCodec(){};
    int encode(const std::vector<char>& in, BitStream& out);
    int decode(BitStream& in, std::vector<char>& out);
    const VLCTable& getVLCTable() {
        return mVlcTable;
    }
private:
    VLCTable mVlcTable;
    std::map<Bits, char> decodeTable;
};

#endif /* HuffmanCodec_hpp */


