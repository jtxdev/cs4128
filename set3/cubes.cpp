#include <cstdio>

#define MAX_CUBES 30005
	
int par[MAX_CUBES]; //parent cube
int size[MAX_CUBES]; //size of stack
int pos[MAX_CUBES]; //position from parent

int find(int a) {
	while (par[a] != a) {
		a = par[a];
	}
	return a;
}

int findandcompress(int a, int x) {
	a = par[a];
	while (par[a] != a) {
		int tmp = a;
		int tmp2 = a;
		a = par[a];		
		// par[tmp] = x;
		// pos[tmp] += size[x];
		tmp2 = par[tmp2];
		while (par[tmp2] != tmp2) {
			pos[tmp] += pos[tmp2] - 1;
			tmp2 = par[tmp2];
		}
		par[tmp] = x;
		pos[tmp] += size[x];
	}
	return a;
}

void unionset(int x, int y) {


	x = find(x); 
	y = findandcompress(y, x);

	par[y] = x; 
	pos[y] += size[x];
	size[x] += size[y];

}

int count(int a) {

	int cubes = pos[a];
	a = par[a];
	while (par[a] != a) {
		cubes += pos[a] - 1;
		a = par[a];
	}
	return size[a] - cubes;

}

int main() {

	char type;
	int i, P;
	for (i = 1; i < MAX_CUBES; i++) {
		par[i] = i;
		size[i] = 1;
		pos[i] = 1;
	}

	scanf("%d\n", &P);
	int x, y, target;
	for (i = 0; i < P; i++) {
		scanf("%c", &type);
		if (type == 'M') {
			
			scanf("%d %d\n", &x, &y);
			unionset(x, y);

		} else {

			scanf("%d\n", &target);
			printf("%d\n", count(target));

			// // for(i = 0; i < 32: i++) {
			// 	printf("tar = %d\n", target);
			// 	printf("pos%d = %d\n", target, pos[target]);
			// 	printf("par%d = %d\n", target, par[target]);
			// 	printf("size%d = %d\n", par[target], size[par[target]]);
			// // }

			// for (int j = 0; j < 32; j++) {
			// 	// printf("tar = %d\n", target);
			// 	// printf("pos%d = %d\n", target, pos[target]);
			// 	// printf("par%d = %d\n", target, par[target]);
			// 	printf("size%d = %d\n", j, size[j]);
			// }

		}
	}
	return 0;
}