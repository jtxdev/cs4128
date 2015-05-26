#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
#include <map>

using namespace std;

#define x first
#define y second
#define INF 2000000

const double EPS = 1e-3; 


typedef pair<double, double> pt;
typedef pair<pt, pt> seg;
map<pt, int> pti;

pt operator-(pt a, pt b) {
	return pt(a.x - b.x, a.y - b.y);
} 

bool zero(double x) {
 	return fabs(x) <= EPS;
}

double cross(pt a, pt b) {
 	return a.x*b.y - a.y*b.x;
}

//Left turn if true, Right if false
bool ccw(pt a, pt b, pt c) {
 	return cross(b - a, c - a) + EPS > 0;
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

bool mycomp(pt a, pt b) {
	return a.y < b.y;
}

vector<pt> half_hull(vector<pt> pts) {
	vector<pt> res;
	for (int i = 0; i < pts.size(); i++) {
		while (res.size() >= 2 && ccw(pts[i], res[res.size()-1], res[res.size()-2])) {
			res.pop_back();
		}
		res.push_back(pts[i]);
	}
	return res;
}

double lowesty;

void findpath(vector<pt> pts) {

	vector<pt> res;
	int changed = res.size();
	while (pts.size() > 0) {
		sort(pts.begin(), pts.end());
		// for (int i = 0; i < pts.size(); i++) {
		// 	printf("%d ", pti[pts[i]]);
		// }
		// printf("\n");
		vector<pt> top = half_hull(pts);
		// for (int i = 0; i < top.size(); i++) {
		// 	printf("%d ", pti[top[i]]);
		// }
		// printf("\n");
		reverse(pts.begin(), pts.end());
		vector<pt> bottom = half_hull(pts);
		// for (int i = 0; i < bottom.size(); i++) {
		// 	printf("%d ", pti[bottom[i]]);
		// }
		// printf("\n");
		top.pop_back();
		bottom.pop_back();
		res.insert(res.end(), top.begin(), top.end());
		res.insert(res.end(), bottom.begin(), bottom.end());
		if (res.size() == changed) {
			break;
		} 
		if (changed == 0) {
			for (int i = 0; i < res.size(); ++i)
			{
				if (res.front().y != lowesty) {
					res.erase(res.begin());
				}
			}
		}
		for (int i = 0; i < res.size(); ++i)
		{
			pts.erase(remove(pts.begin(), pts.end(), res[i]), pts.end());
		}
		changed = res.size();
	} 

	if (pts.size() == 1) {
		res.push_back(pts[0]);
	}
	printf("%lu ", res.size());
	for (int i = 0; i < res.size(); i++) {
		printf("%d ", pti[res[i]]);
	}
	printf("\n");
} 

int main() {

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		int n;
		cin >> n;
		vector<pt> pts;
		lowesty = INF;
		for (int i = 1; i <= n; ++i)
		{
			int a;
			double b, c;
			scanf("%d%lf%lf", &a, &b, &c);
			if (c < lowesty) {
				lowesty = c;
			}
			pt p = make_pair(b, c);
			pti[p] = a;
			pts.push_back(p);
		}
		findpath(pts);
	}

}