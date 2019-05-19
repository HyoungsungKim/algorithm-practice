#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
//null 문자 때문에 CLOCKS + 1로 배열 크기 잡아야 됨
const char linked[SWITCHES][CLOCKS + 1] = {
	// the number of switches : 10 -> row
	// the number of clocks : 16 -> col
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
	for (int i = 0; i < CLOCKS; ++i) {
		if (linked[swtch][i] == 'x') {
			clocks[i] += 3;
		}
		if (clocks[i] == 15)
			clocks[i] = 3;
	}
}

int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES) return areAligned(clocks) ? 0 : INF;
	int ret = INF;
	for (int i = 0; i < 4; ++i) {
		ret = min(ret, i + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}
	return ret;
}

int main() {
	int testCase;
	cin >> testCase;
	while (testCase > 0) {
		vector<int> clocks;
		int time;
		for (int i = 0; i < CLOCKS; ++i) {
			cin >> time;
			clocks.push_back(time);
		}
		int ans = solve(clocks, 0);
		if (ans >= INF)
			cout << "-1" << '\n';
		else
			cout << ans << '\n';
		--testCase;
	}
}