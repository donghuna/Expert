/*
37_EX정거장배정_user_ver02
long long version & radix sort & Dynamic Programing
D[i][j] = i개의 정거장에 j번 집까지 할당할 때 최소 거리합.
seed : 5
score : 44395152.993562
*/
#include <cstdio>

#define rint register int
const int LM = 100000;
const int MOD = 1 << 9;
const int MASK = MOD - 1;
using LL = long long;
const LL INF = (LL)1e14;
int hp[LM];                            // house position
int A[LM], idx[LM], trr[LM], cnt[MOD];
LL sum[LM], dt[5][LM];
int path[5][LM];
int st[] = { 12000, 34000, 56000, 78000, 100000 }; // st[i]-1 : i구간 끝의 최소 한계, st[i] : i+1구간 시작의 최소 한계
int ed[] = { 22000, 44000, 66000, 88000, 100000 }; // ed[i]-1 : i구간 끝의 최대 한계, st[i] : i+1구간 시작의 최대 한계

LL getCost(int s, int e) {
    int m = (s + e) / 2;
    LL sCost = sum[m] - sum[s] - A[m] + A[s];
    LL eCost = sum[e] - sum[m];
    if ((s + e) & 1) eCost -= A[m];
    return eCost - sCost;
}

void rSort() {
    rint i, j;
    int* ap = trr, * bp = idx, * tp;
    for (i = 0; i < 27; i += 9) {
        for (j = 0; j < MOD; ++j) cnt[j] = 0;
        for (j = 0; j < LM; ++j) cnt[(hp[ap[j]] >> i) & MASK] ++;
        for (j = 1; j < MOD; ++j) cnt[j] += cnt[j - 1];
        for (j = LM - 1; j >= 0; --j) {
            bp[--cnt[(hp[ap[j]] >> i) & MASK]] = ap[j];
        }
        tp = ap, ap = bp, bp = tp;
    }
}

int min(int a, int b) { return  a < b ? a : b; }
int max(int a, int b) { return  a > b ? a : b; }
int maxDiff;
void test(double const house[], double station[], unsigned int alloc[]) {
    maxDiff = 0;
    rint i, j, k, s, m, e;
    for (i = 0; i < LM; ++i) hp[i] = (int)(house[i] * 1000000); // convert int type

    for (i = 0; i < LM; ++i) trr[i] = i;                        // index sort
    rSort();

    sum[0] = A[0] = hp[idx[0]];                                 // data copy, get prefixSum
    for (i = 1; i < LM; ++i) A[i] = hp[idx[i]], sum[i] = sum[i - 1] + A[i];

    //for (i = 0; i < 5; ++i) {
    //  for (j = 0; j < LM; ++j) dt[i][j] = INF, path[i][j] = 0;
    //}

    // 1st section process
    LL cost = 0;
    for (s = m = e = 0; e < ed[0]; ++e) {
        cost += A[e] - A[(s + e) / 2];
        dt[0][e] = cost;
    }
    /*
    int st[] = { 12000, 34000, 56000, 78000, 100000};  // st[i]-1 : i구간 끝의 최소 한계, st[i] : i+1구간 시작의 최소 한계
    int ed[] = { 22000, 44000, 66000, 88000, 100000 }; // ed[i]-1 : i구간 끝의 최대 한계, st[i] : i+1구간 시작의 최대 한계
    */

    // 2, 3, 4, 5 section process 
    for (i = 1; i < 5; ++i) {
        k = ed[i - 1];                              // path index
        for (e = ed[i] - 1; e >= st[i] - 1; --e) {  // range end index
            if (e - k + 1 < 12000) k--;
            s = k;                                  // range start index
            dt[i][e] = dt[i - 1][s - 1] + getCost(s, e), path[i][e] = s;
            int last = max(st[i - 1], e - 22000 + 1);
            for (; s >= last; --s) {
                cost = getCost(s, e);
                if (dt[i][e] >= dt[i - 1][s - 1] + cost) {
                    dt[i][e] = dt[i - 1][s - 1] + cost;
                    path[i][e] = s;
                }
            }
            k = path[i][e];
        }
    }

    e = LM - 1;
    for (i = 4; i >= 0; --i) {
        s = path[i][e];
        station[i] = (double)A[(s + e) / 2] / 1000000;
        for (j = s; j <= e; ++j) alloc[idx[j]] = i;
        e = s - 1;
    }
}