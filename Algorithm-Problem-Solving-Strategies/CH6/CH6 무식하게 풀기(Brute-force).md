# CH6 무식하게 풀기(Brute-force)

## 6.1 도입

프로그래밍 대회에서 대부분의 사람들이 가장 많이 하는 실수는 쉬운 문제를 어렵게 푸는 것.

## 6.2 재귀 호출과 완전 탐색

### 재귀 호출

재귀 함수란 자신이 수행할 작업을 유사한 형태의 여러 조각으로 쪼갠 뒤 그 중 한 조각을 수행하고, 나머지를 자기 자신을 호출해 실행하는 함수

```c++
//Example
int sum(int n){
    int ret = 0;
    for(int i = 0; i <= n; ++i)
        ret += i;
    return ret;    
}

//My answer
int recursiveSum(int n) {
	if (n == 0) return 0;
	int val = n;
	val += recursiveSum(n - 1);
	return val;
}

//Answer of Book
int recursiveSum(int n){
    if(n == 1) return 1;
    return n + recursiveSum(n - 1);
}
```

***모든 재귀 함수는 이와 같이 '더 이상 쪼개지지 않는' 최소한의 작업에 도달 했을 때 답을 곧장 반환하는 조건문을 포함해야 함*** -> 기저 사례(Base Case)

문제의 특성에 따라 재귀 호출은 코딩을 훨씬 간편하게 해 줄 수 있는 무기가 됨.

#### 예제: 중첩 반복문 대체하기

```c++
for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j)
        for(int k = j + 1; k < n; ++k)
            for(int l = k + 1; l < n; ++l)
                cout << i << " " << j << " " << k << " " << l << endl;
```

Recursion

```c++
void pick(int n, vector<int>& picked, int toPick){
    if(toPick == 0) { 
        printPicked(picked);
        return;
    }
    int smallest = picked.empty() ? 0 : picked.back() + 1;
    for(int next = smallest; next < n; ++next){
        //Recursion in loop
        picked.push_back(next);
        pick(n, picked, toPick - 1);
        picked.pop_back();
    }
}
```

제귀 호출은 완전 탐색을 구현 할 때 아주 유용한 도구

#### 예제: 보글 게임

간단한 방법은 완전 탐색을 이용, 모든 칸 탐색

##### 문제의 분할

각 글자를 하나의 조각으로 만드는 것. 함수 호출시에 단어의 시작 위치를 정해 주기 때문에, 문제의 조각들 중 첫번째 글자에 해당하는 조각을 간단하게 해결할 수 있음.

##### 기저 사례의 선택

간결한 코드를 작성하는 유용한 팁

- 입력이 잘못되거나 범위에서 벗어난 경우도 기저 사례로 택해서 맨 처음에 처리하는 것.

##### 시간 복잡도 분석

완전 탐색 알고리즘이 모든 경우에 시간 안에 동작함을 홛인하기 위해서는 후보의 최대 수를 계산하면 됨.

최악의 경우는 답이 없을 경우...

이 소스코드에서 시간 복잡도는 O(8^N) -> 단어의 길이에 따라 지수적으로 증가 함.

#### 완전 탐색 레시피

1. 완전 탐색은 존재하는 모든 답을 하나씩 검사하므로, 걸리는 시간은 가능한 답의 수에 정확히 비례

-> 최대 크기의 입력에 대한 수행 시간 고려

2. 가능한 모든 답의 후보를 만드는 과정을 여러 개의 선택으로 나눔.
3.  그중 하나의 조각을 선택해 답의 일부를 만들고, 나머지 답을 재귀 호출을 통해 완성
4. 조각이 하나밖에 남지 않은 경우, 혹은 하나도 남지 않은 경우에는 답을 생성했으므로, 이것을 기저 사례로 선택.

#### 이론적 배경: 재귀 호출과 부분 문제

재귀 호출을 공부하면서 짚고 넘어가야 할 중요한 개념

- 문제(Problem)
- 부분 문제(Subproblem)

이 정의는 뒤에서 다룰 동적 계획법이나 분할 정복과 같은 중요한 디자닝 패러다임을 설명 하는데 사용됨. 쉽게 생각할 수 있는 직관과는 약간 차이가 있음.

Example

- 문제 : 주어진 자연수 수열을 정렬하라
- 문제 : {16, 7, 9, 1, 31}을 정렬하라

얼핏 보면 같은 문제라고 할 수 있지만 두 정의 사이에는 큰 차이가 있음.

-> 특정한 입력이 지정되어 있음.

***재귀 호출을 논의 할 때 '문제'란 항상 수행해야 할 작업과 그 작업을 적용 할 자료의 조합을 의미***

예를 들어 {1, 2, 3}을 정렬 하는 문제와 {3, 2, 1}을 정렬하는 문제는 다른 문제.

문제에서 한 조각을 떼어냈을때, 형식이 같은 또 다른 문제를 푼 결과가 존재 함. ***문제를 구성하는 조각들 중 하나를 뺐기 때문에, 이 문제들은 원래 문제의 일부라고 말할 수 있음.***

