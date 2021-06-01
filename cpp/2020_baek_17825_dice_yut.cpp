//���� �ֻ��� ������
//Ǯ�̽ð�: 2�ð� 55��
//
//����
//size(r1)�� �ȵǼ� ���� ���� ����, ���Ϳ����� �ɵ�.
//���ڰ� 40�� �κп� ���� ��ĥ �� �ִ� ���� ������
//��� 4�� ��쿡 30�� �ι� �� if�� ������ �߰� �ۼ���
//dfs() �Ŀ� �ٽ� idx�� route�� ���ڸ��� �������� ���� ������
//�ҽ� �ڵ尡 �����ؼ� �а�, ������ ������ϱ⿡ ������ ��������
//
//ä�� ��ȣ	���̵�	���� ��ȣ	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//23173657	nh9k	17825	�¾ҽ��ϴ�!!1984	20	C++14 / ����	5100

#include <iostream>
using namespace std;

int r1[] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
int r2[] = { 10,13,16,19,25,30,35,40 };
int r3[] = { 20,22,24,25,30,35,40};
int r4[] = { 30,28,27,26,25,30,35,40 };

int dice[10];
int max_value = 0;
struct horse {
	int idx;
	int route; //5 == end
}h[4];

bool is_arrive(int hi) {
	if (h[hi].route == 1) {
		if (h[hi].idx >= 21) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 2) {
		if (h[hi].idx >= 8) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 3) {
		if (h[hi].idx >= 7) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 4) {
		if (h[hi].idx >= 8) {
			h[hi].route = 5;
			return true;
		}
	}
	else {
		return true;
	}
	return false;
}

bool is_other(int hinput) {
	if (is_arrive(hinput)) return false;

	for (int hi = 0; hi < 4; ++hi) {
		if (hinput == hi) continue; //�ٸ� ���� ��
		if (h[hi].route == 5) continue; //�̹� ������ ���� �� x

		if (h[hinput].route == h[hi].route) { //��Ʈ�� ���� ���
			if (h[hinput].idx == h[hi].idx) //��ġ�� ������
				return true;
		}
		else { //��Ʈ�� �ٸ� ���
			if (h[hinput].route == 1) { //��Ʈ 1
				if ((h[hi].route == 2) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 10))
					return true;
				if ((h[hi].route == 3) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 20))
					return true;
				if ((h[hi].route == 4) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 30))
					return true;

				if ((h[hi].route == 2) && (r2[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
			}
			else if (h[hinput].route == 2) { //��Ʈ 2
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 10)) //��Ʈ1
					return true;
				if ((r2[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //��Ʈ1
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == r2[h[hinput].idx])) //��Ʈ3
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == r2[h[hinput].idx]) && (h[hi].idx !=0)) //��Ʈ4
					return true;
			}
			else if (h[hinput].route == 3) { //��Ʈ 3
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 20))
					return true;
				if ((r3[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //��Ʈ1
					return true;
				if ((h[hi].route == 2) && (r2[h[hi].idx] == r3[h[hinput].idx]))
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == r3[h[hinput].idx]) && (h[hi].idx != 0))
					return true;
			}			
			else if (h[hinput].route == 4) { //��Ʈ 4
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 30))
					return true;
				if ((r4[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //��Ʈ1
					return true;
				if ((h[hi].route == 2) && (r2[h[hi].idx] == r4[h[hinput].idx]) && (h[hinput].idx != 0))
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == r4[h[hinput].idx]) && (h[hinput].idx != 0))
					return true;
			}
		}
	}
	return false;
}

void dfs(int sum, int cnt) {
	if (cnt >= 10) {
		if (sum > max_value)
			max_value = sum;
		//cout << "sum: " << sum << endl;
		return;
	}

	for (int hi = 0; hi < 4; ++hi) {
		int memidx = h[hi].idx;
		int memroute = h[hi].route;

		if (h[hi].route == 1) {

			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				int origin = r1[h[hi].idx];
				if (r1[h[hi].idx] == 10) {
					h[hi].route = 2;
					h[hi].idx = 0;
				}
				else if (r1[h[hi].idx] == 20) {
					h[hi].route = 3;
					h[hi].idx = 0;
				}
				else if (r1[h[hi].idx] == 30) {
					h[hi].route = 4;
					h[hi].idx = 0;
				}
				dfs(sum + origin, cnt + 1);
			}
			else
				dfs(sum, cnt + 1);
		}		
		else if (h[hi].route == 2) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}		
			else if (!is_arrive(hi)) {
				dfs(sum + r2[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}			
		}		
		else if (h[hi].route == 3) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				dfs(sum + r3[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}
		}		
		else if (h[hi].route == 4) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				dfs(sum + r4[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}
		}
		h[hi].idx = memidx;
		h[hi].route = memroute;
	}
}



int main(){
	//�Է�
	for (int i = 0; i < 10; ++i) {
		cin >> dice[i];
	}

	//�˰���
	for (int hi = 0; hi < 4; ++hi) {
		h[hi].route = 1;
		h[hi].idx = 0;
	}
	dfs(0,0);

	//���
	cout << max_value;
	return 0;
}