#include "BinomialHeap.h"
#include "Node.h"
#include<vector>
#include <cstdlib>
#include <ctime>
#include "Point.h"
#include <algorithm>
#include <iostream>
using namespace std;

int RandomNumber(int x, int y) 
{
	return rand() % (y - x + 1) + x;
}
float PointRandomNumber(int x, int y) 
{
	return (float)RandomNumber(x, y) + (RandomNumber(0, 10) / 10.0f);
}

bool AreCollinear(const Point& p1, const Point& p2, const Point& p3)
{
	return abs((p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x)) < 0.0001f;
}

bool Compatibility(Point& a, Point& b, Point& c) 
{
	double x = a.PointDistance(b);
	double y = b.PointDistance(c);
	double z = c.PointDistance(a);

	if (x + y > z && x + z > y && y + z > x && !AreCollinear(a, b, c))
		return true;
	return false;
}


int main() 
{
	//prvi deo zadatka:
	int N, k;

	std::cout << "Unesite vrednosti za N i k tako da vazi:" << endl;
	std::cout << "10 <= N <= 10.000.000 " << endl;
	std::cout << "N = ";
	std::cin >> N;
	std::cout << endl;
	std::cout << "10 <= k <= 100" << endl;
	std::cout << "k = ";
	std::cin >> k;
	std::cout << endl;

	srand(time(nullptr));

	int minVr, maxVr;
	std::cout << "Unesite opseg brojeva minVr i maxVr: " << endl;
	std::cout << "minVr = ";
	std::cin >> minVr;
	std::cout << endl;
	std::cout << "maxVr = ";
	std::cin >> maxVr;
	std::cout << endl;

	/*BinomialHeap heap;
	int count = 0;
	while(heap.size()<N)
	{
		int g = RandomNumber(minVr, maxVr);
		std::cout << g << endl;
		heap.insert(g);
		count++;
		if (count == k) 
		{
			std::cout<< "izbacen je "<<heap.extractMin() << endl;
			count = 0;
		}
	}

	std::cout << "\n\n\n\n";*/


	//rad sa tackama
	BinomialHeap points;
	int count2 = 0;
	while (points.size() < N)
	{
		Point tmp(Point(PointRandomNumber(minVr, maxVr), PointRandomNumber(minVr, maxVr)));

		std::cout << tmp << endl;
		points.insertPoint(tmp);

		count2++;
		if (count2 == k)
		{
			Point tmp2;
			points.extractMinPoint(tmp2);
			std::cout << "\nizbacen je " << tmp2 << "\n" << endl;

			count2 = 0;
		}
	}

	bool found = false;
	vector<Point> pointsExtracted;

	while (!found && points.size() > 0)
	{
		Point curr;
		bool flag = points.extractMinPoint(curr);
		if (!flag) break;

		int m = pointsExtracted.size();
		for (int i = 0; i < m; i++)
		{
			if (found)
				break;
			for (int j = i + 1; j < m; j++)
			{
				if (found)
					break;
				if (Compatibility(pointsExtracted[i], pointsExtracted[j], curr))
				{
					std::cout << "\n\ntri tacke najblize pocetku koje formiraju trougao su:\n";
					std::cout << "A: " << pointsExtracted[i] << "\n";
					std::cout << "B: " << pointsExtracted[j] << "\n";
					std::cout << "C: " << curr << "\n";
					found = true;
				}
			}
		}

		if (!found)
		{
			pointsExtracted.push_back(curr);
		}
	}

	if (!found)
	{
		std::cout << "\n ne postoje 3 tacke iz skupa koje formiraju trougao!";
	}

	points.printHeap();
	
	return 0;
}