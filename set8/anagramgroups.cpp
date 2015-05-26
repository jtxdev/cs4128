#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

bool compare(vector<string> *i, vector<string> *j) { 
	if (i->size() > j->size()) {
		return true;
	} else if (i->size() == j->size()) {
		if (i[0] < j[0]) {
			return true;
		}
	}
	return false;
}

bool compare2(string i, string j) { 
	return (i < j);
}

int main() {
	string a;
	map<string, vector<string> > dict;
	while (cin >> a) {
		string b = a;
		sort(b.begin(), b.end());
		dict[b].push_back(a);
	}

	vector<vector<string>* > anagrams;

	for (map<string, vector<string> >::iterator it = dict.begin(); it != dict.end(); ++it) {
		sort(it->second.begin(), it->second.end(), compare2);
		anagrams.push_back(&it->second);
	}

	sort(anagrams.begin(), anagrams.end(), compare);
	int x = 0;
	for (vector<vector<string>* >::iterator it = anagrams.begin(); it != anagrams.end(); ++it) {
		x++;
		vector<string> s = *(*it);
		printf("Group of size %lu: ", s.size());
		for (int i = 0; i < s.size(); ++i) {
			if ((i != 0 && s[i] != s[i-1]) || i == 0) {
				printf("%s ", s[i].c_str());
			}
		}
		printf(".\n");
		if (x == 5) {
			break;
		}
	}
}