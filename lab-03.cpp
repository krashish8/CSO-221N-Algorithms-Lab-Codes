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
		a[j+1] = temp;
	}
}

void shellSort(int a[], int n) {
	int gap = n / 2;
	while (gap > 0) {
		for (int i = gap; i < n; i++) {
			int temp = a[i];
			int j = i;
			while (j >= gap && a[j-gap] > temp) {
				a[j] = a[j-gap];
				j -= gap;
			}
			a[j] = temp;
		}
		gap /= 2;
	}
}

void radixSort(int a[], int n) {
	int mx = a[0];
	for (int i = 0; i < n; i++)
		mx = max(mx, a[i]);
	int exp = 1;
	while (mx / exp > 0) {
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
		exp *= 10;
	}
}

int a[105];

int main() {
	cout << "1. Selection Sort" << endl;
	cout << "2. Bubble Sort" << endl;
	cout << "3. Insertion Sort" << endl;
	cout << "4. Shell Sort" << endl;
	cout << "5. Radix Sort" << endl;
	cout << "6. Exit" << endl;
	cout << "Enter your choice : ";
	int op, n;
	cin >> op;
	while (op != 6) {
		cout << "Enter the number of elements : ";
		cin >> n;
		cout << "Enter the elements : ";
		for (int i = 0; i < n; i++)
			cin >> a[i];
		switch(op) {
			case 1: selectionSort(a, n); break;
			case 2: bubbleSort(a, n); break;
			case 3: insertionSort(a, n); break;
			case 4: shellSort(a, n); break;
			case 5: radixSort(a, n); break;
			case 6: break;
		}
		cout << "Sorted Elements : ";
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << "\n\nEnter your choice : ";
        cin >> op;
	}
}