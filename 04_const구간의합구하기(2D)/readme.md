# const 구간의 합 구하기(2D)

---

URL : http://codepass.co.kr/bbs/bbs_solve_lecture.php?idx=135&prod_idx=2418&pCode=lecture&seq=4&page=1

---

값이 들어있는 배열이 1000 x 1000이 있고,
좌표 두개를 제시하고, 그 범위에 해당되는 값의 합을 구하는 문제.

---
prefix sum 을 하여, 누적값을 더한다.

1차원이라고 생각해보자,
이렇게 하면 0~1, 0~2, 0~3,... 0~N가지의 합을 구할 수 있다.

그래서 예를들어 3~N까지의 합을 구하고자하면
0~N까지의 합 - 0~2까지의 합 을하면 구할수 있다.

----

2차원은 알다시피 자신의 위와 왼쪽셀 더한다음에 대각선 왼쪽을 빼면서 누적시키면 된다.

----

Pre process : 
S[i][j] = S[i][j-1] + S[i-1][j] - S[i-1][j-1] + A[i][j]

sr, er, sc, ec

S[er][ec] - S[sr - 1][ec] - S[er][sc - 1] + S[sr - 1][sc - 1]


O(N*N+Q)
 
- N * N 만큼 계산하고 Query값만큼 계산이 추가된다.

---
