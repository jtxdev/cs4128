#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

string s;

vector<int> kmp(string s) {
	int n = s.size();
	vector<int> pre(n);
	for (int i = 1; i < n; i++) {
		int j = i;
		while (j > 0 && s[i] != s[pre[j - 1]]) {
			j = pre[j - 1];
		}
		pre[i] = (j > 0) ? pre[j - 1] + 1 : 0;
	}
	return pre;
} 

int main() {
	int N;
	int T = 0;
	while (scanf("%d\n", &N) == 1) {
		T++;
		if (N == 0) break;
		printf("Test case #%d\n", T);
		cin >> s;
		vector<int> pre = kmp(s);
		for (int i = 0; i < N; ++i)
		{	
			if (i > 0 && pre[i] > 0) {
				if ((i+1) % (i+1 - pre[i]) == 0) {
					printf("%d %d\n", i+1, (i+1)/(i+1-pre[i]));
				}
			}
		}
		printf("\n");

	}

	return 0;
}