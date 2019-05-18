#include <iostream>
#include <vector>

//default value of global variable is 0
int n;
bool areFriend[10][10];

//�� �ڵ�� �ߺ����� ������ ���� ����
int countPairings(bool taken[10]) {
	bool finished = true;
	for (int i = 0; i < n; ++i) {
		//¦�� �������� �л��� ������ finished = false
		if (!taken[i])
			finished = false;
	}
	//��� �л��� ¦�� ���������� return 1
	if (finished) return 1;
	int ret = 0;

	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) 
			if (!taken[i] && !taken[j] && areFriend[i][j]) {
				taken[i] = taken[j] = true;
				//��� �Լ� ���
				ret += countPairings(taken);
				taken[i] = taken[j] = false;
			}	
	return ret;
}