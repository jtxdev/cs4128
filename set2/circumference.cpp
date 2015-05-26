#include <cmath>
#include <iostream>
#include <cstdio>

#define PI 3.141592653589793

using namespace std;
	// Input

	//calculating area using 2 points (square)
	double dist(double x1, double y1, double x2, double y2)
	{
	    double x = x2 - x1;
	    double y = y2 - y1;

	    return sqrt(pow(x,2)+pow(y,2));
	}

	int main() {

	int cases = 0;
	double x1, x2, x3, y1, y2, y3;
	double d1, d2, d3;
	double diameter;
	double circumference;

	while (scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3) != EOF) {
		d1 = dist(x2, y2, x1, y1);
		d2 = dist(x3, y3, x1, y1);
		d3 = dist(x3, y3, x2, y2);
		// printf("d1 = %f\n", d1);
		// printf("d2 = %f\n", d2);
		// printf("d3 = %f\n", d3);

		diameter = (2 * d1 * d2 * d3) / sqrt((d1 + d2 + d3)*(- d1 + d2 + d3)*(d1 - d2 + d3)*(d1 + d2 - d3));
		// printf("D = %f\n", diameter);
		circumference = PI * diameter;
		printf("%.2f\n", circumference);
	}

 	return 0;
} 