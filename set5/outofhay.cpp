#include <cstdio>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>


#define MAX_FARMS 2001
#define MAX_ROADS 10001

using namespace std;


typedef pair<int, int> P;

vector<P> edge[MAX_ROADS];
int visited[MAX_FARMS];


int MST() {

	priority_queue<P, vector<P>, greater<P> > pq;

	int f, longestroad = 0;
	pq.push(make_pair(0, 1));
	while (!pq.empty()) {
		P p = pq.top();
		pq.pop();
		f = p.second;
		//printf("%d\n", f);
		if (visited[f]) { continue; }
		visited[f] = 1;
		longestroad = max(longestroad, p.first);
		for (vector<P>::iterator it = edge[f].begin(); it != edge[f].end(); it++) {
			//printf("%d\n", it->second);
			if (!visited[it->second]) {
				pq.push(*it);
			}
		}
	}
	return longestroad;
}

int main() {

	int N, M;
	scanf("%d %d\n", &N, &M);

	for (int i = 0; i < MAX_FARMS; i++) {
		visited[i] = 0;
	}

	while (M > 0) {
		int a, b, l;
		scanf("%d %d %d\n", &a, &b, &l);
		P pa = make_pair(l, a);
		P pb = make_pair(l, b);
		edge[a].push_back(pb);
		edge[b].push_back(pa);
		M--;
	}

	printf("%d\n", MST());

	return 0;
}