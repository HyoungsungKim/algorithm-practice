# 알고리즘의 정당성 증명

## 5.1 도입

### 알고리즘의 정당성 증명

해결해야 할 문제가 간단할 때는 직관적으로 알고리즘을 설계할 수 있지만, 문제가 복잡해지면 이 알고리즘이 과연 문제를 제대로 해결하는지를 파악하기 까다로움.

알고리즘의 증명을 공부해야 하는 가장 큰 이유는 많은 경우 증명이 알고리즘을 유도하는 데 겨정적인 통찰을 담고 있기 때문.

## 5.2 수학적 귀납법과 반복문 불변식

수학적 귀납법

- 첫 번째 도미노는 직접 손으로 밀어서 쓰러뜨린다.
- 한 도미노가 쓰러지면 다음 도미노 역시 바로 쓰러진다.

***수학적 귀납법은 이와 같이 반복적인 구조를 갖는 명제들을 증명하는 데 유용하게 사용***

수학적 귀납법은 크게 세 단계로 나뉨

1. 단계 나누기
2. 첫 단계 증명
3. 귀납 증명

### 반복문 불변식

귀납법은 알고리즘의 정당성을 증명 할 때 가장 유용하게 사용되는 기법임. 

-> 대부분의 알고리즘은 어떠한 형태로든 반복적인 요소를 가지고 있기 때문.

귀납법을 이용해 알고리즘의 정당성을 증명 할 때는 반복문 불변식(loop invariant)라는 개념이 유용하게 사용 됨.

- 반복문 불변식이란 반목문의 내용이 한 번 실행될 때마다 중간 결과가 우리가 원하는 답으로 가는 길 위에 있는지를 명시한느 조건
- 반복문이 마지막에 정답을 계산하기 위해서는 항상 이 식이 변하지 않고 성립해야 함.

### 이진 탐색과 반복문 불변식

```C++
//Binary search
int binarySearch(const vector<int>& A, int x){
    int n = A.size();
    int lo = -1, hi = n;
    //반복문 불변식 1 : lo < hi
    //반복문 불변식 2 : A[lo] < x <= A[hi]
    
    while(lo + 1 <hi){ //반복문 불변식을 위한 조건1
        int mid = (lo + hi) / 2;	
        if(A[mid] < x)	//불변식 2를 위한 조건2
            lo = mid;
        elsr
            hi = mid;
    }
    return hi;
}
```

불변식을 이용해 반복문의 정당성을 증명하는 과정은 귀납법과 다를 것이 없음.

까다로운 코드를 짤 때 해당 코드가 가져야 할 불변식을 파악하고 작성하면 좀 더 오류가 적은 코드를 작성 하 수 있음.

### 삽입정렬과 반복문 불변식

```C++
void insertionSort(vecotr<int>& A){
    for(int i = 0; i < A.size(); ++i){
        //불변식 : A[0,1,2,...,i-1]은 이미 정렬 되어 있음
        //A[0,1,2,...i-1]에 A[i]를 끼워넣는다
        int j = i;
        while(j > 0 && A[j - 1] > A[j]){
            swap(A[j-1],A[j]);
            --j
        }
    }
}
```
