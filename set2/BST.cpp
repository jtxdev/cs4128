#include <cstdio>
#include <cmath>

int main() {
	int n;
	int x;
	int j;
	int diff;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		j = 0;
		while (x % static_cast<int>(pow(static_cast<double>(2), j+1)) != pow(static_cast<double>(2), j)) {
			j++;
		}
		diff = pow(static_cast<double>(2), j) - 1;
		printf("%d %d\n", x - diff, x + diff);
	}

	return 0;
}