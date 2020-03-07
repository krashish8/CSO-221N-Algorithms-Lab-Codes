// Convex Hull using Divide and Conquer

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
};

inline bool operator<(const Point& a, const Point& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool sort_by_x(Point a, Point b) {
	return a.x < b.x;
}

Point mid; // centre of polygon

int quad(Point a) {
	if (a.x >= 0 && a.y >= 0) return 1;
	else if (a.x <= 0 && a.y >= 0) return 2;
	else if (a.x <= 0 && a.y <= 0) return 3;
	else return 4;
}

bool cmp(Point a, Point b) {
	Point p, q;
	p.x = a.x - mid.x;
	p.y = a.y - mid.y;
	q.x = b.x - mid.x;
	q.y = b.y - mid.y;
	if (quad(p) != quad(q))
		return quad(p) < quad(q);
	return (p.y*q.x < q.y*p.x);
}

class ConvexHull {
public:
	vector<Point> merge(vector<Point>&, vector<Point>&);
	vector<Point> computeConvexHull(vector<Point>&);
};

// Intercept on line x = mid, by the line joint points a and b
double intercept(double mid, Point a, Point b) {
	return a.y + (double)(b.y - b.x) * (mid - a.x) / (a.y - a.x);
}

// Return the sign of A * (A(c.x) + B(c.y) - C) (line formed by points a and b) on putting the point c
int lineeqn(Point a, Point b, Point c) {
	int value = (b.y - b.x) * c.x - (a.y - a.x) * c.y - a.x * (b.y - b.x) + a.y * (a.y - a.x);
	return (b.y - b.x) * value >= 0;
}

// left and right are clockwise
vector<Point> ConvexHull::merge(vector<Point> &left, vector<Point> &right) {
	int lsize = left.size(), rsize = right.size();
	int mxleft = 0, mnright = 0;
	for (int i = 0; i < lsize; i++) {
		if (left[mxleft].x < left[i].x)
			mxleft = i;
	}
	for (int i = 0; i < rsize; i++) {
		if (right[mnright].x > right[i].x)
			mnright = i;
	}
	double mid = (left[mxleft].x + right[mnright].x) / 2.0;

	// Lower Hull
	int i = mxleft, j = mnright;
	double y_int = intercept(mid, left[mxleft], right[mnright]);
	while (true) {
		int newi = (i + 1 + lsize) % lsize;
		double new_int = intercept(mid, left[newi], right[mnright]);
		if (new_int <= y_int) {
			i = newi;
			y_int = new_int;
		}
		else break;
	}
	while (true) {
		int newj = (j - 1 + rsize) % rsize;
		double new_int = intercept(mid, left[i], right[newj]);
		if (new_int <= y_int) {
			j = newj;
			y_int = new_int;
		}
		else break;
	}

	// Upper Hull
	int ii = mxleft, jj = mnright;
	y_int = intercept(mid, left[mxleft], right[mnright]);
	while (true) {
		int newi = (ii - 1 + lsize) % lsize;
		double new_int = intercept(mid, left[newi], right[mnright]);
		if (new_int >= y_int) {
			ii = newi;
			y_int = new_int;
		}
		else break;
	}
	while (true) {
		int newj = (jj + 1 + rsize) % rsize;
		double new_int = intercept(mid, left[ii], right[newj]);
		if (new_int >= y_int) {
			jj = newj;
			y_int = new_int;
		}
		else break;
	}

	vector<Point> ans;
	ans.push_back(left[ii]);
	ans.push_back(right[jj]);
	int num = (j - jj + rsize) % rsize; // jj to j
	while (num--) {
		jj++;
		jj = (jj + rsize) % rsize;
		ans.push_back(right[jj]);
	}
	ans.push_back(left[i]);
	num = (ii - i + lsize) % lsize; // i to ii
	while (num--) {
		i++;
		i = (i + lsize) % lsize;
		ans.push_back(left[i]);
	}
	return ans;
}

vector<Point> ConvexHull::computeConvexHull(vector<Point> &v) {
	int n = v.size();
	set<Point> s;
	if (n <= 5) {
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				int flag = 0;
				for (int k = 0; k < n; k++) {
					int sign = 0;
					if (k == i || k == j) continue;
					if (sign == 0) sign = lineeqn(v[i], v[j], v[k]);
					else {
						if (sign != lineeqn(v[i], v[j], v[k]))
						{
							flag = 1; break;
						}
					}
				}
				if (flag == 0) {
					s.insert(v[i]);
					s.insert(v[j]);
				}
			}
		}
		vector<Point> ans;
		for (auto i : s)
			ans.push_back(i);
		mid.x = 0, mid.y = 0;
		for (int i = 0; i < n; i++) {
			mid.x += ans[i].x;
			mid.y += ans[i].y;
			ans[i].x *= n;
			ans[i].y *= n;
		}
		sort(ans.begin(), ans.end(), cmp);
		for (int i = 0; i < n; i++) {
			ans[i].x = ans[i].x/n;
			ans[i].y = ans[i].y/n;
		}
		return ans;
	}
	vector<Point> left, right;
	for (int i = 0; i < n; i++) {
		if (i < n / 2) left.push_back(v[i]);
		else right.push_back(v[i]);
	}
	vector<Point> left_hull = computeConvexHull(left);
	vector<Point> right_hull = computeConvexHull(right);
	return merge(left_hull, right_hull);
}

int main() {
	int n;
	cout << "Enter the number of points: ";
	cin >> n;
	cout << "Enter the points: " << endl;
	vector<Point> v;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		Point p;
		p.x = a, p.y = b;
		v.push_back(p);
	}
	sort(v.begin(), v.end(), sort_by_x);
	ConvexHull h;
	vector<Point> ans = h.computeConvexHull(v);
	cout << "The convex hull is: " << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].x << " " << ans[i].y << endl;
}

