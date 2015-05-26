#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>

#define MAX_V 10000

#define A 0
#define B 10000

#define SOURCE 0
#define SINK 20001

#define INF 200000

using namespace std;

struct Edge
{
	int u;
	int v;
	int w;
	int cap;
	int nextID;

} edges[100000];

int start[SINK+1], k;

void add(int u, int v, int w, int cap) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].w = w;
	edges[k].cap = cap;
	edges[k].nextID = start[u];
	start[u] = k++;
	// printf("%d->%d %d\n", u, v, k);
}

int seen[SINK+1];

int inv(int e) {
	return e^1;
}

bool augment(int u, int t, int f) {
 	if (u == t) return true;
 	if (seen[u]) return false;
 	seen[u] = true;
 	for (int e = start[u]; e != -1; e = edges[e].nextID) {
 		if (edges[e].cap >= f && augment(edges[e].v, t, f)) {
 			edges[e].cap -= f;
 			edges[inv(e)].cap += f;
	 		return true;
	 	}
	}
	return false;
}

int max_flow(int s, int t) {
	int res = 0;
	memset(seen, 0, sizeof(seen));
	while (augment(s, t, 1)) {
		//printf("NEXT\n");
		memset(seen, 0, sizeof(seen));
		res += 1;
	}
	return res;
}

char grid[MAX_V][MAX_V+1];

int main() {
		
	int T;
	scanf("%d", &T);

	for (int t = 1; t <= T; ++t)
	{
		//init
		k = 0;
		memset(start, -1, sizeof(start));

		int N;
		scanf("%d", &N);

		for (int i = 0; i < N; ++i)
		{
			scanf("%s", grid[i]);
		}

		// for (int i = 0; i < N; ++i)
		// {
		// 	for (int j = 0; j < strlen(grid[i]); ++j)
		// 	{
		// 		if (grid[i][j] != '.') {
		// 			printf("%c", grid[i][j]);
		// 		} else {
		// 			printf(".");
		// 		}
		// 	}
		// 	printf("\n");
		// }

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < strlen(grid[i]); ++j)
			{
				if (grid[i][j] != '.') {
					/* Each square has a unique ID = i*N+j+1 */
					int u = i*N+j+1;

					//Add Edge from SOURCE to uA
					add(SOURCE, u+A, 0, 1);
					add(u+A, SOURCE, 0, 0);

					//Add Edge from uB to SINK
					add(u+B, SINK, 0, 1);
					add(SINK, u+B, 0, 0);

					if ((i + 1 < N && grid[i+1][j] != '.') || (j + 1 < N && grid[i][j+1] != '.')) {


						if (j + 1 < N && grid[i][j+1] != '.') {

							int v = i*N+j+1+1;

							// printf("%d %d\n", u, v);

							//Add Edge from uA to vB
							add(u+A, v+B, 0, 1);
							add(v+B, u+A, 0, 0);

							//Add Edge from vA to uB
							add(v+A, u+B, 0, 1);
							add(u+B, v+A, 0, 0);

						}
						if (i + 1 < N && grid[i+1][j] != '.') {

							int v = (i+1)*N+j+1;

							// printf("%d %d\n", u, v);

							//Add Edge from uA to vB
							add(u+A, v+B, 0, 1);
							add(v+B, u+A, 0, 0);

							//Add Edge from vA to uB
							add(v+A, u+B, 0, 1);
							add(u+B, v+A, 0, 0);

						}
					}
				}
			}
		}

		int res = max_flow(SOURCE, SINK);

		printf("Case %d: %d\n", t, res/2);


	}


	return 0;
}