#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS + 1] = {
	// the number of switches : 10
	// the number of clocks : 16
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};

bool areAligned(const vector<int>& clocks) {
	for (auto i : clocks) {
		if (i != 12)
			return false;
	}
	return true;
}

void push(vector<int> & clocks, int swtch) {
	for (int clock = 0; clock < CLOCKS; ++clock) {
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if (clocks[clock] == 15) clocks[clock] = 3;
		}
	}
}

int solve(vector<int> & clocks, int swtch) {
	if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
	int ret = INF;
	//스위치를 0번 누르는 경우부터 3번 누르는 경우까지 모두 시도
	//4번 누르면 어차피 원래대로 돌아오기 때문에 3번만 눌러도 됨
	for (int cnt = 0; cnt < 4; ++cnt) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}
	return ret;
}