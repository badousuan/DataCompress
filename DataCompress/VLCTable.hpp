//
//  VLCTable.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#ifndef VLCTable_hpp
#define VLCTable_hpp

#include <stdio.h>
#include <vector>
#include <set>
#include <memory>
#include <stack>

#include "BinaryTree.hpp"
#include "Bits.hpp"

struct CodePair {
public:
    char src = 0; //源码
    Bits encodeBits;

    CodePair()=default;
    CodePair(const  CodePair&)=default;
    CodePair(CodePair&&)=default;
    CodePair& operator=(const  CodePair& that){
        src = that.src;
        encodeBits = that.encodeBits;
        return *this;
    }

    CodePair& operator=(CodePair&& that) {
        src = that.src;
        encodeBits = that.encodeBits;
        return *this;
    }
};

class VLCTable {
public:

    VLCTable(){
        table = std::vector<struct CodePair>(UINT8_MAX);
    }


    void addCodePair(const struct CodePair& code_p);


    const struct CodePair& getCode(char src_code);

    void dump();

    static VLCTable createVLCTableFromDistribution(const std::vector<std::pair<char, uint32_t>>& distribution, uint32_t src_cnt);

    const std::vector<struct CodePair>& geCodeTable() {
        return table;
    }
    
private:
    std::set<char> src;
    std::vector<struct CodePair> table;
    static const CodePair invalidCodePair;
};

#endif /* VLCTable_hpp */
