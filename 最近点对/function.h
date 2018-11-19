#include <float.h>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
class Point {
public:
	double x;
	double y;
	// 构造函数，初始化为0
	Point() {
		x = y = 0;
	}
	// 拷贝构造函数
	Point(const Point &p) {
		x = p.x;
		y = p.y;
	}
};

// 打印最短距离的两点
void Print_point(Point p1, Point p2) {
	cout << "(" << p1.x << "," << p1.y << ")" << "   (" << p2.x << "," << p2.y << ")\n";
}

// 按照x轴排序
bool Compare_x(Point &p1, Point &p2) {
	return p1.x < p2.x;
}

// 按照y轴排序
bool Compare_y(Point &p1, Point &p2) {
	return p1.y < p2.y;
}

// 返回两点距离的平方
double Get_distance(Point p1, Point p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) +(p1.y - p2.y)*(p1.y - p2.y);
}

// 蛮力法
double Brute_force(Point *point, int start, int end, Point &p1, Point &p2) {
	double min_dis = DBL_MAX;
	for (int i = start; i < end - 1; i++) {
		for (int j = i + 1; j < end; j++) {
			double temp = Get_distance(point[i],point[j]);
			if (temp < min_dis) {
				min_dis = temp;
				p1 = point[i];
				p2 = point[j];
			}
		}
	}
	return min_dis;
}

// 分治法
double DAC_get_mindistance(Point *point, int left, int right, Point &p1, Point &p2) {
	if (right - left == 0) {				// 只有一个点
		return DBL_MAX;
	} else if (right - left == 1) {			//  只有两个点
		p1 = point[left];
		p2 = point[right];
		// 直接返回两点距离
		return Get_distance(p1, p2);
	} else if (right - left == 2) {			//  只有三个点
		// 调用蛮力法来求最短距离
		return Brute_force(point, left, left + 3, p1, p2);
	} else {
		int mid;
		int i, j;
		double min_dis;
		double dl, dr;
		double true_min_dis;
		Point p3, p4;

		mid = (left + right) / 2;
		// 递归得到左右子集的最短距离
		dl = DAC_get_mindistance(point, left, mid, p1, p2);
		dr = DAC_get_mindistance(point, mid + 1, right, p3, p4);

		// 比较两边的最短距离
		if (dl <= dr) {
			min_dis = dl;
		} else {
			min_dis = dr;
			p1 = p3;
			p2 = p4;
		}

		// 新建一个Point数组，用于存放在中间区域Y的点
		Point* pp = new Point[right - left + 1];
		int len = 0;
		true_min_dis = sqrt(min_dis);
		for (i = left; i <= right; i++) {
			// 点与中间点的距离小于最短距离，处于中间区域Y
			if (fabs(point[i].x - point[mid].x) < true_min_dis) {
				pp[len++] = point[i];
			}
		}
		// 中间区域Y的点对y轴进行排序
		sort(pp, pp + len , Compare_y);
		for (i = 0; i < len; i++) {
			for (j = i + 1; j < len; j++) {
				// 之后的点如果不小于已记录的最短距离的话，跳出内循环
				if ((pp[j].y - pp[i].y) >= true_min_dis) {
					break;
				}
				// 两点距离如果小于已记录的最短距离的话，更新最短距离
				if (Get_distance(pp[i], pp[j]) <= min_dis) {
					min_dis = Get_distance(pp[i], pp[j]);
					p1 = pp[i];
					p2 = pp[j];
				}
			}
		}
		delete []pp;
		return min_dis;
	}
}

// 合并过程
// 将左右两个子集的Point数组合成为整个对y轴有序的Point数组
void Merge(Point* point, int *a, int p, int q, int r) {
	int len = r - p + 1;
	int *temp = new int[len];
	int i, j, k;
	for (i = p, j = q + 1, k = 0; i <= q && j <= r; ) {
		if( point[a[i]].y <= point[a[j]].y) {
			temp[k++] = a[i++];
		} else{
			temp[k++] = a[j++];
		}
	}
	for (; i <= q; i++) {
		temp[k++] = a[i];
	}
	for (; j <= r; j++) {
		temp[k++] = a[j];
	}
	
	for (i = p, k = 0; k < len; i++, k++) {
		a[i] = temp[k];
	}
	
	delete[]temp;
}

// 分治法1
double DAC_get_mindistance1(Point *point,int *a, int left, int right, Point &p1, Point &p2) {
	if (right - left == 0) {			// 只有一个点
		a[left] = left;
		return DBL_MAX;
	} else if (right - left == 1) {		// 只有两个点
		p1 = point[left];
		p2 = point[right];
		// 根据y坐标大小来进行排序
		// 数组a存放对y轴排序的Point数组下标
		if (point[left].y <= point[right].y) {		
			a[left] = left;
			a[right] = right;
		} else {
			a[left] = right;
			a[right] = left;
		}
		return Get_distance(p1, p2);
	}  else {
		int mid;
		int i, j;
		double min_dis;
		double dl, dr;
		double true_min_dis;
		Point p3, p4;

		mid = (left + right) / 2;
		// 两个递归分别得到左右子集的最短距离
		dl = DAC_get_mindistance1(point, a,left, mid, p1, p2);
		dr = DAC_get_mindistance1(point, a,mid + 1, right, p3, p4);
		// 合并
		Merge(point, a, left, mid, right);
		if (dl <= dr) {
			min_dis = dl;
		} else {
			min_dis = dr;
			p1 = p3;
			p2 = p4;
		}
		true_min_dis = sqrt(min_dis);
		// 新建一个Point数组，存放中间区域Y的点
		Point *pp = new Point[right - left + 1];
		int len = 0;
		for (i = left; i <= right; i++) {
			// 点与中间点距离小于最短距离的话，处于中间区域Y
			if (fabs(point[a[i]].x - point[mid].x) <= true_min_dis) {
				pp[len++] = point[a[i]];
			}
		}
		for (i = 0; i < len; i++) {
			// 只需要遍历第i个点之后的6个点
			for (j = 1; j <= 6 && i + j < len; j++) {
				if (Get_distance(pp[i], pp[i + j])<= min_dis) {
					min_dis = Get_distance(pp[i], pp[i + j]);
					p1 = pp[i];
					p2 = pp[i + j];
				}
			}
		}
		return min_dis;
	}
}

