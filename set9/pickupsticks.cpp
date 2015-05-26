#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

#define MAX_STICKS 100010

#define x first
#define y second

const double EPS = 1e-8; 

typedef pair<double, double> pt;

typedef pair<pt, pt> seg;
pt operator-(pt a, pt b) {
	return pt(a.x - b.x, a.y - b.y);
} 

bool zero(double x) {
 	return fabs(x) <= EPS;
}
double cross(pt a, pt b) {
 	return a.x*b.y - a.y*b.x;
}
bool ccw(pt a, pt b, pt c) {
 	return cross(b - a, c - a) + EPS >= 0;
}

bool overlap(seg a, seg b) {
	return zero(cross(a.y - a.x, b.x - a.x)) && zero(cross(a.y - a.x, b.y - a.x));
}

bool between(double a, double b, double x) {
	return min(a, b) <= x + EPS && x <= max(a, b) + EPS;
}

bool intersect(seg a, seg b) {
	if (overlap(a, b)) {
		return between(a.x.x, a.y.x, b.x.x) || between(a.x.x, a.y.x, b.y.x)
		|| between(b.x.x, b.y.x, a.x.x) || between(b.x.x, b.y.x, a.y.x);
	}
 	return (ccw(a.x, a.y, b.x) != ccw(a.x, a.y, b.y))
 		&& (ccw(b.x, b.y, a.x) != ccw(b.x, b.y, a.y));
}

int n;

vector<seg> sticks;
vector<int> top;

int main() {
	seg stack[MAX_STICKS];

	while (scanf("%d", &n)) {
		if (n == 0) break;
		sticks.clear();
		top.clear();

		int sp = 0;
		for (int i = 1; i <= n; ++i)
		{
			double x1, y1, x2, y2;
			scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
			
			pt a = make_pair(x1, y1);
			pt b = make_pair(x2, y2);
			seg s = make_pair(a, b);
			stack[++sp] = s;
		}

		while (sp > 0 && top.size() < 1000) {
			seg s = stack[sp--];

			bool fail = false;
			for (vector<seg>::iterator it = sticks.begin(); it != sticks.end(); it++) {
				seg stick = *it;

				if (intersect(s, stick)) {
					fail = true;
					break;
				}

			}
			sticks.push_back(s);
			if (!fail) {
				top.push_back(sp+1);
			}
		}

		printf("Top sticks:");
		for (vector<int>::reverse_iterator it = top.rbegin(); it != top.rend(); it++) {
			printf(" %d", *it);
			if (it + 1 != top.rend()) {
				printf(",");
			}
		}
		printf(".\n");
	}


}