#include <cstdio>
#include <utility>
#include <cstdlib>
#include <cmath> 
using namespace std;

#define MAX_N 100
#define MAX_COWS 10000

	//calculating area using 2 points (square the distance between two points)
	double squareArea(int x1, int y1, int x2, int y2)
	{
	    double x = x2 - x1;
	    double y = y2 - y1;
	    double area = 0;

	    area = pow(x,2)+pow(y,2);
	    return area;
	}

	int main() {

		double area = 0;
 		int n = 0;
 		int i, j;
 		scanf("%d\n", &n);
 		char field[MAX_N][MAX_N+1];

 		//FOR SAVING LOCATION OF EACH COW;
 		pair<int, int> coordinate[MAX_COWS];

 		for (i = 0; i < n; i++) {
 			scanf("%s", field[i]);
 		}
  			
	  	int cows = 0;
	  	int first = 0;

	 	//locate cows
		for (i = 0; i < n; i++) {
	 		for (j = 0; j < n; j++) {
	 			if (field[i][j] == 'J') {
	 				coordinate[cows].first = i;
	 				coordinate[cows].second = j;
	 				cows++;
	 			}
	 		}
	 	}

 		//printf("cows = %d\n", cows);

 		//max area (could be optimised by finding x range and y range but pointless since N<=100)
		double maxarea = pow((n-1), 2);	
		//printf("maxarea = %d\n", int(maxarea));

 		//pick two cows
 		for (i = 0; i < cows; i++) {
 			for (j = i + 1; j < cows; j++) {
 				//break if maximum area reached
 				if (area == maxarea) {
 					break;
 				}

	 			//making it more readable
	 			int x1 = coordinate[i].first;
	 			int y1 = coordinate[i].second;
	 			int x2 = coordinate[j].first;
	 			int y2 = coordinate[j].second;
	 		
	 			int xdelta = x2 - x1;
	 			int ydelta = y2 - y1;
	 			
	 			double currarea = squareArea(x1, y1, x2, y2);
	 			
	 			if (currarea <= area || currarea > maxarea) {
					continue;
				}
				//printf("[%f < %f]\n", currarea, area);

				//attempt to make squares

				int px1 = x1 + ydelta;
				int py1 = y1 - xdelta;
				int px2 = x2 + ydelta; 
				int py2 = y2 - xdelta;

				//printf("%d, %d\n%d, %d\n%d, %d\n%d, %d\n\n", x1, y1, x2, y2, px1, py1, px2, py2);
				
				if (		px1 >= 0 && px1 < n 
						&& 	py1 >= 0 && py1 < n
						&&	px2 >= 0 && px2 < n
						&& 	py2 >= 0 && py2 < n	) {
					if (field[px1][py1] == 'B') {
	 					//continue;
	 				} else if (field[px2][py2] == 'B') {
	 					//continue;
	 				} else if (field[px1][py1] == 'J' || field[px2][py2] == 'J') {
	 					area = currarea;
	 					continue;
	 				}
	 			}

	 			int qx1 = x1 - ydelta;
				int qy1 = y1 + xdelta;
				int qx2 = x2 - ydelta; 
				int qy2 = y2 + xdelta;

	 			if (		qx1 >= 0 && qx1 < n 
						&& 	qy1 >= 0 && qy1 < n
						&&	qx2 >= 0 && qx2 < n
						&& 	qy2 >= 0 && qy2 < n	) {
					if (field[qx1][qy1] == 'B') {
	 					continue;
	 				} else if (field[qx2][qy2] == 'B') {
	 					continue;
	 				} else if (field[qx1][qy1] == 'J' || field[qx2][qy2] == 'J') {
	 					area = currarea;
	 				}
	 			}
	 		//printf("[%d][%d]\n", i, j);
	 		}
	 	}
 	printf("%.f\n", area);
 	return 0;
} 