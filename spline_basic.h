#include <iostream>
#include <string>

using namespace std;

struct sPoint2D
{
	float x;
	float y;
};

struct sSpline
{
	vector<sPoint2D> points;

	virtual sPoint2D GetSplinePoint(float t)
	{
		int p0, p1, p2, p3;

		p0 = 0;
		p1 = 1;
		p2 = 2;
		p3 = 3;

		//hey
		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;


		float q1 = (1 - t) * (1 - t) * (1 - t);
		float q2 = (1 - t) * (1 - t);
		float q3 = (1 - t);
		float q4 = 1;

		float tx = (points[p0].x * q1 + 3 * t * points[p1].x * q2 + 3 * tt * points[p2].x * q3 + ttt * points[p3].x * q4);
		float ty = (points[p0].y * q1 + 3 * t * points[p1].y * q2 + 3 * tt * points[p2].y * q3 + ttt * points[p3].y * q4);

		return{ tx, ty };
	}

};
