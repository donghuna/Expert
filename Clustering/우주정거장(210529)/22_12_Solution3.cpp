/*
35_우주정거장_user_ver03
*/
#define sq(n) ((n)*(n))
#define rint register int

const int LM = 100000;
const double INF = 9e12;
extern double mysqrt(double);

double ans;

struct Point {
    int id;
    double x, y, z, dist;
    void init() { x = y = z = 0; }
    void init(int nid, double* pp) {
        id = nid, x = pp[0], y = pp[1], z = pp[2];
        dist = x * x + y * y + z * z;
    }
    double getD(Point& t) {
        return sq(x - t.x) + sq(y - t.y) + sq(z - t.z);
    }
    bool operator<(const Point& t)const { return dist >= t.dist; }  // 내림차순으로 정읜
}candi[3], A[LM], T[LM], pivot;

void mergeSort(Point* arr, int s, int e) {
    if (s + 1 >= e) return;
    rint m = (s + e) / 2, i = s, j = m, k = s;
    mergeSort(arr, s, m), mergeSort(arr, m, e);
    while (i < m && j < e) {
        if (arr[i] < arr[j]) T[k++] = arr[i++];
        else T[k++] = arr[j++];
    }
    while (i < m) T[k++] = arr[i++];
    while (j < e) T[k++] = arr[j++];
    for (i = s; i < e; ++i) arr[i] = T[i];
}

double getDist() {
    double distSum = 0;
    for (rint i = 0; i < LM; ++i) {  // 10만
        double dist = candi[0].getD(A[i]);
        for (rint j = 1; j < 3; ++j) {
            double td = candi[j].getD(A[i]);
            if (dist > td) dist = td;
        }
        distSum += mysqrt(dist);
        if (distSum > ans) return ans;  // prunning
    }
    return distSum;
}

void getStation(double coordi[100000][3], int result[3])
{
    for (rint i = 0; i < LM; ++i) A[i].init(i, coordi[i]);
    mergeSort(A, 0, LM);  // 내림차순 정렬

    // result[0] 정하기
    pivot = { 0, 1.2149, 1.2055, 1.2095 };
    candi[0] = A[0];
    double retDist = candi[0].getD(pivot), tmpDist;
    for (rint i = 1; i < LM; ++i) {
        tmpDist = A[i].getD(pivot);
        if (retDist > tmpDist) {
            retDist = tmpDist;
            candi[0] = A[i];
        }
    }

    result[0] = candi[0].id;
    // result[1], result[2] 정하기
    ans = INF;
    for (rint i = 0; i < 99; ++i) { // 100 * 100 / 2 * 100000 = 약 5억
        candi[1] = A[i];
        for (rint j = i + 1; j < 100; ++j) {
            candi[2] = A[j];
            retDist = getDist();
            if (ans > retDist) {
                ans = retDist;
                result[1] = candi[1].id;
                result[2] = candi[2].id;
            }
        }
    }
}