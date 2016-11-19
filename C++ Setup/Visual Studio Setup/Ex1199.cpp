// SOLVED
// Simple Base Conversion
// https://www.urionlinejudge.com.br/judge/en/problems/view/1199

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main1199() {
	string inputText;
	int search, sum, mult, base;

	cin >> inputText;

	while ((!inputText.empty()) && inputText[0] != 45) {
		search = inputText.length() - 1;
		sum = 0;
		mult = 1;
		if (inputText[1] == 'x' || inputText[1] == 'X') {
			while (search >= 2) {
				sum += mult * (inputText[search] - ((inputText[search] >= 65) ? ((inputText[search] >= 97) ? 87 : 55) : 48));
				mult = mult * 16;
				search--;
			}
			cout << sum << endl;
		}
		else {
			while (search >= 0) {
				sum += mult * (inputText[search] - 48);
				mult = mult * 10;
				search--;
			}
			search = 0;
			mult = 0;
			inputText.clear();
			if (sum == 0) {
				cout << "0x0" << endl;
			}
			else {
				while (sum > 0) {
					mult = 0;
					while (sum >= 16) {
						sum -= 16;
						mult++;
					}
					inputText.insert(0, 1, (sum < 10) ? 48 + sum : (55 + sum));
					sum = mult;
				}
				inputText.insert(0, 1, 120);
				inputText.insert(0, 1, 48);
				cout << inputText << endl;
			}
		}
		cin >> inputText;
	}
	return 0;
}