//
//  main.cpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#include <iostream>
#include "Statistic.hpp"
#include "BinaryTree.hpp"
#include "VLCTable.hpp"
#include "BitStream.hpp"
#include "HuffmanCodec.hpp"

void testStatisic() {
//    const char* str = "daacbaababbaabbcbaaabaabccdeaaa";
    const char* str = "acbeapafbabbaabbcbaaabaabccdeadaaamjqqssdddssssssssssqwryrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrruiyttoyuombqqqqqqqqqqqqqqqqqqqqqnuahdddddddddddddddddddqxnnnnnnnnnnnnnnnbchksdbhrrnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnmvkldvjnthubhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhv";



    const std::vector<char> src_data(str, str+strlen(str));

    HuffmanCodec hCodec;
    BitStream encoded_bs;
    hCodec.encode(src_data, encoded_bs);
    std::vector<char> decoded_char;
    hCodec.decode(encoded_bs, decoded_char);

    if(memcmp(src_data.data(), decoded_char.data(), src_data.size())) {
        printf("codec error\n");
    }
    decoded_char.push_back(0);
    float q = encoded_bs.getBits()/8.0/src_data.size();
    printf("decoded_char:%s\n q = %f \n",decoded_char.data(),q);

}




int main(int argc, const char * argv[]) {
    testStatisic();
    return 0;
}
