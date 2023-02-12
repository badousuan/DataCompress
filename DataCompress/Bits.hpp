//
//  Bits.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/12.
//

#ifndef Bits_hpp
#define Bits_hpp

#include <stdio.h>
#include <stdlib.h>

struct Bits {
    uint64_t byte = 0;
    uint64_t bitLen = 0; //0~8,LSB对齐
    Bits(uint64_t data, uint64_t len) {
        byte = data;
        bitLen = len;
    }

    Bits(){
        byte = 0;
        bitLen = 0;
    }

    Bits(const  Bits& that)=default;

    Bits(Bits&& that)=default;
    
    Bits& operator=(const Bits& that)=default;

    Bits& operator=(Bits&& that)=default;

    bool operator==(const Bits& that) const{
        return byte == that.byte
                && bitLen == that.bitLen;
    }

    bool operator!=(const Bits& that) const {
        return !(*this == that);
    }

    bool operator < (const Bits& that) const {
        if( bitLen < that.bitLen ) {
            return true;
        } else {
            return byte < that.byte;
        }
    }

};

#endif /* Bits_hpp */
