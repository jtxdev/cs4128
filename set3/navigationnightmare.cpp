#include <cstdio>
#include <vector>

#define MAX_FARMS 40001
#define MAX_QUERY 10001
using namespace std;

typedef pair<int, int> P;

vector<P> q[MAX_FARMS];

int a[MAX_FARMS];
int b[MAX_FARMS];
int c[MAX_FARMS];
char d[MAX_FARMS];

int x[MAX_FARMS];
int y[MAX_FARMS];
int par[MAX_FARMS];

int dx = 0;
int dy = 0;

int Find(int a) {

	int thisx = x[par[a]];
	int thisy = y[par[a]];
	if (par[a] != a) {
		int tmp = a;
		par[a] = Find(par[a]);  		//path compress

		dx += thisx;					//align with new parent farm
		dy += thisy;
		x[tmp] += dx;
		y[tmp] += dy;

	}
	return par[a];						//get parent
}
                   
int main() {
	int F, M, K;
	int i;
	scanf("%d %d\n", &F, &M);

	for (i = 1; i <= M; i++) {
		scanf("%d %d %d %c\n", &a[i], &b[i], &c[i], &d[i]);
		par[i] = i;
		x[i] = 0;
		y[i] = 0;
	}

	scanf("%d\n", &K);
	//printf("K %d\n", K);
	for (i = 1; i <= K; i++) {
		//printf("LOL%d\n", i);
		int f1, f2;
		int line;
		scanf("%d %d %d\n", &f1, &f2, &line);
		P p = make_pair(f1, f2);
		q[line].push_back(p);
	}

	for (i = 1; i <= F; i++) {
		//printf("%d %lu\n", i, q[i].size());
		int from = a[i];
		int to = b[i];
		int dist = c[i];
		char dir = d[i];
		dx = 0;
		dy = 0;
		int p_from = Find(from);	
		dx = 0;
		dy = 0;
		int p_to = Find(to);
		if (dir == 'N') {
			x[p_to] = x[from] - x[to];
			y[p_to] = y[from] - y[to] + dist; 
		} else
		if (dir == 'S') {
			x[p_to] = x[from] - x[to];
			y[p_to] = y[from] - y[to] - dist; 
		} else
		if (dir == 'E') {
			x[p_to] = x[from] - x[to] + dist;
			y[p_to] = y[from] - y[to]; 
		} else
		if (dir == 'W') {
			x[p_to] = x[from] - x[to] - dist;
			y[p_to] = y[from] - y[to]; 
		}
		par[p_to] = p_from;									//Union

		for (vector<P>::iterator it = q[i].begin(); it != q[i].end(); it++) {
			int f1 = it->first;
			int f2 = it->second;
			dx = 0;
			dy = 0;
			int p_f1 = Find(f1);
			dx = 0;
			dy = 0;
			int p_f2 = Find(f2);

			if (p_f1 == p_f2) {

				int manx = x[f1] - x[f2];
				int many = y[f1] - y[f2];
				if (manx < 0) {
					manx *= -1;
				}
				if (many < 0) {
					many *= -1;
				}
				printf("%d\n", manx + many);
			} else {
				printf("-1\n");
			}
		} 

		// for (int j = 1; j <= F; j++) {
		// 	printf("%d [%d %d]\n", j, x[j], y[j]);
		// }
		// printf("\n");

	}
	return 0;
}
