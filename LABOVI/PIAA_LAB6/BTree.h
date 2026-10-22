#pragma once
#include "BTreeNode.h"

class BTree 
{
    BTreeNode* root;
    int t;

public:
    BTree(int _t) 
    {
        root = nullptr;
        t = _t;
    }

    void insert(int k);
    void remove(int k);

    bool contains(int k) 
    {
        if (root == nullptr) return false;
        return (root->search(k) != nullptr);
    }
};
