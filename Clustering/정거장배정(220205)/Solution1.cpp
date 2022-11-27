/*
27_정거장배정
local search version
5 : 44397908.763632
*/
#include <cstdio>

#define rint register int
const int LM = 100000;
const double* hp;    // house[]
double A[LM], S[LM]; // A[] : sorted house[], S[]: prefix sum
double ans;          // min dist sum
int idx[LM], T[LM];  // house[]'s index
int ret[6] = { 0, 0, 0, 0, 0, 100000 };

double getCost(int s, int e) {
    int m = (s + e) / 2;
    double sCost = A[m] * (m - s + 1) - (S[m] - S[s] + A[s]);
    double eCost = (S[e] - S[m]) - A[m] * (e - m);
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

void test(double const house[], double station[], unsigned int alloc[]) {
    hp = house;
    ans = 1e15;
    rint i, j, k, x;
    for (i = 0; i < 4; ++i) station[i] = 0;
    for (i = 0; i < LM; ++i) alloc[i] = 0, idx[i] = i;

    msort(0, LM - 1);

    for (i = 0; i < LM; ++i) A[i] = house[idx[i]];
    S[0] = A[0];
    for (i = 1; i < LM; ++i) S[i] = S[i - 1] + A[i];

    double cost[6], sum;
    for (i = 12000; i <= 22000; i += 100) { // 2구역 시작
        sum = cost[0] = getCost(0, i);
        for (j = 34000; j <= i + 22000; j += 100) {  // 3구역 시작
            cost[1] = getCost(i, j), sum += cost[1];
            for (k = 56000; k <= j + 22000; k += 100) {  // 4구역 시작
                cost[2] = getCost(j, k), sum += cost[2];
                for (x = 78000; x <= k + 22000; x += 100) {  // 5구역 시작
                    cost[3] = getCost(k, x);
                    cost[4] = getCost(x, LM);
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
        station[i] = A[(s + e) / 2];
        for (j = s; j < e; ++j) alloc[idx[j]] = i;
    }

    //for (i = 0; i < 5; ++i) printf("%d ", ret[i]);
}