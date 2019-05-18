#include <iostream>

using namespace std;

int numberOfStudent;
bool areFriend[10][10];

int countPairing(bool done[10]) {
	int firstFree = -1;
	for (int i = 0; i < numberOfStudent; ++i) {
		if(!done[i]){
			firstFree = i;
			break;
		}
	}
	if (firstFree == -1) return 1;
	int ret = 0;
	for (int pairWith = firstFree + 1; pairWith < numberOfStudent; ++pairWith) {
		if (!done[pairWith] && areFriend[firstFree][pairWith]) {
			done[firstFree] = done[pairWith] = true;
			ret += countPairing(done);
			done[firstFree] = done[pairWith] = false;
		}
	}
	return ret;
}

int main() {
	int testCase, numberOfPair;
	cin >> testCase;
	while (testCase > 0) {
		cin >> numberOfStudent >> numberOfPair;
		bool done[10] = { false, };

		for (int i = 0; i < numberOfPair; ++i) {
			int studentA, studentB;
			cin >> studentA >> studentB;
			areFriend[studentA][studentB] = true;
		}

		cout << countPairing(done) << "\n";
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				areFriend[i][j] = false;
			}
		}
		--testCase;
	}
}