
#include <conio.h>

unsigned long factorial(unsigned long long a) {
	unsigned long long result = 1;
	while (a>1) {
		//cout << result << endl;
		result = result*a--;
		if (result == 0)
			result = 1;
	}
	return a;
}

int main() {
	unsigned long input = 10;
	unsigned nibble = 1;
	_cputs("hi nigga\n");
	_cputs("now what");
	//_cputc_native('a',0);
	//fputs('a');
	auto result0 = factorial(input);
	char a = getch();
	return 0;
}