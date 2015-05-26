#include <cstdio>
#include <vector>

#define PRIME 12289

using namespace std;

struct SF
{
	int a;
	int b;
	int c;
	int d;
	int e; 
	int f;
};

vector<SF> snowflakes[12290]; 

void add(int key, SF s) {
	snowflakes[key].push_back(s);
}

int main() {
	int N;
	scanf("%d", &N);
	bool twin = false;
	for (int i = 0; i < N; i++) {
		int a, b, c, d, e, f;
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
		int sum = a + b + c + d + e + f;
		int key = sum % PRIME;
		SF s = {a, b, c, d, e, f};

		for (vector<SF>::iterator it = snowflakes[key].begin(); it != snowflakes[key].end(); it++) {
			SF sf = *it;
			if (s.a == sf.a && s.b == sf.b && s.c == sf.c && s.d == sf.d && s.e == sf.e && s.f == sf.f) {
				twin = true;
				break;
			}
			if (s.a == sf.b && s.b == sf.c && s.c == sf.d && s.d == sf.e && s.e == sf.f && s.f == sf.a) {
				twin = true;
				break;
			}
			if (s.a == sf.c && s.b == sf.d && s.c == sf.e && s.d == sf.f && s.e == sf.a && s.f == sf.b) {
				twin = true;
				break;
			}
			if (s.a == sf.d && s.b == sf.e && s.c == sf.f && s.d == sf.a && s.e == sf.b && s.f == sf.c) {
				twin = true;
				break;
			}
			if (s.a == sf.e && s.b == sf.f && s.c == sf.a && s.d == sf.b && s.e == sf.c && s.f == sf.d) {
				twin = true;
				break;
			}
			if (s.a == sf.f && s.b == sf.a && s.c == sf.b && s.d == sf.c && s.e == sf.d && s.f == sf.e) {
				twin = true;
				break;
			}
			if (s.a == sf.a && s.f == sf.b && s.e == sf.c && s.d == sf.d && s.c == sf.e && s.b == sf.f) {
				twin = true;
				break;
			}
			if (s.a == sf.b && s.f == sf.c && s.e == sf.d && s.d == sf.e && s.c == sf.f && s.b == sf.a) {
				twin = true;
				break;
			}
			if (s.a == sf.c && s.f == sf.d && s.e == sf.e && s.d == sf.f && s.c == sf.a && s.b == sf.b) {
				twin = true;
				break;
			}
			if (s.a == sf.d && s.f == sf.e && s.e == sf.f && s.d == sf.a && s.c == sf.b && s.b == sf.c) {
				twin = true;
				break;
			}
			if (s.a == sf.e && s.f == sf.f && s.e == sf.a && s.d == sf.b && s.c == sf.c && s.b == sf.d) {
				twin = true;
				break;
			}
			if (s.a == sf.f && s.f == sf.a && s.e == sf.b && s.d == sf.c && s.c == sf.d && s.b == sf.e) {
				twin = true;
				break;
			}
		}
		
		add(key, s);

	}

	if (twin == true) {
		printf("Twin snowflakes found.\n");
	} else {
		printf("No two snowflakes are alike.\n");
	}
	
	return 0;
}