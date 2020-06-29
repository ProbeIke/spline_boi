#include <iostream>
#include <string>
using namespace std;
#include "olcConsoleGameEngine.h"

struct sPoint2D
{
	float x;
	float y;
};

struct sSpline
{
	vector<sPoint2D> points;

	sPoint2D GetSplinePoint(float t)
	{
		int p0, p1, p2, p3;

		p0 = 0;
		p1 = 1;
		p2 = 2;
		p3 = 3;


		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;


		float q1 = (1-t)*(1-t)*(1-t);
		float q2 = (1 - t) * (1-t);
		float q3 = (1-t);
		float q4 = 1;
		
		float tx = (points[p0].x * q1 + 3*t*points[p1].x * q2 + 3*tt*points[p2].x * q3 + ttt*points[p3].x * q4);
		float ty = (points[p0].y * q1 + 3*t*points[p1].y * q2 + 3*tt*points[p2].y * q3 + ttt*points[p3].y * q4);

		return{ tx, ty };
	}

};

struct b_spline
{
	vector<sSpline> splines;
};

class OneLoneCoder_Splines : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Splines()
	{
		m_sAppName = L"Splines";
	}

private:
	sSpline path;
	int nSelectedPoint = 0;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		path.points = { { 10, 41 },{ 30, 61 },{ 50, 61 },{ 70, 41 } };
		return true;
	}

	// Called by olcConsoleGameEngine
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		// Clear Screen
		Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

		// Handle input
		if (m_keys[L'X'].bReleased)
		{
			nSelectedPoint++;
			if (nSelectedPoint >= path.points.size())
				nSelectedPoint = 0;
		}

		if (m_keys[L'Z'].bReleased)
		{
			nSelectedPoint--;
			if (nSelectedPoint < 0)
				nSelectedPoint = path.points.size() - 1;
		}

		if (m_keys[VK_LEFT].bHeld)
			path.points[nSelectedPoint].x -= 30.0f * fElapsedTime;

		if (m_keys[VK_RIGHT].bHeld)
			path.points[nSelectedPoint].x += 30.0f * fElapsedTime;

		if (m_keys[VK_UP].bHeld)
			path.points[nSelectedPoint].y -= 30.0f * fElapsedTime;

		if (m_keys[VK_DOWN].bHeld)
			path.points[nSelectedPoint].y += 30.0f * fElapsedTime;


		// Draw Spline
		//for (float t = 0; t < (float)path.points.size(); t += 0.005f)
		for (float t = 0; t < 1; t += 0.005f)
		{
			sPoint2D pos = path.GetSplinePoint(t);
			Draw(pos.x, pos.y);
		}

		// Draw Control Points
		for (int i = 0; i < path.points.size(); i++)
		{
			Fill(path.points[i].x - 1, path.points[i].y - 1, path.points[i].x + 2, path.points[i].y + 2, PIXEL_SOLID, FG_RED);
			DrawString(path.points[i].x, path.points[i].y, to_wstring(i));
		}

		// Highlight control point
		Fill(path.points[nSelectedPoint].x - 1, path.points[nSelectedPoint].y - 1, path.points[nSelectedPoint].x + 2, path.points[nSelectedPoint].y + 2, PIXEL_SOLID, FG_YELLOW);
		DrawString(path.points[nSelectedPoint].x, path.points[nSelectedPoint].y, to_wstring(nSelectedPoint));

		return true;
	}
};

int main()
{
	OneLoneCoder_Splines demo;
	demo.ConstructConsole(160, 80, 10, 10);
	demo.Start();
	return 0;
}