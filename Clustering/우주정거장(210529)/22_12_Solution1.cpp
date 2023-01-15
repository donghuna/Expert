/*
39_우주정거장_user_ver01

1. 문제 요약
    (x, y, z)(0~65535의 3차원)좌표10만개의 행성이 주어짐.
    이중 3곳을 정거장으로 하고
    각 행성을 3정거장 중 최소 유클리드 거리가 되는 곳에 배정할 때
    행성별 배정된 정거장까지 거리의 합을 가능한최소로 하는 정거장 3곳을 선택하는 문제

2. 문제 분석
    1) NP 문제, 전탐색 O(100000_C_3 * 100000 * 3) 시간복잡도.
    2) 데이터 분석:
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
    (2) A그룹에서는 { 1.215, 1.215, 1.215 } 에 가장 가까운 점(여러가지 해보다 보니 가장 좋은 초기값)을
        ret[0]에 구한다. { 1.215, 1.215, 1.215 }는 실험적으로 가장 좋은 pivot중에 하나이다.
    (3) B그룹의 수는 약 60여개 이므로 모든 가능한 경우를 생각하여 두 점을 구하고
        tmp[1], tmp[2]에 저장한다.
    (4) tmp[]를 이용하여 점수를 계산하고 가장 낮은 점수를 답으로 저장한다.
        이들을 답으로 하면 SCORE: 1442195.114439점이다.

    (5) 점수를 더 낮출수 있도록 다양한 시도를 해 볼 수 있다.
        예를 들면 {{ 1.215, 1.215, 1.215 } 에 가장 가까운 점 5개를 구하여 후보로 하고
        각각에 대하여 (3)(4)과정을 실행해 볼 수 있다.
*/
#define sq(n) ((n)*(n))
#define rint register int

const int LM = 100000;
const double INF = 9e12;
extern double mysqrt(double);

double(*p)[3], ans, zeroD[LM];
int A[LM], T[LM];

struct Point {
    double x, y, z;
    void init() { x = y = z = 0; }
    void init(double* pp) {
        x = pp[0], y = pp[1], z = pp[2];
    }
    double getD(double* pp) {
        return sq(x - pp[0]) + sq(y - pp[1]) + sq(z - pp[2]);
    }
}candi[3];

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
    for (i = 0; i < LM; ++i) {
        double dist, minDist = INF;
        for (j = 0; j < 3; ++j) {
            dist = candi[j].getD(p[i]);
            if (minDist > dist) minDist = dist;
        }
        // 거리의 합은 제곱근을 구하여 계산해야 한다.
        // 1 + 100 > 36 + 64 이지만 sqrt(1) + sqrt(100) < = sqrt(36) + sqrt(64) 이다.
        sc += mysqrt(minDist);
        if (sc > ans)
            return INF;
    }
    return sc;
}

void mergeSort(int* A, int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e) / 2;
    mergeSort(A, s, m);
    mergeSort(A, m, e);
    int i = s, j = m, k = s;
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
    candi[0] = { 1.215, 1.205, 1.209 };
    //candi[0] = { 1.215, 1.215, 1.215 };
    int pt = getNearest(candi[0]);               // 첫 번째 점번호 구하기
    candi[0] = { p[pt][0], p[pt][1], p[pt][2] };
    result[0] = pt;

    rint i, j;
    for (i = 0; i < LM; ++i) {
        A[i] = i;                                // 점번호를 저장
        zeroD[i] = sq(p[i][0]) + sq(p[i][1]) + sq(p[i][2]); // 원점으로부터 거리 구하기
    }

    mergeSort(A, 0, LM);  // zeroD[i]를 기준으로 점 번호를 내림차순 정렬


    // 원점으로부터 가장 거리가 먼 100개의 점 중에서 2점을 선택하기
    for (i = 0; i < 100; ++i) {
        candi[1] = { p[A[i]][0], p[A[i]][1], p[A[i]][2] };
        for (j = i + 1; j < 100; ++j) {
            candi[2] = { p[A[j]][0], p[A[j]][1], p[A[j]][2] };
            double sc = getScore();
            if (sc < ans) {
                ans = sc;
                result[1] = A[i], result[2] = A[j];
            }
        }
    }
}