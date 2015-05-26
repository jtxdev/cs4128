#include <cstdio>
#include <vector>
#include <map>

using namespace std;

map<int, int> ints;
map<int, vector<int> > child;
map<int, int> par;
map<int, int> visited1;
map<int, int> visited2;
int integer = 1;
int testnum = 1;

void init() {
	
	ints.clear();
	child.clear();
	par.clear();
	visited1.clear();
	visited2.clear();
	integer = 1;

}

void notTree() {
	printf("Case %d is not a tree.\n", testnum);
	init();
	testnum++;
}

void notTreeEarly() {
	printf("Case %d is not a tree.\n", testnum);
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		if (a == 0 && b == 0) {
			init();
			testnum++;
			break;
		}
	}
}

void isTree() {
	printf("Case %d is a tree.\n", testnum);
	init();
	testnum++;
}

int findRoot(int x) {
	while (par[x] != 0) {
		visited1[x] = 1;
		x = par[x];
		if (visited1[x] == 1) {
			return -1;
		}
	}
	return x;
}

void dfs(int x) {
	//printf("%d\n", x);
	visited2[x] = 1;
	for (vector<int>::iterator it = child[x].begin(); it != child[x].end(); it++) {
		if (visited2[*it] == 1) {
			return;
		} else {
			dfs(*it);
		}
	}
}

int main() {
	init();
	int a, b;
	while (scanf("%d %d", &a, &b) == 2) {
		// printf("%d %d\n", a, b);
		if (a < 0 && b < 0) {
			//printf("%d %d\n", a, b);
			return 0;
		}
		if (a == 0 && b == 0) {
			//Check for null tree
			if (integer == 1) {
				// printf("LOL1\n");
				isTree();
				continue;
			}
			int root = findRoot(1);
			if (root == -1) {
				// printf("LOL2\n");
				notTree();
				continue;
			}
			dfs(root);
			int check = 0;
			for (int i = 1; i < integer; i++) {
				if (visited2[i] != 1) {
					check = 1;
				}
			}
			if (check == 1) {
				// printf("LOL3\n");
				notTree();
				continue;
			} else {
				isTree();
				continue;
			}
		}
		if (ints[a] == 0) {
			ints[a] = integer++;
		}
		if (ints[b] == 0) {
			ints[b] = integer++;
		}
		// printf("ints[a] is %d\n", ints[a]);
		// printf("ints[b] is %d\n", ints[b]);
		a = ints[a];
		b = ints[b];

		if (par[b] == 0) {
			par[b] = a;
		} else {
			notTreeEarly();
			continue;
		}
		child[a].push_back(b);
	}
	return 0;
}