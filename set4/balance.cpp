#include <cstdio>
#include <vector>

#define MAX_N 20001

using namespace std;

int bestbalance;
int bestnode;
vector<int> tree[MAX_N];
int marked[MAX_N];
int marked2[MAX_N];
int balance[MAX_N];

void cleartree() {
	for (int i = 0; i < MAX_N; i++) {
		tree[i].clear();
	}
}

void reset() {
	for (int i = 0; i < MAX_N; i++) {
		marked[i] = 0;
	}
}

void reset2() {
	for (int i = 0; i < MAX_N; i++) {
		marked2[i] = 0;
	}
}


int DFScount(int x) {
	int count = 1;
	marked[x] = 1;
	for (vector<int>::iterator it = tree[x].begin(); it != tree[x].end(); it++) {
		if (marked[*it] == 0) {
			count += DFScount(*it);
		}
	}
	return count;
} 

int getBalance(int x) {
	int balance = -1;
	marked[x] = 1;
	for (vector<int>::iterator it = tree[x].begin(); it != tree[x].end(); it++) {
		if (marked[*it] == 0) {
			int test = DFScount(*it);
			if (test > balance) {
				balance = test;
			}
			if (balance > bestbalance) {
				return balance;
			}
		}
	}
	return balance;
} 

void findBestBalance(int x) {
	marked2[x] = 1;
	reset();
	int balance = getBalance(x);
	if (balance < bestbalance) {
		bestbalance = balance;
		bestnode = x;
	} else if (balance == bestbalance) {
		if (x < bestnode) {
			bestnode = x;
		}
	} else {
		return;
	}
	for (vector<int>::iterator it = tree[x].begin(); it != tree[x].end(); it++) {
		if (marked2[*it] == 0) {
			findBestBalance(*it);
		}
	}
} 

int main() {

	int t, N, n;
	scanf("%d", &t);
	while (t > 0) {
		scanf("%d", &N);
		n = N - 1;
		cleartree();
		while (n > 0) {
			int a, b;
			scanf("%d %d\n", &a, &b);
			tree[a].push_back(b);
			tree[b].push_back(a);
			n--;
		}
		bestbalance = MAX_N;
		bestnode = MAX_N;
		reset2();
		findBestBalance(1);
		printf("%d %d\n", bestnode, bestbalance);
		t--;
	}
	return 0;
}