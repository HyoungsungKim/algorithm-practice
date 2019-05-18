#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int dx[8] = { -1, -1, -1, 1, 1, 1, 0 ,0 };
const int dy[8] = { -1, 0, 1, -1, 0, 1, -1 ,1 };

/*
	(y, x) =
	1 : (-1, -1), 2 : (0, -1), 3 : (1, -1), 
	4 : (-1, 1), 5 : (0, 1), 6 : (1, 1),
	7 : (-1, 0), 8:(1, 0)	
	1 7 4
	2   5
	3 8 6
*/
vector<string> board;
bool inRange(int y, int x);
bool hashWord(int y, int x, const string& word) {
	if (!inRange(y, x)) return false;
	
	if (board[y][x] != word[0]) return false;
	
	if (word.size() == 1) return true;

	for (int direction = 0; direction < 8; ++direction) {
		int nextY = y + dy[direction], nextX = x + dx[direction];
		if(hashWord(nextY, nextX, word.substr(1)))
			return true;
	}
	return false;
}