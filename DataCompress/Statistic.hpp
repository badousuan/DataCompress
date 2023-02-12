//
//  Statistic.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#ifndef Statistic_hpp
#define Statistic_hpp

#include <stdio.h>
#include <vector>

// 计算char数据集src_data的概率分布
extern  void calculateDistribution(const std::vector<char>& src_data, std::vector<uint32_t>& destDistribution);

// 计算char数据集src_data的有大到小概率分布
extern void calculateDistribution(const std::vector<char>& src_data, std::vector<std::pair<char, uint32_t>>& distribution);

#endif /* Statistic_hpp */
