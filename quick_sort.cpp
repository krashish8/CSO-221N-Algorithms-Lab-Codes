#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

int partition(int a[], int l, int r) {
	int pivot = r;
	int cur = l;
	for (int i = l; i < r; i++) {
		if (a[i] < a[pivot]) {
			swap(a[i], a[cur]);
			cur++;
		}
	}
	swap(a[pivot], a[cur]);
	return cur;
}

void quick_sort(int a[], int l, int r) {
	while (l < r) {
		int p = partition(a, l, r);
		quick_sort(a, l, p-1);
		quick_sort(a, p+1, r);
	}
}

int main() {
	int n;
	cin >> n;
	int a[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	quick_sort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}