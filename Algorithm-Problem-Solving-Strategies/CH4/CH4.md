# CH4 알고리즘 시간 복잡도 분석

## 4.1 도입

좀 더 빠른 알고리즘을 만들기 위해 가장 먼저 해야 할 일은 바로 알고리즘의 속도를 어떻게 측정 할지를 정하는 것. 프로그램의 실행 시간은 알고리즘의 속도를 일반적으로 이야기하는 기준이 되기에는 부적합합니다. 

- 프로그램의 수행 시간은 사용 한 프로그래밍 언어, 하드웨어는 물론이고, 운영체제, 컴파일러까지 수많은 요소에 의해 바뀔 수 있기 때문.
- 프로그램의 실제 수행시간이 다양한 입력에 대한 실행 시간을 반영하지 못함

그렇다면 어떤 기준으로 측정해야 할까?

### 반복문이 지배한다

입력의 크기에 따라 수행 횟수가 정해지는 반복문이 있기 마련. 입력의 크기가 작을 때는 반복문외의 다른 부분들이 갖는 비중이 클 수 있지만, 입력의 크기가 커지면 컵질수록 반복문이 알고리즘의 수행 시간을 지배하게 됨.

- 따라서 대개 우리는 알고리즘의 수행 시간을 반복문이 수행되는 횟수로 측정

## 4.2  선형 시간 알고리즘

### 다어이트 현황 파악: 이동 평균 계산하기

이동 평균(Moving average)은 주식의 가격, 연간 국내 총생산, 여자친구의 몸무게 등 ***시간에 따라 변화하는 값들을 관찰 할 때 유용하게 사용 할 수 있는 통계적 기준*** 

- 중요한 아이디어는 중본되는 계산을 제거하는 것

- 입력의 크기에 대비해 걸리는 시간을 그래프로 그려보면 정확한 직선 -> 선형시간(Linear Time)



## 4.3 선형 이하 시간 알고리즘

### 성형 전 사진 찾기

어떤 문제건 입려된 자료를 모두 한 번 훑어보는데 입력의 크기에 비례하는 시간, 즉 선형 시간이 걸림.

- 선형 시간보다 빠르게 동작하는 알고리즘은 입렬된 자료를 다 보지 않음
- ***주어진 자료에 대해 우리가 미리 알고 있는 지식을 활용하면 가능*** 

Ex) 이진탐색(binary search)

### 이진 탐색

C++의 표준 라이브러리에는 이진 탐색 함수가 두개 존재

- 가장 이른 것을 반환하는 *lower_bounc()*
- 가장 뒤의 것을 반환하는 *upper_bound()*

## 4.4 지수 시간 알고리즘

### 다항 시간 알고리즘

반복문의 수행 횟수를 입력 크기의 다항식으로 표현할 수 있는 알고리즘들을 다항 시간 알고리즘이라고 부릅니다. 

#### 알러지가 심한 친구들

할 줄 아는 M가지 음식 중 무엇을 대접해야 할까를 고민하는데, 친구들은 각각 알러지 때문에 못 먹는 음식들이이어서 아무 음식이나 해서는 안됨. 주어진 목록이 있을때 한명당 최소 하나씩은 먹게 하려면 최소 몇가지의 음식을 해야할까?

```c++
const int INF = 987654321;
bool cnaEverybodyEat(const vector<int>& menu);
int M;
int selectMenu(vector<int>& menu, int food){
    //기저 사례: 모든 음식에 대해 만들지 여부를 결정 했을 때
    if(food == M){
        if(canEverybodEat(menu)) return menu.size();
        return INF;
    }
    int ret = selectMenu(menu, food + 1);
    menu.push_back(food);
    ret = min(ret, select(Menu(menu, food + 1)));
    menu.pop_back();
    return ret;
}
```



### 지수 시간 알고리즘

N이 증가 할 때마다 걸리는 시간이 배로 증가하는 알고리즘들을 지수시간(Exponential time)에 동작한다고 말함.



### 소인수 분해의 수행시간

입력으로 주어지는 숫자의 개수가 아니라 그 크기에 따라 수행 시간이 달라지는 알고지즘들 또한 지수 수행 시간을 가질 수 있습니다. 

```C++
//자연수 n의 소인수 분해 결과를 담은 정수 배열을 반환
vector<int> factor(int n){
    if(n == 1) return vetor<int>(1,1);
    vector<int> ret;
    for(int div = 2; n > 1; ++div)
        while(n % div == 0) {
            n /= div;
            ret.push_back(div);
        }
	return ret;         
}
```

소인수 분해 문제에서는 입력으로 주어지는 숫자가 알고리즘의 동작에 직접적인 영향을 미치므로, 숫자가 특정 범위 안에 있다고 가정 할 수없음. ***입력의 값이커지면 커질수록 숫자를 저장하는데 필요한 메모리의 공간도 증가함.*** 이때 입력이 차지하는 비트의 수에 따라 수행 시간이 증가한다고 생각하면 실행횟수와 수행횟수의 불일치 설명 가능.

