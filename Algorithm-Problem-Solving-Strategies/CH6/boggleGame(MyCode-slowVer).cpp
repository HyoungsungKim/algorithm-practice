#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> xAxisArg{ -1, 0, 1, -1, 0, 1, -1, 0, 1 };
vector<int> yAxisArg{ -1, -1, -1, 0, 0, 0, 1, 1, 1 };

bool flag;

void hasWord(int y, int x, string word, const vector<string>& board) {
	if (board.size() != 5 || board[0].size() != 5) {
		cout << "Wrong board size check it again" << '\n';
		exit(1);
	}

	if (flag == true)
		return;
	
	char targetChar = word[0];
	int rowSizeOfBoard = board.size();
	int colSizeOfBoard = board[0].size();

	for(int yIndex = 0; yIndex < rowSizeOfBoard; ++yIndex){
		for(int xIndex = 0; xIndex < colSizeOfBoard; ++xIndex){
			if (y + yIndex >= 5 || x + xIndex >= 5)
				continue;
			if(board[y + yIndex][x + xIndex] == targetChar){
				for (int i = 0; i < 9; ++i) {
					int nextY = y + yAxisArg[i];
					int nextX = x + xAxisArg[i];
					if (nextY >= rowSizeOfBoard || nextY < 0) {
						continue;
					}

					if (nextX >= colSizeOfBoard || nextX < 0) {
						continue;
					}

					if (word.size() == 1) {
						flag = true;
						return;
					}
					string cllippedWord = word.substr(1,word.size());
					hasWord(nextY, nextX, cllippedWord, board);
				}		
			}		
		}
	}
}

int main() {
	int testCase;
	cin >> testCase;
	for (int i = 0; i < testCase; ++i) {
		string rowOfBoard;
		vector<string> board;
		for (int j = 0; j < 5; ++j) {			
			cin >> rowOfBoard;
			board.push_back(rowOfBoard);
		}

		string target;
		vector<string> targetVec;
		int numOfTarget;
		cin >> numOfTarget;
		for (int j = 0; j < numOfTarget; ++j) {
			cin >> target;
			cout << target << " ";
			flag = false;
			hasWord(0, 0, target, board);
			if (flag == true)
				cout << "YES" << '\n';
			else
				cout << "NO" << '\n';
		}		
	}
}