-> 이런 문제들을 원래 문제의 부분 문제라고 함.

## 6.3 문제:소풍

```c++
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
	//모든 학생이 짝이 지어졌으면 returnr 1
	if (finished) return 1;
	int ret = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (!taken[i] && !taken[j] && areFriend[i][j]) {
				taken[i] = taken[j] = true;
				//재귀 함수 사용
				ret += countPairings(taken);
				taken[i] = taken[j] = false;
			}
		}
	}
	return ret;
}
```

이 코드는 중복으로 여러번 세고 있음.

실질적으로 같은 답을 중복으로 세는 이런 상황은 경우의 수를 다룰 떄 굉장히 흔하게 마주치게 됨.

- 이를 해결하기 위한 좋은 방법은 항상 특정 형태를 갖는 답만을 세는 것.
- 흔히 사용하는 방법으로는 같은 답 중에서 ***사전순으로 가장 먼저 오는 답 하나만을 세는 것*** 
- 이 속성을 강제하기 위해서 각 단계에서 남아 있는 학생들 중 가장 번호가 빠른 학생의 짝을 찾아 주도록 함.

```C++
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
```

## 6.5 문제: 게임판 덮기

흰 칸의 수가 3의 배수가 아닐 경우에는 무조건 답이 없으니 이 부분을 따로 처리, 이 외의 경우에는 흰 칸의 수를 3으로 나눠서 내려놓을 블록의 수 N을 얻은뒤, 문제의 답을 생성하는 과정을 N조각으로 나눠 한 조각에서 한 블록을 내려놓으면 됨.

중복을 피하기 위해 특정한 순서대로 답을 생성하도록 강제할 필요가 있음.

***가장 간편한 방법은 재귀 호출의 각 단계마다 아직 빈 칸 중에서 가장 윗 줄, 그 중에서도 가장 왼쪽에 있는 칸을 덮더록 하는 것.*** 

우리는 항상 빈 칸중에서 가장 위, 그중에서도 가장 왼쪽에 있는 칸을 처음 채운다고 가정하기 때문에 그 왼쪽과 위에 있는 칸은 항상 채워져 있다고 가정 할 수 있음.

## 6.7 최적화 문제

지금까지 다뤘던 문제와는 달리 문제의 답이 하나가 아니라 여러 개 이고, 그 중에서 어떤 기준에 따라 가장 '좋은' 답을 찾아 내는 문제들을 통칭해 최적화 문제(Optimization problem)라고 부름.

- 동적 계획법
- 조화 탐색
- 최적화 문제를 결정 문제로 바꿔서 해결하는 기법

### 예제: 여행하는 외판원 문제(Traveling Salesman Problem:TSP)

```c++
int n;	//도시의 수
double dist[MAX][MAX]; //두 도시 간의 거리를 저장하는 배열
//path : 지금까지 만든 경로
//visited : 각 도시의 방문 여부
//currentLength : 지금까지 만든 경로의 길이

//나머지 도시들을 모두 방문하는 경로들 중 가장 짧은 것의 길이를 반환
double shortestPath(vector<int>& path, vector<bool>& visited, double currentLength) {
    //기저 사례 : 모든 도시를 다 방문했을 때는 시작 도시로 돌아가고 종료.
	if(path.size() == n) {
		return currentLength + dist[path[0]][path.back()];
	}
	double ret = INF;	//매우 큰 값으로 초기화 ex)987654321
    //다음 방문 할 도시를 전부 시도해 봄        
	for(int next = 0; next < n; ++next){
		if(visited[next]) continue;
        //path.back() : 가장 최근에 간 경로
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
```

## 6.8 문제:시계 맞추기

### 문제 변형하기

이 문제는 있는 그대로 풀려고 하면 꽤나 복잡해짐. 그러나 문제의 특성을 이용해 적절히 단순화하면 완전 탐색으로 해결 할 수 있음

- 스위치를 누르는 순서는 전혀 중요하지 않음.
- 따라서 계산해야 하는 것은 각 스위치를 몇 번이나 누를 것이냐 뿐
- 시계는 12시간이 지나면 제 자리로 돌아온다는 점을 이용하면 무한한 조합의 수을 유한하게 바꿀  수 있음. 어떤 스위치를 네 번 누르면 연결된 시계는 모두 12시간씩 앞으로 이동하니 하나도 누르지 않은 것과 다름이 없음.
- 따라서 어떤 스위치건 간에 최대 세 번 이상 누를 일이 없음.
- 따라서 각 스위치를 누르는 횟수는 0에서 3사이의 정수.

### 완전 탐색 구현하기

- 문제를 모두 열 조각으로 나눈 후 각 조각에서 한 스위치를 누를 횟수를 정하는 식으로 구현되어 있음.

## 6.10 많이 등장하는 완전 탐색 유형

- 모든 순열 만들기
- 모든 조합 만들기
- 2^n가지 경우의 수 만들기