- ***비트의 수가 하나 증가할 때마다 표현 할 수 있는 수의 범위와 알고리즘의 최대 수행 시간은 두 배로 증가.***
- 이렇게 입력의 크기를 입력이 차지하는 비트 수로 정의하면 위 코드는 입력의 크기에 대해 지수시간이 걸린다고 말할 수 있음.

## 4.5 시간 복잡도

시간 복잡도(time complexity)란 가장 널리 사용되는 알고리즘의 수행 시간 기준으로, 알고리즘이 실행되는 동안 수행하는 기본적인 연산의 수를 입력의 크기에 대한 함수로 표현한 것. 기본적인 연산이란 더 작게 쪼갤 수 없는 최소 크기의 연산.

앞 절들에서 우리는 가장 깊이 중첩된 반목문의 수행 횟수를 계산했음. 가장 깊이 중첩된 반복문의 내부에 있는 기본적 연산들은 더 쪼갤 수 없기 때문에, 이것이 시간 복잡도의 대략적인 기준이 됨.

- 시간 복잡도가 높다 -> 입력의 크기가 증가할 때 알고리즘의 수행 시간이 더 빠르게 증가함.
  ***->시간 복잡도가 낮다고 해서 언제나 더 빠르게 동작하는건 아님. 입력의 크기가 충분히 작을 때는 시간 복잡도가 높은 알고리즘이 더 빠르게 동작할 수도 있음***

Ex) A : 1024 + 35*log(N), B: 2*N*N

-> 입력의 크기가 작으면 B가 더 빠름

### 입력의 종류에 따른 수행 시간의 변화

입력의 크기가 수행 시간을 결정한는 유일한척도는 아님. ***입력이 어떤 형태로 구성되어 있는지도 수행 시간에 영향을 미침*** 

대개 사용하는 것은 최악의 수행 시간 혹은 수행 시간의 기대치.

### 점근적 시간 표기:O 표기

Big-O Notation을 이용해 알고리즘 수행 시간을 표기 함.

- 최고차항만 표기

#### O 표기법의 의미

O표기법은 대략적으로 함수의 상한을 나타낸다는데 그 의미가 있음.

### 시간 복잡도의 분할 상환 분석

알고리즘의 시간 복잡도를 항상 반복문의 개수를 세는 것으로만 결정하지는 않음. 가끔은 문제의 조건에 따라 그 보다 더 정확한 시간 복잡도를 계산 하는 것도 가능.

->시간 복잡도의 분할 상환 분석(Amortized analysis) 사용.

N개의 작은 작업들을 순서대로 하는데, 각 작업에 걸리는 시간은 모두 다르지만 전체 작업에 걸리는 시간이 일정한 경우 이런 방법을 사용 할 수 있음.

- 복잡해보이지만 종종 유용함.
- 분할 상환 분석을 이요하면 일반적으로는 시간이 오래 걸려 실행하지 못할 것이라고 여겼던 작업이 시간 안에 돌아가는 것을 이해 할 수 있게 됨.

## 4.6 수행 시간 어림짐작하기

### 주먹구구 법칙

프로그래밍 대회의 시간 제한은 알고리즘의 시간 복잡도가 아니라 프로그램의 수행 시간을 기준으로 함.

- 따라서 어떤 알고리즘이 이 문제를 해결할 수 있을지 알기 위해서는 프로그램을 작성하기 전에 ***입력의 최대 크기와 알고리즘의 시간 복잡도를 보고 수행 시간을 어림짐작 할 수 있어야 함.***

- 매우 어려운 일이지만 많은 경우에는 시간 복잡도와 입력 크기만 알고 있더라고 어떤 알고리즘이 시간 안에 동작 할지 대략적으로 짐작하는 것이 가능함.

***주먹구구 법칙***

- 입력의 크기를 시간 복잡도에 대입해서 얻은 반복문의 수행 횟수에 대해, 1초 당 반복문 수행 횟수가 1억을 넘어가면 시간 제한을 초과할 가능성이 있다.

### 주먹구구 법칙은 주먹구구일 뿐

고려해야 할 요소

- 시간 복잡도가 프로그램의 실제 수행 속도를 반영하지 못하는 경우
- 반목문 내부가 복잡한 경우:입출력, 실수연산 등
- 메모리 사용 패턴이 복잡한 경우: 현대의 cpu는 메모리에 있는 자료를 직접 접근하는 대신 캐시라고 부르는 작고 빠른 메모리로 옮겨온 뒤 처리함. 메모리에서 캐시로 자료를 가져올 때는 ***인접한 자료들을 함께 가져오기 때문에 인접한 자료들을 연속해서 사용하는 프로그램은 메모리에서 매번 자료를 자겨올 필요가 없음.***
  -> int 5개 보다 크기 5인 벡터나 배열이 더 빠르다는 뜻인가...?
