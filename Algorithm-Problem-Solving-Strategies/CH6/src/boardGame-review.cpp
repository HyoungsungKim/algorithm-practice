#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int blockType[4][3][2]{
	//(y, x)
	{ {0,0}, {0,1}, {1, 0} },
	{ {0,0}, {0,1}, {1,1} },
	{ {0,0}, {1,0}, {1,1} },
	{ {0,0}, {1,0}, {1,-1} }
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; ++i) {
		const int dy = y + blockType[type][i][0];
		const int dx = x + blockType[type][i][1];
		if (dy < 0 || dy >= board.size() || dx < 0 || dx >= board[0].size()) {
			ok = false;
		}
		else if ((board[dy][dx] += delta) > 1) {
			ok = false;
		}
	}

	return ok;
}

int putBlock(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); ++i) {
		for (int j = 0; j < board[i].size(); ++j) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) break;
	}
	if (y == -1) return 1;
	int ret = 0;
	for(int type = 0; type < 4; ++type){
		if (set(board, y, x, type, 1))
			ret += putBlock(board);
		set(board, y, x, type, -1);
	}
	
	return ret;
}
int main() {
	int testCase;
	cin >> testCase;
	while (testCase > 0) {
		int row, col;
		cin >> row >> col;
		vector<vector<int>> board(row, vector<int>(col, 0));

		for (int i = 0; i < row; ++i) {
			string boardElement;
			cin >> boardElement;
			for (int j = 0; j < col; ++j) {				
				if (boardElement[j] == '#') {
					board[i][j] = 1;
				}				
			}
		}
		cout << putBlock(board) << '\n';
		--testCase;
	}
}