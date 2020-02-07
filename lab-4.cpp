#include <iostream>
using namespace std;

void merge(int a[], int l, int mid, int r) {
	int i = l, j = mid + 1;
	int temp[r - l + 1];
	for (int k = 0; k < r - l + 1; k++) {
		if (i > mid) temp[k] = a[j], j++;
		else if (j > r) temp[k] = a[i], i++;
		else if (a[i] <= a[j]) temp[k] = a[i], i++;
		else temp[k] = a[j], j++;
	}
	for (int i = l; i <= r; i++) {
		a[i] = temp[i-l];
	}
}

void merge_sort(int a[], int l, int r) {
	if (l >= r) return;
	int mid = (l + r) / 2;
	merge_sort(a, l, mid);
	merge_sort(a, mid + 1, r);
	merge(a, l, mid, r);
}

void merge_sort_iterative(int a[], int l, int r) {
	int sz = 1;
	int n = r - l + 1;
	while (sz <= n - 1) {
		for (int i = 0; i < n; i += 2*sz) {
			int mid = i + sz - 1;
			if (mid > n - 1) mid = n - 1;
			int r = i + 2*sz - 1;
			if (r > n - 1) r = n - 1;
			merge(a, i, mid, r);
		}
		sz *= 2;
	}
}

int main() {
	int n;
	cout << "Enter the number of elements : ";
	cin >> n;
	int a[n];
	cout << "Enter the elements: ";
	for (int i = 0; i < n; i++)
		cin >> a[i];
	merge_sort(a, 0, n - 1);
	cout << "Sorted list of elements: ";
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}