- 언어와 컴파일러 차이
- 구형 컴퓨터를 사용하는 경우

### 실제 적용해 보기

1차원 배열에서 연속된 부분 구간 중 그 합이 최대인 구간을 찾는 문제

```c++
//O(N^3)
const int MIN = numeric_limits<int>::min();
int inefficientMaxSum(const vector<int>& A){
    int N = A.size(), ret = MIN;
    for(int i = 0; i < N; ++i)
        for(int j = i; j < N; ++j){
            int sum = 0;
            for(int k = i; k <= j; ++k)
                sum += A[k];
            ret = max(ret,sum);
        }
    return ret;
}
```

```c++
//O(N^2)
int betterMaxSum(const vector<int>& A){
    int N A.size(), ret = MIN;
    for(int i = 0; i < N; ++i){
        int sum = 0;
        for(int j = i; j < N; ++j){
            //for문 쓸 필요 없이 바로 sum에 합 한뒤 max 구함
            sum += A[j];
            ret = max(ret, sum);
        }
    }
    return ret;
}
```

```c++
//분할정복
//O(NlogN)
int fastMaxSum(const vector<int>& A, int lo, int hi){
    //기저 사례:구간의 길이가 1인 경우
    if(lo == hi) return A[lo];
    int mid = (lo + hi) / 2;
    int left = MIN, right = MIN, sum = 0;
    for(int i = mid; i >= lo; --i){
        sum += A[i];
        left = max(left,sum);
    }
    sum = 0;
    for(int j = mid + 1; j<= hi; ++j){
        sum += A[j];
        right = max(right, sum);
    }
    int single = max(fastMaxSum(A, lo, mid), fastMaxSum(A,mid + 1, hi));
    return max(left + right, single);
}
```

동적 계획법

A[i]를 오른쪽 끝으로 갖는 구간의 최대 합을 반환하는 함수 maxAt(i)를 정의. ***그런데 A[i]에 끝나는 최대 합 부분 구간은 항상 A[i] 하나만으로 구성되어 있거나, A[i-1]를 오른쪽 끝으로 갖는 최대 합 부분 구간의 오른쪽에 A[i]를 분힌 형태.***

```c++
//동적 계획법
//O(N)
int fastesrMaxSum(const vector<int>& A){
	int N = A.size(), ret = MIN, psum = 0;
    for(int i = 0; i < N; ++i){
        psum = max(psum, 0) + A[i];
        ret = max(psum, ret);
    }
    return ret;
}
```



## 4.7 계산 복잡도 클래스:P, NP,NP-완비

계산 복잡도 이론에서 문제의 난이도는 해당 문제를 해결하는 빠른 알고리즘이 있느냐를 나타냄. 빠른 알고리즘이 있는 문제는 계산적으로 쉽고, 빠른 알고리즘이 없는 문제는 계산적으로 어렵다고 말함.

- 보통 다항 시간 알고리즘이나 그보다 빠른 알고리즘들만을 빠르다고 말함.
- P문제 : 다항시간이 존재하는 알고리즘 문제

### 난이도의 함정

P가 다항 시간에 풀 수 있는 문제면, 그 짝인 NP는 당연히 풀 수 없는 문제여야 하는데 외 이렇게 비관적으로 만들었는가!

- 어떤 문제를 다항 시간에 풀 수 있음을 증명하기란 쉽지만, ***풀 수 없음을 보이기란 어려움.***

계산 복잡도 이론에서는 두 문제의 난이도를 비교하기 위해 환산(reduction)이라는 기법을 이용함. 환산이란 한 문제를 다른 문제로 바꿔서 푸는 기법.

### NP 문제, NP 난해 문제

어려운 문제의 기준이 되는 것이 바로 SAT문제(Satisfiability problem).

- SAT문제란 N개의 불린 값 변수로 구성된 논리식을 참으로 만드는 변수 값을의 조합을 찾는 문제.
- NP 문제 : 답이 주어졌을 때 이것이 정답인지를 다항 시간 내에 확인 할 수 있는 문제.
- SAT가 모든 NP문제 이상으로 어려움 -> SAT를 다항 시간에 풀 수 있으면 NP문제들을 전부 다항 시간에 풀 수 있다는 말.
- 이런 속성을 갖는 문제들의 집합을 NP-Hard(NP-문제)라고 부름.
- NP-난해 문제이면서 NP인 문제를 NP-complete(NP-완비)문제라고 함.
  -> 다항시간에 풀수 있는지는 알수 없지만 답을 알면 답 확인은 다항시간 안에 가능.

### P = NP?

NP-난해 문제 중 하나를 다항 시간에 풀 수 있다면, 이 알고리즘을 이용해 NP에 속한 모든 문제를 다항 시간에 풀 수 있음.
