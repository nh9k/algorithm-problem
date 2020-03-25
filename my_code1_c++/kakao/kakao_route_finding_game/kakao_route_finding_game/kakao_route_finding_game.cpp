//https://kswims.tistory.com/187

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

typedef struct {
	int x, y, index;
}infos;

typedef struct node{
	struct node *left;
	struct node *right;
	int value, x;
}nodes;
nodes *root;

bool cmp( infos& a, infos& b)
{
	if (a.y == b.y)
		return a.x < b.x;
	return a.y > b.y;
}

void linking(nodes *curr, nodes *newNode)
{
	if (curr->x > newNode->x && curr->left != NULL) { //현재 노드보다 왼쪽인데 이미 왼쪽 자식 노드 존재
		linking(curr->left, newNode);
	}
	else if (curr->x > newNode->x && curr->left == NULL) {
		curr->left = newNode;
	}
	else if (curr->x < newNode->x && curr->right != NULL) {
		linking(curr->right, newNode);
	}
	else {
		curr->right = newNode;
	}
}
vector<vector<int>> answer;
void preorder(nodes *curr)
{
	if (curr == NULL)
		return;
	answer[0].push_back(curr->value);
	preorder(curr->left);
	preorder(curr->right);
}
void postorder(nodes *curr)
{
	if (curr == NULL)
		return;
	postorder(curr->left);
	postorder(curr->right);
	answer[1].push_back(curr->value);
}


vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
	vector <infos> info;

	for (int i = 0; i < nodeinfo.size(); i++)
	{
		info.push_back( infos{nodeinfo[i][0], nodeinfo[i][1], i + 1} );	
	}
	sort(info.begin(), info.end(), cmp);

	//for (int i = 0; i < info.size(); i++)
	//	cout << info[i].index << endl;

	nodes *newnode = (nodes*)malloc(sizeof(nodes));
	newnode->left = newnode->right = NULL;
	newnode->value = info[0].index;
	newnode->x = info[0].x; //링킹할 때 트리 구조 위치 파악을 위해
	root = newnode;

	for (int i = 1; i < info.size(); i++)
	{
		nodes *newnode = (nodes*)malloc(sizeof(nodes));
		newnode->left = newnode->right = NULL;
		newnode->value = info[i].index;
		newnode->x = info[i].x;
		linking(root, newnode);
	}

	answer.resize(2);
	preorder(root);
	postorder(root);
	
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < answer[i].size(); j++)
			cout << answer[i][j] << " ";
		cout << endl;
	}

	return answer;
}

int main()
{
	solution({ {5, 3},{11, 5},{13, 3},{3, 5},{6, 1},{1, 3},{8, 6},{7, 2},{2, 2} });
}