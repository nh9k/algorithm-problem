#include <string>
#include <vector>
//#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

typedef struct {
	vector <string> links;//�ܺ� url
	int my_idx = 22;
	float point[3] = { 0, 0, 0 }; //�⺻ ����, �ܺθ�ũ��, ��Ī ����
}page;

bool cmp(pair<float, int> &a, pair<float, int> &b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;
}

int solution(string word, vector<string> pages) {

	//***** ���� url, Ÿ url, word ���� �ľ��ϱ�
	map <string, page> url;
	int myurl[2], yours[2];
	int idx = 0;
	for (int i = 0; i < pages.size(); i++)
	{
		//*�� url
		myurl[0] = pages[i].find("<meta property=");
		myurl[0] = pages[i].find("https://", myurl[0]);
		myurl[1] = pages[i].find('\"', myurl[0]);

		url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].my_idx = idx;
		idx++;
		//*�ٸ���� url
		yours[0] = pages[i].find("<body>", myurl[1]);
		while (pages[i].find("<a href", yours[0]) != string::npos)
		{
			yours[0] = pages[i].find("<a href", yours[0]);
			yours[0] = pages[i].find("https://", yours[0]);
			yours[1] = pages[i].find('\"', yours[0]);

			//string temp = pages[i].substr(yours[0], yours[1] - yours[0]);
			url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].links.push_back(pages[i].substr(yours[0], yours[1] - yours[0]));
			//cout << url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[1] << endl;
		}//cout << endl;

		//*word ��
		yours[0] = pages[i].find("<body>", myurl[1]);
		yours[1] = pages[i].find("</body>", yours[0]);
		string word_list = pages[i].substr(yours[0] + 6, yours[1] - (yours[0] + 7) + 1); //�Ϻη� �յڷ� ��ĭ ���ؼ� word�� ������ ĭ ���� �˻� �����ϵ���
		//transform(word_list.begin(), word_list.end(), word_list.begin(), toupper);
		//transform(word.begin(), word.end(), word.begin(), toupper);
		for (int i = 0; i < word_list.length(); i++)
		{
			if (word_list[i] >= 'a' && word_list[i] <= 'z')
				word_list[i] = word_list[i] - 'a' + 'A';
		}
		for (int i = 0; i < word.length(); i++)
		{
			if (word[i] >= 'a' && word[i] <= 'z')
				word[i] = word[i] - 'a' + 'A';
		}

		yours[0] = word_list.find(word);
		yours[0] -= 1;
		while (word_list.find(word, yours[0] + 1) != string::npos)
		{
			yours[0] = word_list.find(word, yours[0] + 1);
			string temp = word_list.substr(yours[0] - 1, word.length() + 2);

			if (!((temp[0] >= 'A' && temp[0] <= 'Z') || (temp[word.length() + 1] >= 'A' && temp[word.length() + 1] <= 'Z')))
			{
				//cout << temp[0] << endl;
				//cout << temp[word.length() + 1] << endl;
				url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0]++;
				//cout << temp << endl;
				//cout << url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0] << endl;
			}
		}
		if (url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0]) //�ڽ��� ��ũ���� ���
			url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[1] = url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0]
			/ url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].links.size();

		//cout << url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[1] << endl;
	}

	//* �⺻ ���� + ��ũ ���� ���
	for (auto i = url.begin(); i != url.end(); i++)
	{
		int links_size = (*i).second.links.size();

		for (int j = 0; j < links_size; j++)
		{
			if (url[(*i).second.links[j]].my_idx != 22) //�ܺ� ��ũ�� �����ϸ�(�������� ������ idx == 22)
				url[(*i).second.links[j]].point[2] += (*i).second.point[1]; //�ܺ� url�� ��ũ ������ ������
		}
		(*i).second.point[2] += (*i).second.point[0]; //�⺻���� + ��ũ����
		//cout << (*i).second.point[2] << endl << endl;;
	}

	//* ���� �� ��� ����
	vector <pair<float, int>> result;
	for (auto i = url.begin(); i != url.end(); i++)
	{
		if ((*i).second.my_idx != 22) //�������� ������ idx == 22
		{
			result.push_back({ (*i).second.point[2], (*i).second.my_idx });
		}
	}

	sort(result.begin(), result.end(), cmp);
	return result.front().second;
}

int main()
{
	cout << solution("blind", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://a.com\"/>\n</head>  \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>",
		"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://b.com\"/>\n</head>  \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>",
		"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://c.com\"/>\n</head>  \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>" }) << endl;

	cout << solution("Muzi", { "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head>  \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>",
		"<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n  <meta charset=\"utf-8\">\n  <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head>  \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>" });

	return 0;
}


