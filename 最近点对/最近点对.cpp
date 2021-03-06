#include "pch.h"
#include "function.h"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <Windows.h>
#include <algorithm>
using namespace std;

int main()
{
	int t;int n;
	cin >> t;
	cout << "请输入数据规模：";
	cin >> n;

	while (t--) {
		
		double min_distance;
		int *a;
		Point *point;
		Point p1, p2;
		Point *point1;
		
		point = new Point[n];
		point1 = new Point[n];
		a = new int[n];
		srand((unsigned)time(NULL));
		for (int i = 0; i < n; i++) {
			point1[i].x = point[i].x = (rand() * rand() * 1.00) / (RAND_MAX * RAND_MAX) * n;
			point1[i].y = point[i].y = (rand() * rand() * 1.00) / (RAND_MAX * RAND_MAX) * n;
		}
		LARGE_INTEGER freq;
		LARGE_INTEGER begintime;
		LARGE_INTEGER endtime;

		/*QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&begintime);
		min_distance = Brute_force(point, 0, n, p1, p2);
		QueryPerformanceCounter(&endtime);
		//Print_point(p1, p2);
		//cout << "最短距离为" << sqrt(min_distance) << endl;
		cout
			//<< "蛮力法总耗时为"
			<< (double)(endtime.QuadPart - begintime.QuadPart) * 1000 / freq.QuadPart
			//<< "ms"
			<< endl;*/

		/*QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&begintime);
		sort(point, point + n, Compare_x);
		min_distance = DAC_get_mindistance(point, 0, n, p1, p2);
		QueryPerformanceCounter(&endtime);
		//Print_point(p1, p2);
		//cout << "最短距离为" << sqrt(min_distance) << endl;
		cout
			//<< "分治法1总耗时为"
			<< (double)(endtime.QuadPart - begintime.QuadPart) * 1000 / freq.QuadPart
			//<< "ms"
			<< endl;*/


		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&begintime);
		sort(point1, point1 + n, Compare_x);
		min_distance = DAC_get_mindistance1(point1, a, 0, n - 1, p1, p2);
		QueryPerformanceCounter(&endtime);
		//Print_point(p1, p2);
		//cout << "最短距离为" << sqrt(min_distance) << endl;
		cout
			//<< "分治法2总耗时为"
			<< (double)(endtime.QuadPart - begintime.QuadPart) * 1000 / freq.QuadPart
			//<< "ms"
			<< endl;
	}
	
}

