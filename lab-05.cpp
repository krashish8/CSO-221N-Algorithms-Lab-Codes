// Binary Multiplication using Divide and Conquer (Karatsuba Algorithm)

#include <iostream>
#include <string>

using namespace std;

void swap(string &a, string &b) {
	string temp = a;
	a = b;
	b = temp;
}

class Karatsuba {
public:
	string add(string, string);
	long int multiply(string, string);
};

string Karatsuba::add(string a, string b) {
	if (a.length() > b.length())
		swap(a, b);
	int blen = b.length(), alen = a.length();
	for (int i = 0; i < blen-alen; i++)
		a = '0' + a;
	string sum;
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		sum = (char)(s % 2 + '0') + sum;
		carry = s / 2;
	}
	if (carry == 1)
		sum = '1' + sum;
	return sum;
}

long int Karatsuba::multiply(string a, string b) {
	if (a.length() > b.length())
		swap(a, b);
	int blen = b.length(), alen = a.length();
	for (int i = 0; i < blen - alen; i++) {
		a = '0' + a;
	}
	int n = a.length();
	if (n == 1) {
		return (a[0] - '0') * (b[0] - '0');
	}
	int left = n / 2, right = n - left;
	string aleft = a.substr(0, left), aright = a.substr(left);
	string bleft = b.substr(0, left), bright = b.substr(left);
	long int albl = multiply(aleft, bleft);
	long int arbr = multiply(aright, bright);
	long int alarblbr = multiply(add(aleft, aright), add(bleft, bright));

	return (1ll << (2*right)) * albl + (1ll << right) * (alarblbr - albl - arbr) + arbr;
}

int main() {
	cout << "Enter two binary strings: " << endl;
	string a, b;
	cin >> a >> b;
	Karatsuba k;
	long int m = k.multiply(a, b);
	cout << "Product: " << m << endl;
}