#pragma once
#include <iostream>
#include<math.h>
using namespace std;
class Point
{
public:
	float x;
	float y;

	Point() 
	{
		x = 0.0f;
		y = 0.0f;
	}

	Point(float a, float b) 
	{
		x = a;
		y = b;
	};


	float d()const
	{
		return sqrt(x*x + y*y);
	};
	
	

	friend ostream& operator<<(ostream& izlaz, const Point& obj) 
	{
		izlaz << obj.x << " " << obj.y<< "  d =  "<<obj.d();
		return izlaz;
	}

	double PointDistance(Point& drugi) 
	{
		return sqrt((drugi.x - this->x) * (drugi.x - this->x) + (drugi.y-this->y) * (drugi.y - this->y));
	}
};

