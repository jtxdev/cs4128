#include <iostream>
#include <string>

using namespace std;

//PolyHash
int P[400010];
int H[400010];
int B = 137;		//Base Prime
string s;
int n;				//s.size()

void init() {
	P[0] = 1;
	for (int i = 1; i <= n; i++) {
		P[i] = P[i-1]*B;
		H[0] = 0;
	}
	for (int i = 1; i <= n; i++) {
		H[i] = H[i-1] + s[i-1] * P[i-1];
	}
}
// (i,j) inclusive, 0-based.
int hashstr(int i, int j) {
	return (H[j+1] - H[i]) * P[n - j];
} 

int main() {
	// vector<int> res;
	while (cin >> s) {
		n = s.size();
		init();

		for (int i = 0; i < s.length(); i++) {
			int end = s.length() - 1;
			if (hashstr(0, i) == hashstr(end - i, end)) {
				cout << i+1 << " ";
			}
		}
		cout << endl;
	}
}