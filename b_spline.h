#include <iostream>
#include <string>

using namespace std;

float calc_weights(float t, int m, int k);

struct sPoint2D
{
	float x;
	float y;

};


struct bSpline
{

	vector<sPoint2D> points;
	int k; //degree of b spline

	int getsize()
	{
		return points.size();
	}
	

	sPoint2D GetSplinePoint(float t, int m)
	{
		
		float tx = 0;
		float ty = 0;
		//iterate through weight for each point
		for (int a = 0; a < m - k - 1; a++)
		{
			float q = calc_weights(t, a, k);

			tx = tx + points[a].x * q;
			ty = ty + points[a].y * q;
		}
		//cout << tx << endl;
		return{ tx, ty };
	}
};

float calc_weights(float t, int a, int k)
{
	if (k == 1)
	{
		if (t >= a && t <= (a + 1))
			return 1;
		else
			return 0;
	}

	
	float numeratorA = (t - a);
	float denominatorA = ((a + k-1) - a);
	float numeratorB = ((a + k) - t);
	float denominatorB = ((a + k) - (a + 1));

	float subweightA = 0;
	float subweightB = 0;

	if (denominatorA != 0)
		subweightA = numeratorA / denominatorA * calc_weights(t, a, k-1);
	if (denominatorB != 0)
		subweightB = numeratorB / denominatorB * calc_weights(t, a+1, k-1);

	return subweightA + subweightB;
}