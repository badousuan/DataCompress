//
//  Statistic.cpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#include "Statistic.hpp"

// 计算char数据集src_data的概率分布
void calculateDistribution(const std::vector<char>& src_data, std::vector<uint32_t>& destDistribution) {
    destDistribution.resize(UINT8_MAX,0);

    auto p = destDistribution.data();
    auto d = src_data.data();
    for (size_t i = 0; i < src_data.size(); i++) {
        p[d[i]]++;
    }

}
// 计算char数据集src_data的有大到小概率分布,由小到大
void calculateDistribution(const std::vector<char>& src_data, std::vector<std::pair<char, uint32_t>>& distribution) {
    distribution.resize(0);
    std::vector<uint32_t> all_distribution(UINT8_MAX,0);
    calculateDistribution(src_data, all_distribution);

    for(int i = 0;i < UINT8_MAX; i++) {
        if(all_distribution[i] != 0) {
            distribution.push_back(std::make_pair(i, all_distribution[i]));
        }
    }

    auto cmp_func = []  (const std::pair<char, uint32_t>& a, const std::pair<char, uint32_t>& b) {
        return a.second < b.second;
    };

    std::sort(distribution.begin(), distribution.end(), cmp_func);

}
