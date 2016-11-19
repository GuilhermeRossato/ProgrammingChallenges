// UNSOLVED
// ICPC Finals
// https://www.urionlinejudge.com.br/judge/en/problems/view/1455

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

double getFurthest(double * pos, int posSize, double centerX, double centerY, int except, double &x1, double &y1, double &x2, double &y2) {
	int i;
	double highDist = 0, dist;
	for (i = except; i < posSize; i++) {
		dist = pow(centerX - pos[i * 3], 2) + pow(centerY - pos[i * 3 + 1], 2);
		if (i == except || (dist > highDist)) {
			highDist = dist;
			x1 = pos[i * 3];
			y1 = pos[i * 3 + 1];
			x2 = centerX;
			y2 = centerY;
		}
	}
	return highDist;
}

int main1455() {
	int number_cities, i, instanciaCount = 0, highId;
	double thisX, thisY,  highDist, c1X, c1Y, c2X, c2Y, r1X, r1Y, r2X, r2Y;
	while (instanciaCount == 0) {
		number_cities = 0;
		cin >> number_cities;
		if (number_cities == 0) {
			break;
		} else {
			double* pos = new double[(number_cities) * 3];

			for (i = 0; i < number_cities; i++) {
				cin >> thisX >> thisY;
				pos[i * 3] = thisX;
				pos[i * 3 + 1] = thisY;
			}

			highDist = 0;
			highId = 0;

			for (i = 0; i < number_cities; i++) {
				//cout << "Checking (" << pos[i * 3] << ", " << pos[i * 3+1] << ")" << endl;
				pos[i * 3 + 2] = getFurthest(pos, number_cities, pos[i * 3], pos[i * 3 + 1], i, c1X, c1Y, c2X, c2Y);
				if (i == 0 || pos[i * 3 + 2] > highDist) {
					highDist = pos[i * 3 + 2];
					r1X = c1X;
					r2X = c2X;
					r1Y = c1Y;
					r2Y = c2Y;
				}
			}

			r1X = ((r1X + r2X) / 2.0);
			r1Y = ((r1X + r2X) / 2.0);
			highDist = getFurthest(pos, number_cities, r1X, r1Y, i, c1X, c1Y, c2X, c2Y);

			highDist = sqrt(highDist)/2;

			//cout << "Furtherst appart: " << r1X << ", " << r1Y << " and " << r2X << ", " << r2Y << endl;
			//cout << "Array" << endl;
			//for (i = 0; i < number_cities; i++) {
			//	cout << "(" << pos[i * 3] << ", " << pos[i * 3 + 1] << ") -> " << pos[i * 3 + 2] << endl;
			//}
			//cout << "High: id " << highId << ", at " << highDist << endl;
			instanciaCount++;
			cout << "Instancia " << instanciaCount << endl;
			cout << fixed << setprecision(2) << ((r1X+r2X)/2.0) << " " << ((r1Y + r2Y) / 2.0) << " " << highDist << endl;
			delete[] pos;
		}
	}
	cin >> instanciaCount;
	return 0;
}