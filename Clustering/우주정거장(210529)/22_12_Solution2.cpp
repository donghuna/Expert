/*
39_����������_user ver02
* 10������ �� coordi[i]�߿��� candi[0]���� �� ����� ����
  farthest[100] �߿� �ִ� ��� �� ���� B[]�� ���� ������.(seed�� 5�϶� 185���̴�.)
* farthest[100]�߿� 2���� ������ ���� candi[1], candi[2]��� �� ��,
  B[]���� ������� �����ϴ� ������ ����ϸ� ����ð��� ���� ���� �� �ִ�.

1. ���� ���
    (x, y, z)(0~65535�� 3����)��ǥ10������ �༺�� �־���.
    ���� 3���� ���������� �ϰ�
    �� �༺�� 3������ �� �ּ� ��Ŭ���� �Ÿ��� �Ǵ� ���� ������ ��
    �༺�� ������ ��������� �Ÿ��� ���� �������ּҷ� �ϴ� ������ 3���� �����ϴ� ����

2. ���� �м�
    1) NP ����, ��Ž�� O(100000_C_3 * 100000 * 3) �ð����⵵.
    2) ������ �м� :
    �� ��ǥ�� ������ ���� ��Ģ�� random() / (random() + 1)�̴�.
    �������κ����� �Ÿ��� ������ ���� �Ʒ��� ����.
         6�̸��� ���� : 75241
        30�̸��� ���� : 19678
       300�̸��� ���� : 4551
      3000�̸��� ���� : 467
     30000�̸��� ���� : 59
    113511�̸��� ���� : 4

3. solution sketch
    (1) �� ������ �м��� ����
    �������κ��� �Ÿ� 3000 �̸��� A�׷�� 3000�̻��� B�׷����� ������
    A�׷쿡�� 1���� �������� B�׷쿡�� 2���� �������� �����Ѵ�.
    (2) A�׷� pivot���� {
        1.214, 1.205, 1.209
    }; �������κ��� �Ÿ� 6������ ������ ����� �̿��� �� �ִ�.
    �Ǵٸ� A�׷� pivot���δ�{ 1.215, 1.215, 1.215 }�� ����� �� �ִµ� ���������� ���� ���� pivot�߿� �ϳ��̴�.
    pivot �� ���� ����� ���� ret[0]�� ���Ѵ�.

    (3) B�׷��� ���� �� 60���� �̹Ƿ� ��� ������ ��츦 �����Ͽ� �� ���� ���ϰ�
    tmp[1], tmp[2]�� �����Ѵ�.
    (4) tmp[]�� �̿��Ͽ� ������ ����ϰ� ���� ���� ������ ������ �����Ѵ�.
    �̵��� ������ �ϸ� SCORE : 1442195.114439���̴�.

    (5) ������ �� ����� �ֵ��� �پ��� �õ��� �� �� �� �ִ�.
    ���� ���{ { 1.215, 1.215, 1.215 } �� ���� ����� �� 5���� ���Ͽ� �ĺ��� �ϰ�
    ������ ���Ͽ�(3)(4)������ ������ �� �� �ִ�.
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
    candi[0] = { 1.214, 1.205, 1.209 }; // �������κ��� �Ÿ��� 6�̸��� ������ ������� ������ ��ǥ
    //candi[0] = { 1.215, 1.215, 1.215 }; // ������ �������� ���� ��ǥ
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

    // �������κ��� ����� 100���� ���� farthest�� ����
    for (i = 0; i < 100; ++i) farthest[i].init(p[A[i]]);

    // ����� 100���� ���� ������ ���� ���ɼ��� �ִ� ���� B[]�� ����
    // O(100,000 * 100)
    for (i = 0; i < LM; ++i) {
        double ad = candi[0].getD(p[i]);        // candi[0]���� �Ÿ����ϱ�
        for (j = 0; j < 100; ++j) {
            double bd = farthest[j].getD(p[i]); // farthest[j]���� �Ÿ� ���ϱ�
            if (ad > bd) {                      // farthest[j]�� ������ �޴� ���
                B[++bn] = i;                    // B[]�� ����
                break;
            }
        }
    }

    for (i = 0; i < 100; ++i) {
        candi[1] = { p[A[i]][0], p[A[i]][1], p[A[i]][2] };
        for (j = i + 1; j < 100; ++j) {
            candi[2] = { p[A[j]][0], p[A[j]][1], p[A[j]][2] };
            double sc = getScore();             // B[]���� ������� �����ϱ�
            if (sc < ans) {
                ans = sc;
                result[1] = A[i];
                result[2] = A[j];
            }
        }
    }
}