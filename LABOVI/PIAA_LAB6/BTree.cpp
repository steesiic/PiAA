#include <iostream>
#include "BTree.h"
#include "BTreeNode.h"



void BTree::insert(int k) 
{
    if (root == nullptr) 
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else 
    {
        if (root->n == 2 * t - 1) 
        {
            BTreeNode* s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k) i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

void BTree::remove(int k) 
{
    if (!root) return;
    root->remove(k);
    if (root->n == 0) 
    {
        BTreeNode* tmp = root;
        if (root->leaf) root = nullptr;
        else root = root->C[0];
    }
}