/*
24_����������_user
CKW's test

1. ���� ���
    (x, y, z)(0~65535�� 3����)��ǥ10������ �༺�� �־���.
    ���� 3���� ���������� �ϰ�
    �� �༺�� 3������ �� �ּ� ��Ŭ���� �Ÿ��� �Ǵ� ���� ������ ��
    �༺�� ������ ��������� �Ÿ��� ���� �������ּҷ� �ϴ� ������ 3���� �����ϴ� ����

2. ���� �м�
    1) NP ����, ��Ž�� O(100000_C_3 * 100000 * 3) �ð����⵵.
    2) ������ �м�:
    �� ��ǥ�� ������ ���� ��Ģ�� random() / (random() + 1)�̴�.
    �������κ����� �Ÿ��� ������ ���� �Ʒ��� ����.
         <4      <10    <100  <3000  <10000  <100000
         63458,  21561, 13378, 1513,  40,    23

3. solution sketch
    (1) �� ������ �м��� ����
        �������κ��� �Ÿ� 3000 �̸��� A�׷�� 3000�̻��� B�׷����� ������
        A�׷쿡�� 1���� �������� B�׷쿡�� 2���� �������� �����Ѵ�.
    (2) A�׷쿡���� { 1.215, 1.215, 1.215 } �� ���� ����� ��(�������� �غ��� ���� ���� ���� �ʱⰪ)��
        ret[0]�� ���Ѵ�. { 1.215, 1.215, 1.215 }�� ���������� ���� ���� pivot�߿� �ϳ��̴�.
    (3) B�׷��� ���� �� 60���� �̹Ƿ� ��� ������ ��츦 �����Ͽ� �� ���� ���ϰ�
        tmp[1], tmp[2]�� �����Ѵ�.
    (4) tmp[]�� �̿��Ͽ� ������ ����ϰ� ���� ���� ������ ������ �����Ѵ�.
        �̵��� ������ �ϸ� SCORE: 1442195.114439���̴�.

    (5) ������ �� ����� �ֵ��� �پ��� �õ��� �� �� �� �ִ�.
        ���� ��� {{ 1.215, 1.215, 1.215 } �� ���� ����� �� 5���� ���Ͽ� �ĺ��� �ϰ�
        ������ ���Ͽ� (3)(4)������ ������ �� �� �ִ�.
*/
#define sq(n) ((n)*(n))
#define rint register int

const int LM = 100000;
const double INF = 9e12;
extern double mysqrt(double);

double(*p)[3];     // coordi������ �����Ͽ� ���
double ans = INF;  // �ּҰŸ��� ��
double zeroD[LM];  // �� ���� �������κ��� �Ÿ�
int A[LM], T[LM];  // ������ index�� �����Ͽ� A[]�� ����

struct Point {
    double x, y, z;
    void init() { x = y = z = 0; }
    void init(double* pp) {
        x = pp[0], y = pp[1], z = pp[2];
    }
    double getD(double* pp) {
        return sq(x - pp[0]) + sq(y - pp[1]) + sq(z - pp[2]);
    }
}candi[3];  // ���� ����� �Ǵ� 3��

int getNearest(Point& pt) {  // ret[0]���ϱ�
    rint i, k = 0;
    double dist, minDist = INF;
    for (i = 0; i < LM; ++i) {
        dist = pt.getD(p[i]);
        if (minDist > dist) minDist = dist, k = i;
    }
    return k;
}

double getScore() {         // ���� candi[]�� ���� ����
    double sc = 0.0;        // ���� candi[]�� ���� �Ÿ��� ����
    rint i, j;
    for (i = 0; i < LM; ++i) {
        double dist, minDist = INF;
        for (j = 0; j < 3; ++j) {     // i�� ���� ���� ����� candi[j]���ϱ�
            dist = candi[j].getD(p[i]);
            if (minDist > dist) minDist = dist;
        }
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
    while (i < m || j < e) {  // �������κ��� �Ÿ��� �������� �����ϱ�
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
    candi[0] = { 1.214, 1.205, 1.209 }; // �������κ��� �Ÿ��� 6�̸��� ������ ������� ������ pivot��ǥ
    //candi[0] = { 1.215, 1.215, 1.215 }; // ������ �������� ���� pivot��ǥ
    int pt = getNearest(candi[0]);
    candi[0] = { p[pt][0], p[pt][1], p[pt][2] };
    result[0] = pt;

    rint i, j;
    for (i = 0; i < LM; ++i) {  // �� ���� �������κ����� �Ÿ� ���ϱ�
        A[i] = i;               // �� ����ȣ�� A[]�� ����
        zeroD[i] = sq(p[i][0]) + sq(p[i][1]) + sq(p[i][2]);
    }

    mergeSort(A, 0, LM);        // �� ��ȣ�� �������κ����� �Ÿ��� �������� �������� ����

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