#include <iostream>
#include <vector>

//default value of global variable is 0
int n;
bool areFriend[10][10];

//이 코드는 중복으로 여러번 세고 있음
int countPairings(bool taken[10]) {
	bool finished = true;
	for (int i = 0; i < n; ++i) {
		//짝이 안지어진 학생이 있으면 finished = false
		if (!taken[i])
			finished = false;
	}
	//모든 학생이 짝이 지어졌으면 return 1
	if (finished) return 1;
	int ret = 0;

	for (int i = 0; i < n; ++i) 
		for (int j = 0; j < n; ++j) 
			if (!taken[i] && !taken[j] && areFriend[i][j]) {
				taken[i] = taken[j] = true;
				//재귀 함수 사용
				ret += countPairings(taken);
				taken[i] = taken[j] = false;
			}	
	return ret;
}