//strtok
// https://dojang.io/mod/page/view.php?id=376
// find
// https://modoocode.com/241
//https://blankspace-dev.tistory.com/314
// https://blockdmask.tistory.com/338
// toupper of string
// https://hashcode.co.kr/questions/596/string%ED%83%80%EC%9E%85-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%A0%84%EC%B2%B4%EB%A5%BC-%EB%8C%80%EB%AC%B8%EC%9E%90%EB%A1%9C-%EB%B0%94%EA%BE%B8%EB%8A%94-%EB%B0%A9%EB%B2%95


		//char pagecpy[1500]; //������ ��
		//strcpy(pagecpy, pages[i].c_str());

		//char *tok1 = strtok(pagecpy,  "content=\"https://"); //content=\"https:// �� �и�
		////tok1 = strtok(NULL, "https://");
		//htmlpage[i].me = strtok(NULL, "/>"); //�ڽ��� url \"/>
		//cout << "��url::  " << htmlpage[i].me << endl;

		//tok1 = strtok(NULL, "<body>");
		//tok1 = strtok(NULL, "</body>"); //�ܺ� url�� �ܾ� �˻��� ��
		//cout << "body::  " << tok1 << endl;

		//char *tok1in = strtok(tok1, "<a href=""https://");
		//int fsz = 0, firstidx = 0;
		//while (tok1in != NULL)
		//{
		//	string check(tok1in);
		//	transform(check.begin(), check.end(), check.begin(), toupper);
		//	while (1) //�ܾ� üũ
		//	{
		//		firstidx = check.find(word, firstidx);
		//		if (firstidx == string::npos)
		//			break;
		//		else {
		//			if(!(check[firstidx+word.size()] >= 'A' && check[firstidx + word.size()] <= 'Z'))
		//				htmlpage[i].point[0]++;
		//			cout << "ã�� �ܾ��::  " << htmlpage[i].point[0] << endl;
		//		}					
		//	}
		//	
		//	htmlpage[i].friends[fsz] = strtok(NULL, """>"); //�ܺ� url ����
		//	cout << "�ܺ�url::  " << htmlpage[i].friends[fsz] << endl;
		//	tok1in = strtok(NULL, "<a href=""https://");

		//	fsz++;
		//}
//
//
//			//* �߰� �߰� �ܾ split�ؼ� �ܾ �´��� �˻�
//string spliting = pages[i].substr(where1, yoururl[0] - where1);
//char split_c[1400];
//strcpy(split_c, spliting.c_str());
//char* test = strtok(split_c, " ");
//
//while (test != NULL)
//{
//	string test_s(test);
//	if (test_s.length() < word.length()) { //�˻��� ���� ª���� �ѱ��
//		test = strtok(NULL, " ");
//		continue;
//	}
//	else if (word.length() < test_s.length()) //�˻���� ��� Ȯ��
//	{
//		int mem = 0;
//		for (int k1 = 0; k1 < test_s.length(); k1++)
//		{
//			if (word[0] == test_s[k1])
//			{
//				mem = k1;
//
//				if (mem == 0)//word�� ù��° ���ں��� ���۵� ���
//				{
//					if (test_s[word.length()] >= 'a' || test_s[word.length()] <= 'z' ||
//						test_s[word.length()] >= 'A' || test_s[word.length()] <= 'Z')
//					{//�Ѿ
//						//test = strtok(NULL, " ");
//						continue;
//						//break;
//					}
//				}
//				else if (mem + word.length() <= test_s.length())//�׷��� ���� ���
//				{
//
//				}
//				else//ã�� �Ȱ��� ù��° ���ĺ����κ��� �ܾ��� ���̸� �������� ���� ª����
//				{
//					//break;
//					continue;
//				}
//			}
//		}
//
//	}
//	//���̰� ������
//	//test_s = test_s.substr(test_s.find(word), word.length());
//	//transform(test_s.begin(), test_s.end(), test_s.begin(), toupper);
//
//	if (!strnicmp(test, c_word, word.length())) //���� ���� �ܾ ã����
//		url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0]++; //�⺻ ���� ++
//	//if(!(test_s.compare(word)))
//
//	cout << pages[i].substr(myurl[0], myurl[1] - myurl[0]) << " : " << url[pages[i].substr(myurl[0], myurl[1] - myurl[0])].point[0] << endl;
//	test = strtok(NULL, " ");
//}