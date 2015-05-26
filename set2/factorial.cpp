#include <cstdio>
#include <cmath>
#include <iostream>

int main() {
	int i, j;
	int n;
	scanf("%d", &n);
	int curr;
	int zeros;
	for (i = 0; i < n; i++) {
		zeros = 0;
		scanf("%d", &curr);
		for (j = 1; j <= 12; j++) {
			zeros += curr / pow(static_cast<double>(5), j);
		}
		printf("%d\n", zeros);
	}
	return 0;
}