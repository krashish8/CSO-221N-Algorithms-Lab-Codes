// Implementation of Bubble Sort, Selection Sort, Insertion Sort, Shell Sort and Radix Sort
#include <iostream>
using namespace std;

void swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void selectionSort(int a[], int n) {
	for (int i = 0; i < n; i++) {
		int mn = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[mn])
				mn = j;
		}
		swap(a[i], a[mn]);
	}
}

void bubbleSort(int a[], int n) {
	for (int i = 0; i < n - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < n - i - 1; j++) {
			if (a[j] > a[j+1]) {
				swap(a[j], a[j+1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

void insertionSort(int a[], int n) {
	for (int i = 1; i < n; i++) {
		int temp = a[i];
		int j = i - 1;
		while (j >= 0 && temp < a[j]) {
			a[j+1] = a[j];
			j--;
		}
		a[j] = temp;
	}
}

void shellSort(int a[], int n) {
	for (int gap = n / 2; gap >= 0; gap /= 2) {
		for (int i = 0; i + gap < n; i++) {
			if (a[i] > a[i+gap])
				swap(a[i], a[i+gap]);
		}
	}
}

void radixSort(int a[], int n) {
	int mx = a[0];
	for (int i = 0; i < n; i++)
		mx = max(mx, a[i]);
	for (int exp = 1; mx / exp > 0; exp *= 10) {
		int output[10] = {0}, count[10] = {0};
		for (int i = 0; i < n; i++)
			count[a[i] / exp % 10]++;
		for (int i = 1; i < 10; i++)
			count[i] += count[i-1];
		for (int i = n - 1; i >= 0; i--) {
			output[count[a[i] / exp % 10] - 1] = a[i];
			count[a[i] / exp % 10]--;
		}
		for (int i = 0; i < n; i++)
			a[i] = output[i];
	}
}

int main() {
	cout << "Enter the number of elements : ";
	int n;
	cin >> n;
	cout << "Enter the elements : ";
	int a[n];
	for (int i = 0; i < n; i++)
		cin >> a[i];
	radixSort(a, n);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}