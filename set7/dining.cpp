#include <cstdio>
#include <cstring>

#define MAXFOOD 100
#define MAXDRINK 100
#define MAXCOWS 100

#define FOOD 0
#define DRINK 100
#define COW 200

#define A 0
#define B 100

#define SOURCE 0
#define SINK 401

using namespace std;

struct Edge
{
	int u;
	int v;
	int cap;
	int nextID;

} edges[SINK*SINK*SINK];

int start[SINK+1], k;

void add(int u, int v, int cap) {
	edges[k].u = u;
	edges[k].v = v;
	edges[k].cap = cap;
	edges[k].nextID = start[u];
	start[u] = k++;
	// printf("%d->%d %d\n", u, v, cap);
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
		memset(seen, 0, sizeof(seen));
		res += 1;
	}
	return res;
}

int main() {

	memset(start, -1, sizeof(start));
	k = 0;
	int foodcow[101][101];
	int cowdrink[101][101];
	int N, F, D;
	scanf("%d%d%d", &N, &F, &D);

	for (int i = 1; i <= MAXCOWS; ++i)
	{
		for (int j = 1; j <= MAXCOWS; ++j)
		{
			foodcow[i][j] = 0;
			cowdrink[i][j] = 0;
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		// int foods[100], f = 0;
		// int drinks[100], d = 0;
		int numfood, numdrinks;	
		scanf("%d%d", &numfood, &numdrinks);
		for (int j = 1; j <= numfood; ++j)
		{
			int food;
			scanf("%d", &food);
			// foods[f++] = food;
			foodcow[food][i] = 1;			//mark this cow liking this food
		}
		for (int j = 1; j <= numdrinks; ++j)
		{
			int drink;
			scanf("%d", &drink);
			// drinks[d++] = drink;
			cowdrink[i][drink] = 1; 	//mark this cow liking this drink
		}
	}

	// printf("ADD FOOD\n");
	for (int food = 1; food <= F; ++food)
	{
		add(SOURCE, food+FOOD, 1);	//Connect SOURCE to food and ensure FOOD USED ONCE
		add(food+FOOD, SOURCE, 0);	
	}

	// printf("ADD DRINKS\n");
	for (int food = 1; food <= F; ++food)
	{
		for (int cow = 1; cow <= N; ++cow)
		{
			if (foodcow[food][cow] == 1) 
			{	
				add(food+FOOD, cow+COW+A, 1);		//add an edge from this food to this cow
				add(cow+COW+A, food+FOOD, 0);
			}
		}
	}
	
	for (int cow = 1; cow <= N; ++cow)
	{
		add(cow+COW+A, cow+COW+B, 1);		//Ensure COW USED ONCE
		add(cow+COW+B, cow+COW+A, 0);
	}

	for (int cow = 1; cow <= N; ++cow)
	{
		for (int drink = 1; drink <= D; ++drink)
		{
			if (cowdrink[cow][drink] == 1)
			{
				add(cow+COW+B, drink+DRINK, 1);	//add an edge from this cow to this drink
				add(drink+DRINK, cow+COW+B, 0); 	
			}
		}
	}
	// printf("ADD SINK\n");
	for (int drink = 1; drink <= D; ++drink)
	{
		add(drink+DRINK, SINK, 1); 	//Connect SINK and ensure DRINK USED ONCE
		add(SINK, drink+DRINK, 0);
	}

	int res = max_flow(SOURCE, SINK);
	printf("%d\n", res);
	return 0;
}