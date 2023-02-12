//
//  BinaryTree.hpp
//  DataCompress
//
//  Created by Lei Yue on 2023/2/4.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include <stdio.h>
#include <list>
template <typename T>
struct Node {
    char key = 0;
    T val;
    struct Node* left = NULL;
    struct Node* right = NULL;
    struct Node* parent = NULL;
    bool isLeave(){
        return !right && !left;
    }
    bool isRoot(){
        return !parent;
    }
};

//左序遍历 中-左-右
template <typename T>
static void leftTravel(Node<T> *tree )
{
    if(tree){
        printf("%c[%d],",tree->key,(int)(tree->val));
        if(tree->left){
            leftTravel(tree->left);
        }
        if(tree->right){
            leftTravel(tree->right);
        }
    }
}

//中序遍历 左-中-右
template <typename T>
static void middleTravel(Node<T> *tree) {
    if(tree){
        if(tree->left){
            middleTravel(tree->left);
        }
        printf("%c[%d],",tree->key,(int)(tree->val));
        if(tree->right){
            middleTravel(tree->right);
        }

    }
}

//后序遍历 左-右-中
template <typename T>
static void rightTravel(Node<T> *tree) {
    if(tree){
        if(tree->left){
            rightTravel(tree->left);
        }

        if(tree->right){
            rightTravel(tree->right);
        }

        printf("%c[%d],",tree->key,(int)(tree->val));
    }
}

//层次遍历
template <typename T>
static void levelTravel(Node<T> *tree) {
    std::vector<std::vector<Node<T>*>> all_node;
    if(tree){
        std::vector<Node<T>*> root(1);
        root[0] = tree;
        all_node.push_back(root);
        while(all_node[all_node.size()-1].size() > 0) {
            std::vector<Node<T>*>& lastlevel = all_node[all_node.size()-1];
            std::vector<Node<T>*> level_i_list;
            for (const auto& tree : lastlevel) {
                if(tree->left) {
                    level_i_list.push_back(tree->left);
                }
                if(tree->right) {
                    level_i_list.push_back(tree->right);
                }
            }
            all_node.push_back(level_i_list);
        }
        for (const auto& node_l : all_node) {
            printf("\n");
            for (const auto& node : node_l) {
                printf("%c[%d],",node->key,(int)(node->val));
            }
        }
    }
}


////层次遍历
//template <typename T>
//static void levelTravel(Node<T> *tree) {
//
//    struct NodePath {
//        Node<T> *node = nullptr;
//        std::vector<uint8_t> path;
//        NodePath(Node<T> *n) {
//            node = n;
//        }
//        NodePath() {
//            node = NULL;
//        }
//    };
//
//
//    std::vector<std::vector<NodePath>> all_node;
//    if(tree){
//        while(tree->left || tree->right) {
//            std::vector<NodePath> level_i_list;
//            if(tree->left) {
//                NodePath np = {tree->left};
//                np.path = tree-
//                level_i_list.push_back(np);
//            }
//            if(tree->right) {
//                level_i_list.push_back(tree->right);
//            }
//        }
//
//    }
//}


#endif /* BinaryTree_hpp */
