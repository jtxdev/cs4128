#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

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

//Left turn if > 0, Right if < 0
bool ccw(pt a, pt b, pt c) {
 	return cross(b - a, c - a) + EPS >= 0;
}

// bool overlap(seg a, seg b) {
// 	return zero(cross(a.y - a.x, b.x - a.x)) && zero(cross(a.y - a.x, b.y - a.x));
// }

// bool between(double a, double b, double x) {
// 	return min(a, b) <= x + EPS && x <= max(a, b) + EPS;
// }

// bool intersect(seg a, seg b) {
// 	if (overlap(a, b)) {
// 		return between(a.x.x, a.y.x, b.x.x) || between(a.x.x, a.y.x, b.y.x)
// 		|| between(b.x.x, b.y.x, a.x.x) || between(b.x.x, b.y.x, a.y.x);
// 	}
//  	return (ccw(a.x, a.y, b.x) != ccw(a.x, a.y, b.y))
//  		&& (ccw(b.x, b.y, a.x) != ccw(b.x, b.y, a.y));
// }

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

vector<pt> convex_hull(vector<pt> pts) {
	sort(pts.begin(), pts.end());
	vector<pt> top = half_hull(pts);
	reverse(pts.begin(), pts.end());
	vector<pt> bottom = half_hull(pts);
	top.pop_back();
	bottom.pop_back();
	vector<pt> res(top.begin(), top.end());
	res.insert(res.end(), bottom.begin(), bottom.end());
 return res;
} 

struct line {
 	double a, b, c;
};

struct half_plane {
	line l;
	bool neg;
};

pt intersect(line a, line b) {
	double d = a.a*b.b - a.b*b.a;
	double y = (a.a*b.c - a.c*b.a)/(a.b*b.a - a.a*b.b);
	double x = (a.c*b.b - a.b*b.c)/(a.b*b.a - a.a*b.b);
	return pt(x, y);
}

bool in_half_plane(half_plane p, pt q) {
	if (p.neg) {
		return p.l.a*q.x + p.l.b*q.y + p.l.c <= EPS;
	} else {
		return p.l.a*q.x + p.l.b*q.y + p.l.c >= -EPS;
	}
} 

vector<pt> intersect_half_planes(vector<half_plane> half_planes) {
	int n = half_planes.size();
	vector<pt> pts;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			pt p = intersect(half_planes[i].l, half_planes[j].l);
			bool fail = false;
			for (int k = 0; k < n; k++) {
				if (!in_half_plane(half_planes[k], p)) {
					fail = true;
				}
			}
			if (!fail) {
				pts.push_back(p);
			}
		}
	}
	vector<pt> res = pts;
	if (pts.size() > 2) {
		pts = convex_hull(res);
	}
	return pts;
} 

double area(vector<pt> pts) {
	double res = 0;
		int n = pts.size();
	for (int i = 0; i < n; i++) {
		res += cross(pts[i] - pts[0], pts[(i+1)%n] - pts[0]);
	}
	return res/2.0;
} 

vector<half_plane> hps;

void init() {
	line l1 = {1.0, 0.0, 0.0 };
	line l2 = {1.0, 0.0, -10.0};
	line l3 = {0.0, 1.0, 0.0 };
	line l4 = {0.0, 1.0, -10.0};
	half_plane h1 = { l1 , false };
	hps.push_back(h1);

	half_plane h2 = { l2 , true };
	hps.push_back(h2);

	half_plane h3 = { l3 , false };
	hps.push_back(h3);

	half_plane h4 = { l4 , true };
	hps.push_back(h4);

}

int main() {

	init();
	double x1 = 0.0;
	double y1 = 0.0;
	double x2 = 0.0;
	double y2 = 0.0;
	string hc;
	vector<pt> pts;
	pts = intersect_half_planes(hps);

	double polyarea = area(pts);

	while ( cin >> x2 >> y2 >> hc) {
		line l = { y2-y1, x2-x1, -((x2-x1)*(x1+x2)/2.0 + (y2-y1)*(y1+y2)/2.0)};
		x1 = x2;
		y1 = y2;
		bool lr = true;
		if (hc[0] == 'H') {
			half_plane h = { l , false };
			hps.push_back(h);
		} else if (hc[0] == 'C') {
			half_plane h = { l , true };
			hps.push_back(h);
		} else {
			half_plane h = { l , true };
			half_plane h2 = { l , false };
			hps.push_back(h);
			hps.push_back(h2);
		}

		vector<pt> pts;
		pts = intersect_half_planes(hps);
		polyarea = area(pts);
		printf("%.2f\n", polyarea);
	}
}
