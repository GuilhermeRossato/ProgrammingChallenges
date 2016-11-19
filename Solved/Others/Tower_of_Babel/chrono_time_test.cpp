#include <iostream>
#include <chrono>
#include <stdio.h>
#include <tchar.h>
#include <SDKDDKVer.h>

using namespace std;

unsigned long factorial(unsigned long long a) {
	unsigned long long result = 1;
	while (a>1) {
		cout << result << endl;
		result = result*a--;
		if (result == 0)
			result = 1;
	}
	return a;
}

int main() {
	unsigned long input;
	cin >> input;
	auto start_moment = chrono::high_resolution_clock::now();
	auto result0 = factorial(input);
	auto end_moment = chrono::system_clock::now();
	unsigned long long diff = chrono::duration_cast<chrono::nanoseconds>(end_moment - start_moment).count();
	cout << "res: " << result0 << endl;
	if (diff==0 || diff%1000000==0) {
		diff = chrono::duration_cast<chrono::milliseconds>(end_moment - start_moment).count();
		cout << "Took " << diff << " ms" << endl;
	} else if (diff%1000==0) {
		diff = chrono::duration_cast<chrono::microseconds>(end_moment - start_moment).count();
		cout << "Took " << diff << " us" << endl;
	} else {
		
	}
	cout << diff << endl;
	system("pause");
	return 0;
}