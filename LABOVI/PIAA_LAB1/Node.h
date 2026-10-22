#pragma once
#include<vector>
#include "Point.h"
using namespace std;
class Node
{
public:
    double value;   
    Node* parent;
    vector<Node*> children;
    int degree;
    Point* point;

    Node(double val) 
    {
        value = val;
        parent = nullptr;
        children.clear();
        degree = 0;
        point = nullptr;
    };

    Node(const Point& p) 
    {
        value = p.d();
        parent = nullptr;
        children.clear();
        degree = 0;
        point = new Point(p);
    };
    
    ~Node()
    {
        if (point != nullptr)
            delete point;
    };
};

