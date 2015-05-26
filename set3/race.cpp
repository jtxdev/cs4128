#include <cstdio>
#include <vector>
#include <queue>
#include <utility>
#include <stack>

#define MAX_V 100
#define MAX_S 250001

using namespace std;

int v[MAX_S];
int x[MAX_S];
vector<int> V[MAX_V];
typedef pair<int, int> P1;
typedef pair<double, double> P2;
typedef pair<P2, P1> PQ_type;

class myComp
{
public:
    bool operator()(PQ_type n1, PQ_type n2)
    {
      if (n1.first.first < n2.first.first) {
      	return true;
      } else if (n1.first.first > n2.first.first) {
      	return false;
      } else if (n1.first.second < n2.first.second) {
      	return true;
      } else {
      	return false;
      }
    }
};

priority_queue<PQ_type, vector<PQ_type>, myComp> pq;
stack<P1> s;

int main() {

	int N;
	scanf("%d", &N);
	int i, j;
	int passes = 0;

	for (i = 1; i <= N; i++) {
		scanf("%d %d\n", &x[i], &v[i]);
		// passes += V[v[i]];
		// for (j = 1; j < v[i]; j++) { //For each car slower
		// 	V[j]++;		 //This car will beat them, ordered from x;
		// }
		// for (vector<int>::iterator it = V[v[i]].begin(); it != V[v[i]].end(); it++) {
		// 	printf("%d %d\n", *it, i);
		// }
		for (j = v[i] + 1; j < MAX_V; j++) { //For each car faster
			passes += V[j].size();		
			for (vector<int>::reverse_iterator it = V[j].rbegin(); it != V[j].rend(); it++) {
				//printf("%d %d\n", *it, i);
				/*X get increasingly big, so does t, once we hit a t that is > highest t we can stop*/
				double _t = static_cast<double>(x[i] - x[*it])/(v[*it] - v[i]);
				double _x = v[i] * _t + x[i];
				if (pq.size() == 10000 && _t > pq.top().first.first) {
					break;
				}
				P1 pass = make_pair(*it, i);
				P2 priority = make_pair(_t, _x);
				PQ_type pp = make_pair(priority, pass);
				pq.push(pp);
				if (pq.size() > 10000) {
					pq.pop();
				}
			}
		}
		V[v[i]].push_back(i);
		passes %= 1000000;

	//printPQreverse(pq);
	}	
	printf("%d\n", passes);
		
	while(!pq.empty()){
		s.push(pq.top().second);
		pq.pop();
	}

	while(!s.empty()){
		printf("%d %d\n", s.top().first, s.top().second);
		s.pop();
	}
	return 0;
}