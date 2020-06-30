#include <iostream>
#include <string>
using namespace std;
#include "spline_basic.h"
#include "b_spline.h"
#include "olcConsoleGameEngine.h"



class OneLoneCoder_Splines : public olcConsoleGameEngine
{
public:
	OneLoneCoder_Splines()
	{
		m_sAppName = L"Splines";
	}

private:
	bSpline path;
	bSpline k;
	int nSelectedPoint = 0;

protected:
	// Called by olcConsoleGameEngine
	virtual bool OnUserCreate()
	{
		path.points = { { 10, 41 },{ 30, 61 },{ 50, 61 },{ 70, 41 },{90, 21},{110, 21} };
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