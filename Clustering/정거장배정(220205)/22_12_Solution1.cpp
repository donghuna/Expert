/*
37_EX���������_user_ver01
huristic
local search version
seed : 5
score : 44397911.735631
*/
#include <cstdio>

#define rint register int
const int LM = 100000;
const double* hp;            // house[]
double A[LM], prefixSum[LM]; // A[] : sorted house[], prefixSum[]: prefix sum
int idx[LM], T[LM];          // house[]'s index
int ret[6] = { 0, 0, 0, 0, 0, 100000 };

double getCost(int s, int e) {
    int m = (s + e) / 2;
    double sCost = A[m] * (m - s + 1) - (prefixSum[m] - prefixSum[s] + A[s]);
    double eCost = (prefixSum[e] - prefixSum[m]) - A[m] * (e - m);
    return sCost + eCost;
}

void msort(int s, int e) {
    if (s >= e) return;
    rint m = (s + e) / 2, i = s, j = m + 1, k = s;
    msort(s, m), msort(m + 1, e);
    while (i <= m && j <= e) {
        if (hp[idx[i]] < hp[idx[j]]) T[k++] = idx[i++];
        else T[k++] = idx[j++];
    }
    while (i <= m) T[k++] = idx[i++];
    while (j <= e) T[k++] = idx[j++];
    for (i = s; i <= e; ++i) idx[i] = T[i];
}
// house[]: ����ġ, station[]: ������ ��ġ, alloc[]: station[alloc[]]�� ����Ű�� ������ ��ȣ(0~4)
void test(double const house[], double station[], unsigned int alloc[]) {
    hp = house;
    double ans = 1e15;                  // min dist sum;
    rint i, j, k, x;
    for (i = 0; i < LM; ++i) alloc[i] = 0, idx[i] = i;

    msort(0, LM - 1);

    for (i = 0; i < LM; ++i) A[i] = house[idx[i]];    // ���ĵ� ���� ��ġ��
    prefixSum[0] = A[0];
    for (i = 1; i < LM; ++i) prefixSum[i] = prefixSum[i - 1] + A[i];  // prefix sum

    double cost[6], sum;   // cost[i]: i�� ���������� ���̴� ������ �Ÿ���, sum: ����
    for (i = 12000; i <= 22000; i += 100) {                  // 2���� ����
        sum = cost[0] = getCost(0, i - 1);                   // 1���� �����
        for (j = 34000; j <= i + 22000; j += 100) {          // 3���� ����
            cost[1] = getCost(i, j - 1), sum += cost[1];     // 2���� �����
            for (k = 56000; k <= j + 22000; k += 100) {      // 4���� ����
                cost[2] = getCost(j, k - 1), sum += cost[2]; // 3���� �����
                for (x = 78000; x <= k + 22000; x += 100) {  // 5���� ����
                    cost[3] = getCost(k, x - 1);             // 4���� �����
                    cost[4] = getCost(x, LM - 1);            // 5���� �����
                    sum += cost[3] + cost[4];
                    if (sum < ans) {
                        ans = sum;
                        ret[1] = i, ret[2] = j, ret[3] = k, ret[4] = x;
                    }
                    sum -= cost[3] + cost[4];
                }
                sum -= cost[2];
            }
            sum -= cost[1];
        }
    }

    for (i = 0; i < 5; ++i) {
        int s = ret[i], e = ret[i + 1];
        station[i] = A[(s + e - 1) / 2]; // �������� ��ġ
        for (j = s; j < e; ++j) alloc[idx[j]] = i;
    }

    //for (i = 0; i < 5; ++i) printf("%d ", ret[i]);
}