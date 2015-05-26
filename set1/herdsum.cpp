#include <cstdio>

#define MAXCOWS 10000000

	int main() {
 	int n;
 	int ways = 1;
 	int lowest = 1;
 	int highest = 0;
 	int sum = 0;
 	scanf("%d", &n);

 	while (lowest < n/2 + 1) {
	 	if (sum < n) {
	 		highest++;
	 		sum += highest;
	 	}
	 	else if (sum > n) {
	 		sum -= lowest;
	 		lowest++;
	 	} else {
	 		ways++;
	 		sum = sum - lowest + highest + 1;
	 		lowest++;
	 		highest++;
	 	}
 	}

 	printf("%d\n", ways);
 	return 0;
} 