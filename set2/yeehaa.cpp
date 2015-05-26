#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
	// Input
	int main() {

	int cases = 0;
	double R;
 	double n;
 	double r;
 	double PI = 4 * atan(1);

 	//printf("LOL?:\n");
	scanf("%d", &cases);
 	//printf("TY\n");
 	for (int i = 0; i < cases; i++) {
	 	scanf("%lf %lf", &R, &n);
	 	//cout << M_PI / n;
	 	r = R * sin(PI / n) / (1 + sin(PI / n));
	 	printf("Scenario #%d:\n", i+1);
	 	printf("%.3f\n\n", r);
 	}
 	return 0;
} 