#include <float.h>
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
class Point {
public:
	double x;
	double y;
	// ���캯������ʼ��Ϊ0
	Point() {
		x = y = 0;
	}
	// �������캯��
	Point(const Point &p) {
		x = p.x;
		y = p.y;
	}
};

// ��ӡ��̾��������
void Print_point(Point p1, Point p2) {
	cout << "(" << p1.x << "," << p1.y << ")" << "   (" << p2.x << "," << p2.y << ")\n";
}

// ����x������
bool Compare_x(Point &p1, Point &p2) {
	return p1.x < p2.x;
}

// ����y������
bool Compare_y(Point &p1, Point &p2) {
	return p1.y < p2.y;
}

// ������������ƽ��
double Get_distance(Point p1, Point p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) +(p1.y - p2.y)*(p1.y - p2.y);
}

// ������
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

// ���η�
double DAC_get_mindistance(Point *point, int left, int right, Point &p1, Point &p2) {
	if (right - left == 0) {				// ֻ��һ����
		return DBL_MAX;
	} else if (right - left == 1) {			//  ֻ��������
		p1 = point[left];
		p2 = point[right];
		// ֱ�ӷ����������
		return Get_distance(p1, p2);
	} else if (right - left == 2) {			//  ֻ��������
		// ����������������̾���
		return Brute_force(point, left, left + 3, p1, p2);
	} else {
		int mid;
		int i, j;
		double min_dis;
		double dl, dr;
		double true_min_dis;
		Point p3, p4;

		mid = (left + right) / 2;
		// �ݹ�õ������Ӽ�����̾���
		dl = DAC_get_mindistance(point, left, mid, p1, p2);
		dr = DAC_get_mindistance(point, mid + 1, right, p3, p4);

		// �Ƚ����ߵ���̾���
		if (dl <= dr) {
			min_dis = dl;
		} else {
			min_dis = dr;
			p1 = p3;
			p2 = p4;
		}

		// �½�һ��Point���飬���ڴ�����м�����Y�ĵ�
		Point* pp = new Point[right - left + 1];
		int len = 0;
		true_min_dis = sqrt(min_dis);
		for (i = left; i <= right; i++) {
			// �����м��ľ���С����̾��룬�����м�����Y
			if (fabs(point[i].x - point[mid].x) < true_min_dis) {
				pp[len++] = point[i];
			}
		}
		// �м�����Y�ĵ��y���������
		sort(pp, pp + len , Compare_y);
		for (i = 0; i < len; i++) {
			for (j = i + 1; j < len; j++) {
				// ֮��ĵ������С���Ѽ�¼����̾���Ļ���������ѭ��
				if ((pp[j].y - pp[i].y) >= true_min_dis) {
					break;
				}
				// ����������С���Ѽ�¼����̾���Ļ���������̾���
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

// �ϲ�����
// �����������Ӽ���Point����ϳ�Ϊ������y�������Point����
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

// ���η�1
double DAC_get_mindistance1(Point *point,int *a, int left, int right, Point &p1, Point &p2) {
	if (right - left == 0) {			// ֻ��һ����
		a[left] = left;
		return DBL_MAX;
	} else if (right - left == 1) {		// ֻ��������
		p1 = point[left];
		p2 = point[right];
		// ����y�����С����������
		// ����a��Ŷ�y�������Point�����±�
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
		// �����ݹ�ֱ�õ������Ӽ�����̾���
		dl = DAC_get_mindistance1(point, a,left, mid, p1, p2);
		dr = DAC_get_mindistance1(point, a,mid + 1, right, p3, p4);
		// �ϲ�
		Merge(point, a, left, mid, right);
		if (dl <= dr) {
			min_dis = dl;
		} else {
			min_dis = dr;
			p1 = p3;
			p2 = p4;
		}
		true_min_dis = sqrt(min_dis);
		// �½�һ��Point���飬����м�����Y�ĵ�
		Point *pp = new Point[right - left + 1];
		int len = 0;
		for (i = left; i <= right; i++) {
			// �����м�����С����̾���Ļ��������м�����Y
			if (fabs(point[a[i]].x - point[mid].x) <= true_min_dis) {
				pp[len++] = point[a[i]];
			}
		}
		for (i = 0; i < len; i++) {
			// ֻ��Ҫ������i����֮���6����
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

