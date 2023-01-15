/*
26_TS페어찾기_user_ver02
use quickSort + recur
* quick sort를 응용한 방법을 사용할 수 있다.
   이때, 구간을 잘 나누어야 한다.  아래 예를 보자.
index   0   1   2   3   4   5   6   7   8   9
number  3   3   1   1   2   2   4   4   5   5
*위 예의 경우 s = 0, e = 9 이므로 구간의 크기는 10이다.
  차 = 구간크기/2 = 10/2 = 5 이하와 초과로 나누면 구간이 나누어지지 않는다.
  차 = 구간크기/5 = 10/5 = 2 이하와 초과로 나누어도 구간이 나누어지지 않는다.

* 차 = 구간크기/6 = 10/6 = 1이하로 하면 (3 3 1 1 2 2 ) 과 (4 4 5 5 )로 나누어지는데
   이후 (3 3 1 1 2 2 ) 에서 다시 6/6=1 이하와 초과로 되어 나누어지지 않는다.
     따라서
   1) 구간크기 / 6미만과 이상으로 나누거나
   2) 구간크기 / 7이하와 초과로 나누는 방법을 사용할 수 있다.
      7대신 8, 9등을 선택할 수 있으나 성능이 떨어진다.

*/
extern bool checkCards(int indexA, int indexB, int diff);

int A[100000];
inline void swap(int& a, int& b) { int t = a; a = b; b = t; }
void qsort(int L, int H) {
    if (L + 1 >= H) checkCards(A[L], A[H], 0); // 2개만 남은 경우
    else {
        int i = L, j = L + 1, d = (H - L) / 6;//int i = L, j = L + 1, d = (H - L + 1) / 7;
        for (; j <= H; ++j) if (checkCards(A[j], A[L], d)) {
            swap(A[++i], A[j]);
        }
        if (d) qsort(L, i); // d가 0이라면 이미 찾은 경우이다.
        qsort(i + 1, H);
    }
}

void playGame(int N) {
    for (int i = 0; i < N + N; ++i) A[i] = i;
    qsort(0, N + N - 1);
}