// UNSOLVED
// Counting Crow
// https://www.urionlinejudge.com.br/judge/en/problems/view/1848
#include <iostream>

using namespace std;

int main1848() {
	int sum = 0, count = 0;
	char str[10];
	bool lastCow = false;
	int r1 = 0, r2 = 1, r3 = 0;
	while (count < 3) {
		cin.getline(str, 9);
		if (str[0] == 99) {
			if (count == 0)
				r1 = sum;
			else if (count == 1)
				r2 = sum;
			else
				r3 = sum;
			count++;
			sum = 0;
		}
		else if (str[0] > 40) {
			if (str[0] == 42) {
				sum += 4;
			}
			if (str[1] == 42) {
				sum += 2;
			}
			if (str[2] == 42) {
				sum += 1;
			}
		}
	}
	cout << r1 << endl << r2 << endl << r3 << endl;
	return 0;
}