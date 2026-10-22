#pragma once
#include "Node.h"
#include <vector>
#include <algorithm>

using namespace std;

class BinomialHeap
{
public:
    vector<Node*> trees;
    Node* min;

    // konstruktor
    BinomialHeap();

    //destruktor
    ~BinomialHeap();

    //pomocna f-ja za destr.
    void destructorHelper(Node* node);

    // spaja 2 binomna heapa
    void merge(BinomialHeap& drugi);

    // dodavanje nove vrednosti(cvora) u heap
    void insert(double value);

    //dodavanje nove tacke u heap
    void insertPoint(const Point& p);

    // izbacuje cvor s minimalnom vrednoscu i vraca tu vrednost
    double extractMin();

    bool extractMinPoint(Point& p);

    // trazi minimum u heapu
    void findMin();
    // povezuje 2 stabla
    void link(Node* tree1, Node* tree2);

    // konsoliduje sve sukobe  istog stepena
    void consolidate();

    // velicina heapa
    int size() const;
    int countNodes(Node* node) const;

    //stampanje heapa

    void printHeap(); 
    void printTree(Node* root, int br);

};

