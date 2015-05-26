#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

#define x first
#define y second

const double PI = 3.1415926539;
const double EPS = 1e-6; 

typedef pair<double, double> pt;


double solvex(double chord, double arclen) {
	double lo = 0;
	double hi = PI * 2;
	double mid = (lo+hi)/2.0;
	while (lo < hi + EPS) {
		mid = (lo+hi)/2.0;
		if (2 * arclen * sin(mid/2.0) > chord * mid) {
			lo = mid;
		} else if (2 * arclen * sin(mid/2.0) < chord * mid) {
			hi = mid;
		} else {
			return mid;
		}
	}
	return mid;
}

int main() {
	double chord, temp, C;
	while (scanf("%lf%lf%lf", &chord, &temp, &C)) {
		if (chord < 0 && temp < 0 && C < 0) break;
		double arclen = (1+temp*C)*chord;
		// printf("%.3f\n", arclen);

		double x = solvex(chord, arclen);
		// printf("%.10f\n", x);
		if (x < EPS) {
			printf("0.000\n");	
		} else {
			double R = arclen/x;
			double r = R*cos(x/2.0);
			printf("%.3f\n", R-r);	
		}	
	}
}