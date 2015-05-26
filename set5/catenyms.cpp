#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string>
#include <set>
#include <map>
#include <vector>

#define MAX 1010

using namespace std;

int start[MAX], to[MAX], nextID[MAX], deleted[MAX], m;
set<string> sorted;
map<int, string> dict;

int indegree[26];
int outdegree[26];

int isBridge[MAX];
int T;
int low[26];
int preorder[26];
vector<int> postorder;

void add(int u, int v, string l) {
	to[m] = v;
	nextID[m] = start[u];
	dict[m] = l;
	start[u] = m++;
}

void tarjanDFS(int u) {

	preorder[u] = T++;
	low[u] = preorder[u];

	for (int ID = start[u]; ID != -1; ID = nextID[ID]) {
		if (!deleted[ID]) {
			int v = to[ID];
			if (preorder[v] == -1) {
				tarjanDFS(v);
				low[u] = min(low[u], low[v]);
				if (low[v] == preorder[v]) {
					isBridge[ID] = 1;
				}
			} else {
				low[u] = min(low[u], preorder[v]);
			}
		}
	}
}

void fluerys(int u) {
	int moved = 0;
	for (int ID = start[u]; ID != -1; ID = nextID[ID]) {
		if (!deleted[ID]) {
			memset(preorder, -1, sizeof(preorder));
			memset(low, -1, sizeof(low));
			memset(isBridge, 0, sizeof(isBridge));
			T = 0;
			tarjanDFS(u);
			if (!isBridge[ID]) {
				moved = 1;
				deleted[ID] = 1;
				int v = to[ID];
				fluerys(v);
				postorder.push_back(ID);
				break;
			}
		}
	}	
	if (moved == 0) {
		for (int ID = start[u]; ID != -1; ID = nextID[ID]) {
			if (!deleted[ID]) {
				deleted[ID] = 1;
				int v = to[ID];
				fluerys(v);
				postorder.push_back(ID);	
			}
		}
	}	
}

int main() {
	int T, N;
	cin >> T;

	while (T > 0) {
		m = 0;
		int words = 0;
		sorted.clear();
		postorder.clear();
		memset(start, -1, sizeof(start));
		memset(deleted, 0, sizeof(deleted));
		memset(indegree, 0, sizeof(indegree));
		memset(outdegree, 0, sizeof(outdegree));
		cin >> N;
		int n = N;
		while (n > 0) {

			string l;
			cin >> l;
			int a = l[0] - 'a';
			int b = l[l.length()-1] - 'a';
			outdegree[a]++;
			indegree[b]++;
			words++;
			sorted.insert(l);
			n--;
		}	

		for (set<string>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it) {
			string l = *it;
			int a = l[0] - 'a';
			int b = l[l.length()-1] - 'a';
			add(a, b, *it);

		}

		int check = 0;
		int head = -1;
		int extraout = 0;
		int extrain = 0;
		for (int i = 0; i < 26; i++) {
			if (outdegree[i] > 0 && head == -1) {
				head = i;
			}
			if (indegree[i] != outdegree[i]) {
				check++;
				if (indegree[i] == outdegree[i] + 1) {
					extrain++;
				} else if (indegree[i] + 1 == outdegree[i]) {
					extraout++;
					head = i;
				}	
			}
		}

		if ( check == 0 || (check == 2 && extrain == 1 && extraout == 1)) {
			fluerys(head);
		}
		if (postorder.size() != words) {
			printf("***\n");
		} else {
			reverse(postorder.begin(), postorder.end());
			for (vector<int>::iterator it = postorder.begin(); it != postorder.end(); ++it) {
				if (it != postorder.begin()) {
					printf(".");
				}
				printf("%s", dict[*it].c_str());
			}
			printf("\n");
		}
		T--;
	}
	return 0;
}