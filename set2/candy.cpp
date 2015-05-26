#include <cstdio>
#include <cmath>

#define MAX_FLAVOURS 100000

int getCount(int F, int lowest, int i, int flavour[]) {
	
	int packsize = F * i;
	int count = 0;
	int l = lowest - packsize; // l = lowest level of candy after removing one pack;

	if (l > 0 && l % i == 0) { //good
		int clear = 0;
		for (int j = 0; j < F && clear == 0; j++) {
			if ((flavour[j] - l) % packsize != 0) {
				clear = 1;
			}
		}

		if (clear == 0) {
			// count += ((levelOfCandyAfterRemovingOnePack + (levelOfCandyAfterRemovingOnePack % packsize)) / packsize);
			count += (l / packsize);
			if (l % packsize != 0) {
				count++;
			}
		}
	}
	return count;
}


int main() {

	int flavour[MAX_FLAVOURS];
	int F;
	int i, j;
	int count;
	int clear;

	while (scanf("%d", &F) == 1) {

		count = 0;
		if (F == 0) {
			return 0;
		}
		int lowest = 10e9 + 1;
		for (i = 0; i < F; i++) {
			scanf("%d", &flavour[i]);
			if (flavour[i] < lowest) {
				lowest = flavour[i];
			}
		}
		
		i = 1;
		while (i < sqrt(lowest)) {

			if (lowest % i == 0) {
				
				count += getCount(F, lowest, i, flavour);
				count += getCount(F, lowest, (lowest/i), flavour);

			}
			i++;
		}
		if (i * i == lowest) {
			count += getCount(F, lowest, i, flavour);
		}
		printf("%d\n", count);
	}
	return 0;
}