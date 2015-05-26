//Thanks Stanley for suggesting trees

#include <cstdio>
#include <stack>
#include <queue>
#include <string>
#include <iostream>

using namespace std;
	
typedef struct Node node;
struct Node
{
	char C;
	node *left;
	node *right;
};

stack<node*> s;
queue<node*> q;	
stack<char> ans;
// void insertb(node *b, node *root)
// {
// 	root->left = b;
// }

// void inserta(node *a, node *root)
// {
// 	root->right = a;
// }

void printTree(node *root) {
	if (root != NULL) {
		printTree(root->left);
		printf("%c", root->C);
		printTree(root->right);
	}
} 



int main() {
	int i;
	int n;
	scanf("%d\n", &n);
	string l;
	while (n > 0) {
		getline(cin, l);
		//printf("%s\n", l.c_str());
		n--;
		for (i = 0; i < l.length(); i++) {
			//printf("%c\n", l[i]);
			if (l[i] >= 'a' && l[i] <= 'z') {
				//printf("%s\n", );
				node *root = new Node;
				root->C = l[i];
				root->left = NULL;
				root->right = NULL;
				s.push(root);
			} else {
				node *root = new Node;
				root->C = l[i];
				root->left = s.top();
				s.pop();
				root->right = s.top();
				s.pop();
				s.push(root);
			}
			//printf("%d\n", i);
		}
		node *root = s.top();
		// printTree(root);
		// printf("\n");
		q.push(root);
		while (!q.empty()) {
			node *root = q.front();
			ans.push(root->C);
			q.pop();
			if (root->C >= 'A' && root->C <= 'Z') {
				q.push(root->right);
				q.push(root->left);
			}
		}
		while (!ans.empty()) {
			printf("%c", ans.top());
			ans.pop();
		}

		printf("\n");
	}
}