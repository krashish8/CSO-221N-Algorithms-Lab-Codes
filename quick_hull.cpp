#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct Point {
	int x, y;
};

inline bool operator<(const Point& a, const Point& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

class ConvexHull {
private:
	set<Point> ch;
public:
	void computeHull(vector<Point>&, Point, Point, int);
	void print();
};

// Distance between point x and line formed by a and b
int dist(Point p1, Point p2, Point p) {
	return abs((p.y-p1.y)*(p2.x-p1.x) - (p2.y-p1.y)*(p.x-p1.x));
}

int side(Point p1, Point p2, Point p) {
	int v = (p.y - p1.y)*(p2.x - p1.x) - (p2.y - p1.y)*(p.x - p1.x);
	if (v > 0) return 1;
	else if (v < 0) return -1;
	else return 0;
}

void ConvexHull::computeHull(vector<Point> &a, Point p1, Point p2, int s) {
	int n = a.size();
	int idx = -1, mx = 0;
	for (int i = 0; i < n; i++) {
		int dis = dist(p1, p2, a[i]);
		if (mx < dis && side(p1, p2, a[i]) == s) {
			idx = i;
			mx = dis;
		}
	}

	if (idx == -1) {
		ch.insert(p1);
		ch.insert(p2);
		return;
	}
	computeHull(a, a[idx], p1, -side(a[idx], p1, p2));
	computeHull(a, a[idx], p2, -side(a[idx], p2, p1));
}

void ConvexHull::print() {
	for (auto i : ch) {
		cout << i.x << " " << i.y << endl;
	}
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
	int mn = 0, mx = 0;
	for (int i = 0; i < n; i++) {
		if (v[i].x <= v[mn].x)
			mn = i;
		if (v[i].x >= v[mx].x)
			mx = i;
	}
	ConvexHull h;
	h.computeHull(v, v[mn], v[mx], 1);
	h.computeHull(v, v[mn], v[mx], -1);
	cout << "The convex hull is: " << endl;
	h.print();
}