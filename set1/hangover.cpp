#include <cstdio>
#include <vector>
using namespace std;
int main() {
	int i, count = 0;
	float tmp;
	//use vector due to unknown input size
 	vector<float> n; 

 	//scan and store until 0.00
 	while (scanf("%f", &tmp) == 1 && tmp != 0.00) {
 		n.push_back(tmp);
 		count++;
 	}

 	//do stuff
 	for (i = 0; i < count; i++) {
 		int cards = 0;
 		float total = 0;
 		while (total < n[i]) {
 			cards++;
 			total += 1.00/(cards + 1);
 		}
 		printf("%d card(s)\n", cards);
 	}

 	return 0;
} 