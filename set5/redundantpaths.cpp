#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MAX_V 5010
#define MAX_E 10010

int start[MAX_V], to[MAX_E], nextID[MAX_E], k;

//Tarjan Variables
int T = 1;
int top;
int low[MAX_V];
int preorder[MAX_V];
int stack[MAX_V];
int stacked[MAX_V];

//SCC
int sccs[MAX_V];
int scc;

//Problem Specific
int outdegree[MAX_V];


void add(int u, int v) {
	to[k] = v;
	nextID[k] = start[u];
	start[u] = k++;
}

void tarjanDFS(int u, int from) {

	preorder[u] = T++;
	low[u] = preorder[u];
	stack[++top] = u;
	stacked[u] = 1;

	for (int ID = start[u]; ID != -1; ID = nextID[ID]) {
		int v = to[ID];
		if (ID == (from^1)) continue;
		if (preorder[v] == -1) {
			tarjanDFS(v, ID);
			low[u] = min(low[u], low[v]);
		} else if (stacked[v]) {
			low[u] = min(low[u], preorder[v]);
		}
	}

	if (low[u] == preorder[u]) {
		int x = 0;
		scc++;
        do {
            x = stack[top--];
 			sccs[x] = scc;
            stacked[x] = 0;
        } while (u != x);
	}
}

void tarjans(int N) {
    T = 1;
    top = 0;
    scc = 0;
    memset(low, -1, sizeof(low));
    memset(preorder, -1, sizeof(preorder));
    memset(stacked, 0, sizeof(stacked));
    memset(sccs, -1, sizeof(sccs));
    for (int i = 1; i <= N; i++) {
    	if (preorder[i] == -1) {
    		tarjanDFS(i, -1);
    	}
    }
}

int main() {
	int F, R;
	scanf("%d %d\n", &F, &R);
	k = 0;

	memset(start, -1, sizeof(start));

	while (R > 0) {
		int a, b;
		scanf("%d %d\n", &a, &b);
		add(a, b);
		add(b, a);
		R--;
	}

	tarjans(F);

	memset(outdegree, 0, sizeof(outdegree));
	for (int i = 1; i <= F; i++) {
		for (int ID = start[i]; ID != -1; ID = nextID[ID]) {
			int v = to[ID];
			if (sccs[i] != sccs[v]) {
				outdegree[sccs[i]]++;
			}
		}	
	}
	int count = 0;
	for (int i = 1; i <= F; i++) {
		if (outdegree[i] == 1) {
			count++;
		}
	}
	printf("%d\n", (count+1)/2);
	return 0;
}