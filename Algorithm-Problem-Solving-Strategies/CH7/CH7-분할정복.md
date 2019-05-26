# CH7 분할 정복

## 7.1 도입

분할 정복 패러다임을 차용한 알고리즘들은 주어진 문제를 둘 이상으 부분 문제로 나눈 뒤 각 문제에 대한 답을 재귀 호출을 이용해 계산하고, 각 부분 문제의 답으로부터 전체 문제의 답을 계산

- 재귀 : 항상 문제를 한 조각과 나머지로 쪼갬
- 분할 정복 : 항상 문제를 절반씩 쪼갬

분할정복의 구성 요소

- 문제를 더 작은 문제로 분할하는 과정(divide)
- 각 문제에 대해 구한 답을 원래 문제에 대한 답으로 병합하는 과정(merge)
- 더이상 답을 분할하지 않고 곧장 풀 수 있는 매우 작은 문제(base case)

### 예제: 수열의 빠른 합과 행렬의 빠른 제곱

분할 정복을 이용해 recursion보다 빠른 합 구현

```c++
int fastSum(int n) {
    if(n == 1) return 1;
    if(n % 2 == 1) return fastSum(n - 1) + n;
    return 2 * fastSum(n / 2) + (n / 2) * (n / 2)
}
```

### 시간 복잡도 분석

`fastSum() `이 수행하는데 걸리는 시간은 `recursiveSum()`이랑 다름. 종료하는데 걸리는 시간은 순전히 함수가 호출되는 횟수에 비레함.

- `recursiveSum()` n번 호출
- `fastSum()` 최소한 두번에 한번 꼴로 n이 절반으로 줄어듬

## 행렬의 거듭제곱

행렬의 곱셈은 `O(n^3)` 거듭제곱은 꽤 많은 시간이 걸림

분할정복을 이용 `A^m = A^m/2 + A^m/2`

```c++
class SquareMatrix;
SquareMatrix identity(int n);
SquareMatrix pow(const SquareMatrix& A, int m) {
    //기저사례 : A^0 = I
    if(m == 0) return identity(A.size());
    //m이 홀수 일때
    if(m % 2 > 0) return pow(A, m- 1) * A;
    //m이 짝수 일때
    SquareMatrix half = pow(A, m/2);
    //와... 기가 막히네;;;
    return half * half;
}
```

### 나누어 떨어지지 않을 때의 분할과 시간 복잡도

m이 홀수일때 `A^m = A * A^m-1`로 나누지 않고 절반에 가깝게 나누는게 좋지 않을까?

대부분의 분할 정복 알고리즘은 가능한 절반에 가깝게 문제를 나누고자 함. 하지만 이 문제에서 이 방식의 분할은 오히려 알고리즘을 더 느리게 만듬. 이런 식으로 문제를 나누면 `A^m`을 찾기 위해 게산해야 할 부분 문제의 수가 늘어나기 때문(중복으로 계산하는 부분이 생겨남) -> 동적 계획법이 고안된 계기

## 예제: 병합 정렬과 퀵 정렬

병합 정렬과 퀵 정렬. 이 두 알고리즘은 모두 분할 정복 패러다임을 기반으로 해서 만들어진 것들.

- 병합 정렬은 주어진 수열을 가운데에서 쪼개 비슷한 크기의 수열 두 개로 만든 뒤 이들을 재귀 호출을 이용해 각각 정렬 함. 그 후 정렬된 배열을 하나로 합침으로써 정렬된 전체 수열을 얻음.
- 퀵 정렬 알고리즘은 배열을 단순하게 가운데에서 쪼개는 대신, 병합 과정이 필요 없도록 한쪽의 배열에 있는 수 중 임의의 'pivot'을 지정한 후 기준보다 작거나 같은 숫자를 왼쪽, 더 큰 숫자를 오른쪽으로 보냄.

### 시간 복잡도 분석

병합 정렬 : `O(nlgn)`

퀵 정렬 : 퀵 정렬의 경우 대부분의 시간을 차지하는 것은 주어진 문제를 두 개의 부분 문제로 나누는 파티션 과정임. 파티션에는 주어진 수열의 길이에 비례하는 시간이 걸리므로, 사실 병합 정렬에서의 병합 과정과 다를 것이 없음. 

하지만 분할된 두 부분 문제가 비슷한 크기로 나눠진다는 보장을 할 수 없기 때문에 시간 복잡도 분석이 까다로움.

최악의 경우 `O(n^2)`  최선의 경우 : `O(nlgn)`  -> ***퀵 정렬에서는 정확히 절반으로 분할 되는 것이 좋음***

## 예제: 카라츠바의 빠른 곱셈 알고리즘

수백자리, 수만 자리는 되는 큰 수자들을 다룰 때 주로 사용 함.  일반적인 정수형 변수가 아닌 정수형 배열을 입력받는 점을 눈여겨 볼만 함. 이 배열들은 곱할 수의 각 자릿수를 맨 아래 자리부터 저장하고 있음.

```c++
//두 큰 수를 곱하는 O(n^2)시간 알고리즘
void normalize(vector<int>& num) {
    num.push_back(0);
    for(int i = 0; i < num.size(); ++i){
        if(num[i] < 0) {
            int borrow = abs(num[i] + 9) / 10;
            num[i + 1] -= borrow;
            num[i] += borrow * 10;
        }
        else {
            num[i + 1] += num[i] / 10;
            num[i] %= 10;
        }
    }
    while(num.size() > 1 && num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
    vector<int> c(a.size() + b.size() + 1, 0);
    for(int i = 0; i < a.size(); ++i)
        for(int j = 0; j < b.size(); ++j)
            c[i + j] += a[i] * b[j];
    normalize(c);
    return c;       
}
```

```c++
//카라츠바의 빠른 곱셈 알고리즘
void addTo(vector<int>& a, const vector<int>& b, int k);
void subFrom(vector<int>& a, const vector<int>& b);
//z2 = a1 * b1;
//z0 = a0 * b0;
//z1 = (a0 + a1) * (b0 + b1) - z0 - z2;
vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
    int an = a.size(), bn = b.size();
    if(an < bn) return karatsuba(b,a);
    if(an == 0 || bn == 0) return vector<int>();
    if(an <= 50) return multiply(a,b);
    int half = an / 2;
    vector<int> a0(a.begin(), a.begin() + half);
    vector<int> a1(a.begin() + half, a.end());
    
    //여기가 기가 막히네;;;
    vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
    vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());
    
    vector<int> z2 = karatsuba(a1, b1);
    vector<int> z0 = karatsuba(a0, b0);
    
    addTo(a0, a1, 0); addTo(b0, b1, 0);
    vector<int> z1 = karatsuba(a0, b0);
    subFrom(z1, z0);
    subFrom(z1, z2);
    
    vector<int> ret;
    addTo(ret, z0, 0);
    addTo(ret, z1, half);
    addTo(ret, z2, half + half);
    return ret;
}
```

원래 문제의 답을 병합해 내는 부분을 개선함으로써 알고리즘의 성능을 향상시킨 좋은 예입니다.

### 시간 복잡도 분석

카라츠바 알고리즘은 세 번 재귀 호출을 하기 때문에 재귀 호출을 한 번이나 두 번만 하던 지금까지의 예제와는 다르게 시간 복잡도를 분석해야 함.

단, 카라츠바 알고리즘의 구현은 단순한 `O(n^2)` 알고리즘보다 훨씬 복잡하기 때문에, 입력의 크기가 작을 경우 `O(n^2)` 알고리즘보다 느린 경우가 많음.

## 7.2 문제: 쿼드 트리 뒤집기