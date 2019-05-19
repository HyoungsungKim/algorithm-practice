#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 987654321;
const int MAX = 1000;
int numberOfCity;
double dist[MAX][MAX];

double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
	if (path.size() == numberOfCity)
		return currentLength + dist[path[0]][path.back()];
	double ret = INF;
	for (int next = 0; next < numberOfCity; ++next) {
		if (visited[next]) continue;
		int here = path.back();
		path.push_back(next);
		visited[next] = true;
		double cand = shortestPath(path, visited, currentLength + dist[here][next]);

		ret = min(ret, cand);
		visited[next] = false;
		path.pop_back();
	}
	return ret;
}