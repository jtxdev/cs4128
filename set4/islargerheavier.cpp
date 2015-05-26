//

#include <cstdio>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>
#include <map>

using namespace std;

typedef pair<int, int> P;
typedef map<pair<int, int>, int> M;

int main() {

	int s[10001];
	int w[10001];
	P sw[10001];
	set<P> items;
	set<P>::iterator it;

	int size, weight;
	int i = 1;
	M m;
	
	while (scanf("%d %d", &size, &weight) != EOF) {
		P p = make_pair(size, weight);
		m[p] = i;
		//P p2 = make_pair(weight, i);
		items.insert(p);
		i++;
	}

	int n = i - 1;

	i = 1;
	for (it = items.begin(); it != items.end(); it++) {
		//printf("%d = %d %d\n", i, it->first, it->second);
		sw[i] = *it;
		s[i] = it->first;
		w[i] = it->second;
		i++;
	}


	int best = 0;
	int dp[10001];
	dp[best] = 0;
	int from[10001];
	int j;
	for (i = 1; i <= n; i++) { //for each element
		dp[i] = 1; //longest sequence = 1
		for (j = 1; j < i; j++) { //for every element before
			if (w[j] > w[i]) { // if it's smaller than it
				if (dp[j] + 1 > dp[i]) { // if adding 1 to it's score > than our score so far
					dp[i] = dp[j] + 1; // make our score = it + 1
					from[i] = j; //set parent to it
				}
			}
			if (dp[best] < dp[i]) {
				best = i;
			}
		}
	}

	vector<int> ans;
	int u = best;
	while (from[u]) {
	 	ans.push_back(u);
		u = from[u];
	}
	ans.push_back(u);
	reverse(ans.begin(), ans.end());

	printf("%lu\n", ans.size());
	for (vector<int>::iterator itv = ans.begin(); itv != ans.end(); itv++) {
		printf("%d\n", m[sw[*itv]]);
	}

	return 0;

}