// SOLVED
// LED
// https://www.urionlinejudge.com.br/judge/en/problems/view/1168

//				0	1	2	3	4	5	6	7	8	9
int lookup[] = {6,	2,	5,	5,	4,	5,	6,	3,	7,	6};

#include <iostream>
#include <string>

using namespace std;

int main1168() {
	int count, sum, i, j;
	string str;
	cin >> count;

	int * solutions = new int[count];
	for (i = 0; i < count; i++) {
		cin >> str;
		sum = 0;
		for (j = str.length() - 1; j >= 0; j--) {
			sum += lookup[str[j] - 48];
		}
		solutions[i] = sum;
	}
	for (i = 0; i < count; i++) {
		cout << solutions[i] << " leds" << endl;
	}
	return 0;
}