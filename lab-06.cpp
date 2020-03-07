// Convex Hull using Divide and Conquer

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Point {
public:
	int x, y;
	int find_quadrant();
}midn;

int Point::find_quadrant() {
	if (x >= 0) return ((y >= 0) ? 1 : 4);
	else return ((y >= 0) ? 2 : 3);
}

inline bool operator<(const Point& a, const Point& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool sort_by_x(Point a, Point b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool sort_anticlockwise(Point p1, Point p2) {
	Point a, b;
	a.x = p1.x - midn.x, a.y = p1.y - midn.y;
	b.x = p2.x - midn.x, b.y = p2.y - midn.y;
	int q1 = a.find_quadrant(), q2 = b.find_quadrant();
	if (q1 == q2) return  b.x*a.y < b.y*a.x;
	else return q1 < q2;
}

class ConvexHull {
public:
	int linecross(Point, Point, Point);
	vector<Point> combine(vector<Point>, vector<Point>);
	vector<Point> find_hull(vector<Point>);
};

int ConvexHull::linecross(Point p1, Point p2, Point p) {
	int eqn = (p2.y-p1.y)*(p.x-p2.x) - (p2.x-p1.x)*(p.y-p2.y);
	if (eqn == 0) return 0;
	else if (eqn > 0) return 1;
	else return -1;
}

vector<Point> ConvexHull::combine(vector<Point> a, vector<Point> b) {
	int n = a.size(), m = b.size();

	int mxleft = 0, mnright = 0;
	for (int i = 0; i < n; i++) {
		if (a[mxleft].x < a[i].x)
			mxleft = i;
	}
	for (int i = 0; i < m; i++) {
		if (b[mnright].x > b[i].x)
			mnright = i;
	}

	int upperleft, upperright;
	int lowerleft, lowerright;

	int pleft = mxleft, pright = mnright;
	int flag = 0;
	while (!flag) {
		flag = 1;
		while (linecross(b[pright], a[pleft], a[(pleft + 1) % n]) >= 0) {
			pleft = (pleft + 1) % n;
		}
		while (linecross(a[pleft], b[pright], b[(pright - 1 + m) % m]) <= 0) {
			pright = (pright - 1 + m) % m;
			flag = 0;
		}
	}
	upperleft = pleft, upperright = pright;

	pleft = mxleft, pright = mnright;
	flag = 0;
	while (!flag) {
		flag = 1;
		while (linecross(a[pleft], b[pright], b[(pright + 1) % m]) >= 0) {
			pright = (pright + 1) % m;
		}
		while (linecross(b[pright], a[pleft], a[(pleft - 1 + n) % n]) <= 0) {
			pleft = (pleft - 1 + n) % n;
			flag = 0;
		}
	}
	lowerleft = pleft, lowerright = pright;

	vector<Point> ans;
	int i = upperleft;
	ans.push_back(a[i]);
	while (i != lowerleft) {
		i = (i + 1) % n;
		ans.push_back(a[i]);
	}
	i = lowerright;
	ans.push_back(b[i]);
	while (i != upperright) {
		i = (i + 1) % m;
		ans.push_back(b[i]);
	}
	return ans;
}

vector<Point> ConvexHull::find_hull(vector<Point> a) {
	int n = a.size();
	if (n <= 5) {
		set<Point> s;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				int A = a[i].y - a[j].y;
				int B = a[j].x - a[i].x;
				int C = a[i].x*a[j].y - a[j].x*a[i].y;
				int count_n = 0, count_p = 0;
				for (int k = 0; k < n; k++) {
					if (A*a[k].x + B*a[k].y + C <= 0) count_n++;
					if (A*a[k].x + B*a[k].y + C >= 0) count_p++;
				}
				if (count_n == n || count_p == n)
				{
					s.insert(a[i]);
					s.insert(a[j]);
				}
			}
		}
		vector<Point> ans;
		for (auto i : s)
			ans.push_back(i);

		midn.x = 0, midn.y = 0;
		for (int i = 0; i < n; i++) {
			midn.x += ans[i].x;
			midn.y += ans[i].y;
			ans[i].x *= n;
			ans[i].y *= n;
		}
		sort(ans.begin(), ans.end(), sort_anticlockwise);
		for (int i = 0; i < n; i++) {
			ans[i].x = ans[i].x/n;
			ans[i].y = ans[i].y/n;
		}
		return ans;
	}
	vector<Point> left_points, right_points;
	for (int i = 0; i < n; i++) {
		if (i < n/2) left_points.push_back(a[i]);
		else right_points.push_back(a[i]);
	}
	vector<Point> left_hull, right_hull;
	left_hull = find_hull(left_points);
	right_hull = find_hull(right_points);
	return combine(left_hull, right_hull);
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
	vector<Point> ans = h.find_hull(v);
	cout << "The convex hull is: " << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].x << " " << ans[i].y << endl;
}
