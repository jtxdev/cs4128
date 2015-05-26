#include <cstdio>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

#define MAXTREES 1000000
#define MAXSPECIES 10000

int main() {
	string tree;
	map<string, int> trees;
	int	n = 0;
	int i;
	while (getline(cin,tree)) {
		trees[tree]++;
		n++;
	}
	for (map<string, int>::iterator it=trees.begin(); it!=trees.end(); ++it) {
		double x = static_cast<double>(it->second)/n * 100;
		printf("%s %.4f\n", it->first.c_str(), x);
	}
	return 0;
}