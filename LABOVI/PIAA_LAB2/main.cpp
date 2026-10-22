#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime> 
#include <algorithm>
#include <iostream>
using namespace std;
struct Point
{
	double x, y;

	bool operator == (const Point& point) const
	{
		return (x == point.x && y == point.y);
	}
	bool operator<(const Point& other) const //dodato da moze da se nadje min pomocu min_element f-je
	{
		return (y < other.y) || (y == other.y && x < other.x);
	}
	friend ostream& operator<<(ostream& izlaz, const Point& obj)
	{
		izlaz << "(" << obj.x << ", " << obj.y << ")";
		return izlaz;
	}
};


Point p0;

int orientation(Point a, Point b, Point c)  
{
	double V = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
	if (V < 0)
		return -1; //clockwise
	if (V > 0)
		return 1; //counter clockwise
	return 0;	//collinear
}

double distSquared(Point a, Point b) 
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool compare(const Point& a, const Point& b) 
{
	int orient = orientation(p0, a, b);
	if (orient == 0)
		return distSquared(p0, a) < (distSquared(p0, b));
	return orient < 0;
}

vector<Point> findConvexHull(const vector<Point>& points)	//graham's scan
{
	int n = points.size();
	if (n < 3)
		return {};

	vector <Point> other = points;
	p0 = *min_element(other.begin(), other.end());

	sort(other.begin(), other.end(), compare); //sort po polarnom uglu u odnosu na p0

	vector<Point> stek;

	for (const Point& p : other) 
	{
		while (stek.size() > 1 && orientation(stek[stek.size() - 2], stek.back(), p) >= 0) 
		{
			stek.pop_back();
		}
		stek.push_back(p);
	}

	if (stek.size() < 3) return {};

	return stek;

}
///////////////////////////////////////////////////////////////////////////

int RandomNumber(int x, int y)
{
	return rand() % (y - x + 1) + x;
}

double PointRandomNumber(int x, int y)
{
	return (double)RandomNumber(x, y) + (RandomNumber(0, 10) / 10.0f);
	
}

vector<Point> generateRandomPoints(int N, int minVr, int maxVr)
{
	vector<Point> points;
	while (points.size() < N)
	{
		Point tmp;
		tmp.x = PointRandomNumber(minVr, maxVr);
		tmp.y = PointRandomNumber(minVr, maxVr);
		cout << tmp << endl;
		points.push_back(tmp);
	}
	return points;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

bool linesIntersect(Point p1, Point q1, Point p2, Point q2) //dve duzi 1: p1->q1, 2: p2->q2
{
	int orient1 = orientation(p1, q1, p2);
	int orient2 = orientation(p1, q1, q2);
	int orient3 = orientation(p2, q2, p1);
	int orient4 = orientation(p2, q2, q1);

	if ((orient1 != orient2) && (orient3 != orient4))
		return true;

	return false;
}

bool polygonsIntersect (const vector<Point>& hull1, const vector<Point>& hull2)
{
	int n1 = hull1.size();
	int n2 = hull2.size();

	for (int i = 0; i < n1; i++)
	{
		Point a1 = hull1[i];
		Point a2 = hull1[(i + 1) % n1];
		for (int j = 0; j < n2; j++)
		{
			Point b1 = hull2[j];
			Point b2 = hull2[(j + 1) % n2];
			if (linesIntersect(a1, a2, b1, b2))
				return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

int main() 
{
	srand(time(nullptr));
	int N;

	cout << "unesite vrednost za N tako da vazi: " << endl;
	cout << "10 <= N <= 10.000.000 " << endl;
	cin >> N;

	int minVr, maxVr;
	cout << "Unesite opseg brojeva minVr i maxVr koje moze imati tacka : " << endl;
	cout << "minVr = ";
	cin >> minVr;
	cout << endl;
	cout << "maxVr = ";
	cin >> maxVr;
	cout << endl;

	vector<Point> points1 = generateRandomPoints(N, minVr, maxVr);

	vector<Point> hull1 = findConvexHull(points1);

	cout << "\nkonveksni omotac prvog skupa ima: " << hull1.size() << " tacaka\n" << endl;

	for (Point p : hull1) 
	{
		cout << p << endl;
	}

	cout << "\n\n\n";

	vector<Point> points2 = generateRandomPoints(N, minVr, maxVr);
	
	vector<Point> hull2 = findConvexHull(points2);

	cout << "\nkonveksni omotac drugog skupa ima: " << hull2.size() << " tacaka\n" << endl;

	for (Point p : hull2)
	{
		cout << p << endl;
	}

	if (polygonsIntersect(hull1, hull2))
		cout << "\nkonveksni omotaci se seku" << endl;
	else
		cout << "\nkonveksni omotaci su disjunktni" << endl;

	return 0;
}