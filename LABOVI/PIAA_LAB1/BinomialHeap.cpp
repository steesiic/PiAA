#include "BinomialHeap.h"

BinomialHeap::BinomialHeap()
{
    min = nullptr;
    trees.clear();
}

BinomialHeap::~BinomialHeap()
{
    for (Node* root : trees) 
    {
        destructorHelper(root);
    }
    trees.clear();
    min = nullptr;
}

void BinomialHeap::destructorHelper(Node* node)
{
    if (node==nullptr) 
        return;
    for (Node* tmp : node->children) 
    {
        destructorHelper(tmp);
    }
    delete node;
}

void BinomialHeap::merge(BinomialHeap& drugi)
{
    if (this == &drugi)
        return;
    trees.insert(trees.end(), drugi.trees.begin(), drugi.trees.end());

    drugi.trees.clear();
    drugi.min = nullptr;

    findMin();
    consolidate();
}
    
void BinomialHeap::insert(double value)
{
    Node* node = new Node(value);
    BinomialHeap tmp;
    tmp.trees.push_back(node);
    merge(tmp);
    //consolidate();

}

void BinomialHeap::insertPoint(const Point& p)
{
    Node* node = new Node(p);
    BinomialHeap tmp;
    tmp.trees.push_back(node);
    merge(tmp);

}

double BinomialHeap::extractMin()
{
    if (min == nullptr) 
        return 0.0;
    Node* tmpMin = min;
    trees.erase(remove(trees.begin(), trees.end(), tmpMin), trees.end());
    BinomialHeap tmp;
    tmp.trees = tmpMin->children;
    for (Node* child : tmp.trees) 
    {
        if(child!=nullptr)
            child->parent = nullptr;
    }
    merge(tmp);
    //consolidate();
    double minVal = tmpMin->value;
    delete tmpMin;
    return minVal;
}

bool BinomialHeap::extractMinPoint(Point& p)
{
    if (min == nullptr) 
        return false;
    Node* tmpMin = min;
    if (tmpMin->point == nullptr)
        return false;
    trees.erase(remove(trees.begin(), trees.end(), tmpMin), trees.end());

    BinomialHeap tmp;
    tmp.trees = tmpMin->children;
    for (Node* child : tmp.trees) 
    {
        if(child!=nullptr)
            child->parent = nullptr;
    }
    merge(tmp);
    //consolidate();
    
    p = *(tmpMin->point);
    delete tmpMin;
    return true;
}



void BinomialHeap::findMin()
{
    min = nullptr;

    for (int i = 0; i < trees.size(); i++)
    {
        if (min == nullptr || trees[i]->value < min->value)
        {
            min = trees[i];
        }
    }
}



void BinomialHeap::link(Node* tree1, Node* tree2)
{
    if (tree1->value > tree2->value)
        swap(tree1, tree2);

    tree2->parent = tree1;
    tree1->children.push_back(tree2);
    tree1->degree += 1;
}

void BinomialHeap::consolidate()
{
    if(size() == 0)
    {
        min = nullptr;
        trees.clear();
        return;
    }
    int maxDegree = floor(log2(size())) + 1;
    vector<Node*> degreeOfTrees(maxDegree + 1, nullptr);

    while (!trees.empty()) 
    {
        Node* current = trees[0];
        trees.erase(trees.begin());
        int degree = current->degree;
        while (degreeOfTrees[degree] != nullptr) 
        {
            Node* tmp = degreeOfTrees[degree];
            degreeOfTrees[degree] = nullptr;
            if (current->value < tmp->value)
                link(current, tmp);
            else 
            {
                link(tmp, current);
                current = tmp;
            }
            degree++;
        }
        degreeOfTrees[degree] = current;
    }
    trees.clear();
    for (int i = 0; i < degreeOfTrees.size(); i++) 
    {
        if (degreeOfTrees[i] != nullptr)
            trees.push_back(degreeOfTrees[i]);
    }

    findMin();
}

int BinomialHeap::countNodes(Node* node) const
{
    if (node==nullptr) 
        return 0;
    int count = 1;
    for (Node* child : node->children)
        count += countNodes(child);
    return count;
}

int BinomialHeap::size() const
{
    int br = 0;
    for (Node* root : trees)
        br += countNodes(root);
    return br;
}

void BinomialHeap::printTree(Node* root, int br) 
{
    if (root == nullptr) 
        return; 
    for (int i = 0; i < br; i++) 
        cout << " "; 
    if (root->point == nullptr)
        cout << root->value << endl; 
    else 
        cout << "(" << root->point->x << ", " << root->point->y << ") d=" << root->value << endl;
    for (Node* child : root->children) 
        printTree(child, br + 1); 
} 


void BinomialHeap::printHeap() 
{ 
    cout << "\nbinomni heap:\n";

    cout << "br el: "<< size() << endl;
    for (Node* tmp : trees)
    { 
        cout << "stablo stepena" << tmp->degree << "\n"; 
        printTree(tmp, 0); 
        cout << "\n";
    }
}





