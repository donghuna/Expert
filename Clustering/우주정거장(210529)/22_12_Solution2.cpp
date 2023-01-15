/*
39_우주정거장_user ver02
* 10만개의 점 coordi[i]중에서 candi[0]보다 더 가까운 점이
  farthest[100] 중에 있는 경우 이 점을 B[]에 따로 모은다.(seed는 5일때 185개이다.)
* farthest[100]중에 2점을 선택한 것이 candi[1], candi[2]라고 할 때,
  B[]만을 대상으로 점검하는 전략을 사용하면 실행시간을 많이 줄일 수 있다.

1. 문제 요약
    (x, y, z)(0~65535의 3차원)좌표10만개의 행성이 주어짐.
    이중 3곳을 정거장으로 하고
    각 행성을 3정거장 중 최소 유클리드 거리가 되는 곳에 배정할 때
    행성별 배정된 정거장까지 거리의 합을 가능한최소로 하는 정거장 3곳을 선택하는 문제

2. 문제 분석
    1) NP 문제, 전탐색 O(100000_C_3 * 100000 * 3) 시간복잡도.
    2) 데이터 분석 :
    각 좌표의 데이터 생성 규칙이 random() / (random() + 1)이다.
    원점으로부터의 거리별 개수를 세면 아래와 같다.
         6미만의 개수 : 75241
        30미만의 개수 : 19678
       300미만의 개수 : 4551
      3000미만의 개수 : 467
     30000미만의 개수 : 59
    113511미만의 개수 : 4

3. solution sketch
    (1) 위 데이터 분석에 따라
    원점으로부터 거리 3000 미만인 A그룹과 3000이상인 B그룹으로 나누어
    A그룹에서 1개의 정거장을 B그룹에서 2개의 정거장을 선택한다.
    (2) A그룹 pivot으로 {
        1.214, 1.205, 1.209
    }; 원점으로부터 거리 6이하인 점들의 평균을 이용할 수 있다.
    또다른 A그룹 pivot으로는{ 1.215, 1.215, 1.215 }을 사용할 수 있는데 실험적으로 가장 좋은 pivot중에 하나이다.
    pivot 에 가장 가까운 점을 ret[0]에 구한다.

    (3) B그룹의 수는 약 60여개 이므로 모든 가능한 경우를 생각하여 두 점을 구하고
    tmp[1], tmp[2]에 저장한다.
    (4) tmp[]를 이용하여 점수를 계산하고 가장 낮은 점수를 답으로 저장한다.
    이들을 답으로 하면 SCORE : 1442195.114439점이다.

    (5) 점수를 더 낮출수 있도록 다양한 시도를 해 볼 수 있다.
    예를 들면{ { 1.215, 1.215, 1.215 } 에 가장 가까운 점 5개를 구하여 후보로 하고
    각각에 대하여(3)(4)과정을 실행해 볼 수 있다.
*/

#define sq(n) ((n)*(n))
#define rint register int

const int LM = 100000;
const double INF = 9e15;
extern double mysqrt(double);

double(*p)[3], ans, zeroD[LM];
int A[LM], T[LM], B[LM], bn;

struct Point {
    double x, y, z;
    void init() { x = y = z = 0; }
    void init(double* pp) {
        x = pp[0], y = pp[1], z = pp[2];
    }
    double getD(double* pp) {
        return sq(x - pp[0]) + sq(y - pp[1]) + sq(z - pp[2]);
    }
}candi[3], farthest[501];

int getNearest(Point& pt) {
    rint i, k = 0;
    double dist, minDist = INF;
    for (i = 0; i < LM; ++i) {
        dist = pt.getD(p[i]);
        if (minDist > dist) minDist = dist, k = i;
    }
    return k;
}

double getScore() {
    double sc = 0.0;
    rint i, j;
    for (i = 0; i < bn; ++i) {
        double dist, minDist = INF;
        for (j = 0; j < 3; ++j) {
            dist = candi[j].getD(p[B[i]]);
            if (minDist > dist) minDist = dist;
        }
        sc += mysqrt(minDist);
        if (sc > ans)
            return INF;
    }
    return sc;
}

void mergeSort(int* A, int s, int e) { // d
    if (s + 1 >= e) return;
    int m = (s + e) / 2;
    mergeSort(A, s, m);
    mergeSort(A, m, e);
    rint i = s, j = m, k = s;
    while (i < m || j < e) {
        if (i >= m) T[k++] = A[j++];
        else if (j >= e) T[k++] = A[i++];
        else if (zeroD[A[i]] >= zeroD[A[j]]) T[k++] = A[i++];
        else T[k++] = A[j++];
    }
    for (i = s; i < e; ++i) A[i] = T[i];
}

void getStation(double coordi[100000][3], int result[3])
{
    ans = INF;
    p = coordi;
    candi[0] = { 1.214, 1.205, 1.209 }; // 원점으로부터 거리가 6미만인 점들의 평균으로 구해진 좌표
    //candi[0] = { 1.215, 1.215, 1.215 }; // 직감과 실험으로 얻은 좌표
    int pt = getNearest(candi[0]);
    candi[0] = { p[pt][0], p[pt][1], p[pt][2] };
    result[0] = pt;
    B[0] = pt;

    rint i, j;
    for (i = 0; i < LM; ++i) {
        A[i] = i;
        zeroD[i] = sq(p[i][0]) + sq(p[i][1]) + sq(p[i][2]);
    }

    mergeSort(A, 0, LM);

    // 원점으로부터 가장먼 100개의 점을 farthest에 저장
    for (i = 0; i < 100; ++i) farthest[i].init(p[A[i]]);

    // 가장먼 100개의 점에 영향을 받을 가능성이 있는 점을 B[]에 저장
    // O(100,000 * 100)
    for (i = 0; i < LM; ++i) {
        double ad = candi[0].getD(p[i]);        // candi[0]과의 거리구하기
        for (j = 0; j < 100; ++j) {
            double bd = farthest[j].getD(p[i]); // farthest[j]와의 거리 구하기
            if (ad > bd) {                      // farthest[j]에 영향을 받는 경우
                B[++bn] = i;                    // B[]에 저장
                break;
            }
        }
    }

    for (i = 0; i < 100; ++i) {
        candi[1] = { p[A[i]][0], p[A[i]][1], p[A[i]][2] };
        for (j = i + 1; j < 100; ++j) {
            candi[2] = { p[A[j]][0], p[A[j]][1], p[A[j]][2] };
            double sc = getScore();             // B[]만을 대상으로 검토하기
            if (sc < ans) {
                ans = sc;
                result[1] = A[i];
                result[2] = A[j];
            }
        }
    }
}