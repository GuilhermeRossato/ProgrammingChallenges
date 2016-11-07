// HALF SOLVED
// Problem A. Minimum Scalar Product
// https://code.google.com/codejam/contest/dashboard?c=32016

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void ArrayReceive(vector<int> &v, int s) {
	for (int i = 0; i < s; i++) {
		cin >> v[i];
	}
}

void ArrayShow(string name, vector<int> &v, int size, int maxPerLine) {
	cout << name << " = {";
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (i != 0)
			cout << ", ";
		max++;
		if (max == maxPerLine) {
			cout << endl;
			max = 0;
		}
		cout << v[i];
	}
	cout << "}" << endl;
}

int ArrayScalarProduct(vector<int> &v1, vector<int> &v2, int size) {
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += v1[i] * v2[i];
	}
	return sum;
}

bool positiveSort(int i, int j) { return i > j; }
bool negativeSort(int i, int j) { return i < j; }

int mainG32016A() {
	int test_cases, test_count = 0;
	cin >> test_cases;
	for (int n = 0; n < test_cases;n++) {
		int v_size;
		cin >> v_size;
		if (v_size != 0) {
			test_count++;
			vector <int> v1(v_size);
			vector <int> v2(v_size);
			ArrayReceive(v1, v_size);
			ArrayReceive(v2, v_size);
			sort(v1.begin(), v1.end(), positiveSort);
			sort(v2.begin(), v2.end(), negativeSort);
			//ArrayShow("v1",v1, v_size, 8);
			//ArrayShow("v2",v2, v_size, 8);
			cout << "Case #" << test_count << ": " << ArrayScalarProduct(v1, v2, v_size) << endl;
		}
	}
	//cout << "End" << endl;
	return 0;
}