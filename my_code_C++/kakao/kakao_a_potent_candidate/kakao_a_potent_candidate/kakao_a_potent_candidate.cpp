//6시
#include <string>
#include <vector>
#include <iostream>
using namespace std;
vector<vector<string>> cpy_rela;
int keyvalue;
int visit[8];
vector <vector<bool>> yes;
int x, y, yesidx;

bool checking()
{
	bool pass = false;
	for (int i = 0; i < x; i++)
	{
		for (int i2 = i + 1; i2 < x; i2++)
		{
			for (int j = 0; j < y; j++)
			{
				//if (visit[j] == 2) continue;
				if (visit[j])
				{
					if (cpy_rela[i][j].compare(cpy_rela[i2][j]))
					{//다른게 있으면
						pass = true;
					}
				}
			}
			if (pass==false)//둘다 같으면 false 유지후
			{
				return false; //false 리턴
			}
			pass = false;
		}
	}
	return true;
}

void dfs(int cnt, int compare_cnt, int idx)
{
	if (compare_cnt == cnt)
	{
		if (checking())
		{
			bool  pass = false;
			for (int i = 0; i < yesidx; i++)
			{
				for (int j = 0; j < y; j++)
				{
					if (!yes[i][j]) continue;
					if (!(visit[j] != 0)) //다르면
					{
						pass = true; //패스조건이 생김
					}
				}
				if (pass == false) 
					return;
				pass = false;
			}
			for (int i = 0; i < y; i++)
			{
				if (visit[i]) {
					yes[yesidx][i] = true;
					//cout << i << " ";
				}
			}//cout << endl;
			keyvalue++;
			yesidx++;
		}
		return;
	}
	for (int i = idx; i < y; i++)
	{
		//if (visit[i]==2) continue;
		visit[i] = true;
		dfs(cnt, compare_cnt + 1, i + 1);
		visit[i] = false;
	}
}

int solution(vector<vector<string>> relation) {
	x = relation.size();
	cpy_rela.assign(relation.begin(), relation.end());

	for (int i = 0; i < x; i++)
	{
		y = relation[i].size();
		break;
	//	for (int j = 0; j < relation[i].size(); j++)
	//	{
	//		//cpy_rela.push_back({ relation[i][j] });
	//		cout << cpy_rela[i][j] << " ";
	//	}
	}
	yes.assign(100, vector<bool>(y, 0));
	keyvalue = 0, yesidx = 0;
	//bool allcheck = true;
	for (int cnt = 1; cnt <= y; cnt++)
	{
		dfs(cnt, 0, 0);

		//for (int i = 0; i < y; i++)
		//	if (yes[i])
		//	{
		//		visit[i] = 2;
		//	}
		//{
		//	else
		//	{
		//		allcheck = false;
		//	}
		//}
		//if (allcheck) break;
		//allcheck = true;
	}
	return keyvalue;
}

int main()
{
	cout << solution({ {"100", "ryan", "music", "2"},{"200", "apeach", "math", "2"},
		{"300", "tube", "computer", "3"},{"400", "con", "computer", "4"},
		{"500", "muzi", "music", "3"},{"600", "apeach", "music", "2"} }) << endl;

	memset(visit, 0, 8*sizeof(int));
	//memset(yes, 0, 8 * sizeof(bool));

	cout << solution({ { "a","b","c"},{"1","b","c"},
	{"a","b","4"},{"a","5","c"} }) << endl;

	memset(visit, 0, 8 * sizeof(int));
	//memset(yes, 0, 8 * sizeof(bool));

	cout << solution({ { "a","1","4"},{"2","1","5"},
	{"a","2","4"}}) << endl;
}