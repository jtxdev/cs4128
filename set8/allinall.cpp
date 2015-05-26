#include <iostream>
#include <string>

using namespace std;

int main() {
	string a, b;
	while(cin >> a >> b) {
		int x = 0;
		for (int i = 0; i < b.length(); i++) {
			if (b[i] == a[x]) {
				x++;
			}
		}
		if (x == a.length()) {
			cout << "Yes" << endl;
		} else {
			cout << "No" << endl;
		}
	}
}