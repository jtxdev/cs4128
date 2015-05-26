#include <cstdio>
#include <cmath>
#include <utility>
#include <vector>

using namespace std;

#define MAXGRID 50

const double EPS = 1e-6; 

double dist(double x1, double y1, double x2, double y2)
{
    double x = x2 - x1;
    double y = y2 - y1;

    return sqrt(pow(x,2)+pow(y,2));
}

int main() {
	double x1, y1, x2, y2, x3, y3, centrex, centrey;
	vector<pair<double, double> > coordinates;

	while (scanf("%lf %lf", &x1, &y1) != EOF) {
		pair<double, double> p = make_pair(x1, y1);
		coordinates.push_back(p);
	}
	int i, j, k;
	int count;
	int highest = 0;

	for (i = 0; i < coordinates.size(); i++) {
		//for each chocchip
		x1 = coordinates[i].first;
		y1 = coordinates[i].second;
		
		for (j = 0; j < coordinates.size(); j++) {
			//match with another chocchip that hasnt been matched previously
			x2 = coordinates[j].first;
			y2 = coordinates[j].second;
			if (dist(x1, y1, x2, y2) < 5.0 + EPS) {
			//if within bounds
				count = 0;
				centrex = (x1 + x2) / 2;
				centrey = (y1 + y2) / 2;
				for (k = 0; k < coordinates.size(); k++) {
					x3 = coordinates[k].first;
					y3 = coordinates[k].second;
					if (dist(centrex, centrey, x3, y3) < 2.5 + EPS) {
						count++;
					}
				}			
				if (count > highest) {
					highest = count;
				}
			}
		}
	}

	printf("%d\n", highest);

	return 0;
}