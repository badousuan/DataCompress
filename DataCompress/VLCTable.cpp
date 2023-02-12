//
//  VLCTable.cpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#include "VLCTable.hpp"


const CodePair VLCTable::invalidCodePair = CodePair();



void VLCTable::addCodePair(const struct CodePair& code_p) {
    src.insert(code_p.src);
    table[(uint8_t)code_p.src] = code_p;
}


const struct CodePair& VLCTable::getCode(char src_code) {
    if(src.count(src_code) > 0) {
        return table[src_code];
    } else {
        return invalidCodePair;
    }
}


void VLCTable::dump(){
    for (const auto& ct: src) {
        printf("%c:",table[ct].src);
        for (int i = 0; i < table[ct].encodeBits.bitLen; i++) {
            printf("%d",int(0x01&(table[ct].encodeBits.byte >> (table[ct].encodeBits.bitLen - i - 1))));
        }
        printf("\n");
    }
}


VLCTable VLCTable::createVLCTableFromDistribution(const std::vector<std::pair<char, uint32_t>>& distribution, uint32_t src_cnt) {
    VLCTable vlcTable;
    auto cnt = distribution.size();
    if(cnt <=2) {
        for (int i = 0; i < cnt; i++) {
            CodePair p;
            p.src = distribution[i].first;
            p.encodeBits.byte = i;
            p.encodeBits.bitLen = 1;
            vlcTable.addCodePair(std::move(p));
        }
    } else {

        //左小右大
        std::vector<Node<int>*> dis_tree; // for delete
        std::vector<Node<int>*> leave;
        Node<int>* node_l = new Node<int>();
        node_l->key = distribution[0].first;
        node_l->val = distribution[0].second;
        leave.push_back(node_l);
        dis_tree.push_back(node_l);
        Node<int>* node_r = new Node<int>();
        node_r->key = distribution[1].first;
        node_r->val = distribution[1].second;
        leave.push_back(node_r);
        dis_tree.push_back(node_r);
        int cur_sum = node_l->val + node_r->val;
        for (int i = 2; i < cnt; i++) {

            if(cur_sum >= src_cnt-cur_sum) {
                Node<int>*  new_node_l = new Node<int>();
                new_node_l->key = distribution[i].first;
                new_node_l->val = distribution[i].second;

                Node<int>*  new_node_r =  new Node<int>();
                new_node_r->val = cur_sum;
                new_node_r->left = node_l;
                new_node_r->right = node_r;
                node_l->parent = new_node_r;
                node_r->parent = new_node_r;
                node_l = new_node_l;
                node_r = new_node_r;
            } else {
                Node<int>*  new_node_r = new Node<int>();
                new_node_r->key = distribution[i].first;
                new_node_r->val = distribution[i].second;

                Node<int>*  new_node_l =  new Node<int>();
                new_node_l->val = cur_sum;
                new_node_l->left = node_l;
                new_node_l->right = node_r;
                node_l->parent = new_node_l;
                node_r->parent = new_node_l;
                node_l = new_node_l;
                node_r = new_node_r;
            }
            cur_sum = node_l->val + node_r->val;
            dis_tree.push_back(node_l);
            dis_tree.push_back(node_r);
            if(node_l->isLeave()){
                leave.push_back(node_l);
            }
            if(node_r->isLeave()){
                leave.push_back(node_r);
            }
        }
        Node<int>* root = new Node<int>();
        root->left = node_l;
        root->right = node_r;
        root->val = src_cnt;
        node_l->parent = root;
        node_r->parent = root;
        dis_tree.push_back(root);
        if(node_l->isLeave()){
            leave.push_back(node_l);
        }
        if(node_r->isLeave()){
            leave.push_back(node_r);
        }
        //leftTravel(root);
        //levelTravel(root);
        for (auto& c : leave) {
            std::stack<uint8_t> e_code;
            uint64_t e_codex = 0;
            int len = 0;
            auto tmp = c->key;
            while (c && c->parent) {
                if(c->parent->left == c) {
                    e_code.push(0);
                    e_codex |= 0;
                } else if(c->parent->right == c) {
                    e_code.push(1);
                    e_codex |= ((uint64_t)1)<<len;
                }
                len++;
                c = c->parent;
            }
            CodePair p;
            p.src = tmp;
            p.encodeBits.byte = e_codex;
            p.encodeBits.bitLen = len;
            vlcTable.addCodePair(std::move(p));
        }

        for (auto node : dis_tree) {
            delete node;
        }
    }

    return vlcTable;
}

