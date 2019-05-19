#include <iostream>

using namespace std;

int n;
bool areFriends[10][10];

int countPairings(bool taken[10]) {
	int firstFree = -1;
	for (int i = 0; i < n; ++i) {
		if (!taken[i]) {
			//첫번째로 짝 안지어진 학생 찾음
			firstFree = i;
			break;
		}
	}
	//모든 학생이 짝이 있으면 return 1
	if (firstFree == -1) return 1;

	int ret = 0;
	//짝이 안지어진 학생부터 loop 시작
	for (int pairWith = firstFree + 1; pairWith < n; ++pairWith) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			//set free for next loop and recursion
			taken[firstFree] = taken[pairWith] = false;
		}
	}
	return ret;
}