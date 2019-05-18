#include <iostream>

using namespace std;

int numberOfStudent;
bool areFriend[10][10];

int getAns(bool taken[10]) {
	bool flag = true;
	for (int i = 0; i < numberOfStudent; ++i) {
		if (!taken[i]) {
			flag = false;
		}			
	}
	if (flag == true) return 1;

	int ret = 0;
	for (int i = 0; i < numberOfStudent; ++i) {
		for (int j = 0; j < numberOfStudent; ++j) {
			if (!taken[i] && !taken[j] && areFriend[i][j]) {
				taken[i] = taken[j] = true;
				ret += getAns(taken);
				taken[i] = taken[j] = false;
			}
		}
	}
	return ret;
}

int main() {
	int testCase;
	cin >> testCase;

	int numberOfPair;
	int studentA, studentB;
	auto temp = areFriend;
	while (testCase > 0) {
		bool taken[10] = { false };
		cin >> numberOfStudent >> numberOfPair;		
		for (int i = 0; i < numberOfPair; ++i) {
			cin >> studentA >> studentB;
			areFriend[studentA][studentB] = true;
		}

		cout << getAns(taken) << '\n';

		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				areFriend[i][j] = false;
			}
		}
		--testCase;		
	}
}