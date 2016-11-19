// UNSOLVED [Time limit exceeded]
// Escaping from Escaping
// https://www.urionlinejudge.com.br/judge/en/problems/view/2093

#include <iostream>
#include <string>

using namespace std;

int main2093() {
	int tests, i, count0, count1, highestCount0, highestCount1;
	char thisChar, lastChar;
	bool valid = false;
	cin >> tests;
	for (i = 0; i < tests; i++) {
		highestCount0 = -1;
		highestCount1 = -1;
		count0 = 0;
		count1 = 0;
		lastChar = -1;
		valid = false;
		while (true) {
			thisChar = '\0';
			cin.get(thisChar);
			if (lastChar != -1) {
				if (lastChar == 48 && lastChar == thisChar) {
					count0++;
					valid = true;
				} else if (lastChar == 49 && lastChar == thisChar) {
					count1++;
					valid = true;
				} else {
					if (lastChar == 48) {
						if (highestCount0 <= count0)
							highestCount0 = count0 + 1;
						count0 = 0;
						valid = true;
					} else if (lastChar == 49) {
						if (highestCount1 <= count1)
							highestCount1 = count1 + 1;
						count1 = 0;
						valid = true;
					}
				}
				if (thisChar == 0 || thisChar == 10 || thisChar == -1) {
					break;
				}
			}
			if (thisChar == 0)
				break;
			else if (thisChar == 10 && lastChar == -1)
				lastChar = -1;
			else
				lastChar = thisChar;
		}
		if (valid) {
			if (highestCount0 == -1 || highestCount1 == -1)
				cout << '1' << endl;
			else if (highestCount0 > highestCount1)
				cout << highestCount1 + 1 << endl;
			else
				cout << highestCount0 + 1 << endl;
		}
	}
	return 0;
}