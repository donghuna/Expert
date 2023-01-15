/*
18_기수정렬_user
*/
#define rint register int

const int LM = (int)25e6 + 1;
const int MSB = 1 << 31;    // -2147483648
const int BASE = 8;
const int MOD = 1 << BASE;  // 256
const int MASK = MOD - 1;   // 255

int sortedArr[LM], cnt[MOD];

void initUser(int nSize, int* arr) {
    rint N = nSize, i, j;
    int* ap = sortedArr, * bp = arr, * tp;

    // preprocessing : MSB flip
    for (i = 0; i < N; ++i) ap[i] = bp[i] ^ MSB;
    //for (i = 0; i < N; ++i) ap[i] = bp[i] + MSB;
    //for (i = 0; i < N; ++i) ap[i] = bp[i] - MSB;

    // radix sort
    for (i = 0; i < 32; i += BASE) {
        for (j = 0; j < MOD; ++j) cnt[j] = 0;                  // init count array
        for (j = 0; j < N; ++j) cnt[(ap[j] >> i) & MASK] ++;   // count
        for (j = 1; j < MOD; ++j) cnt[j] += cnt[j - 1];        // accumulate
        for (j = N - 1; j >= 0; --j)                           // counting sort
            bp[--cnt[(ap[j] >> i) & MASK]] = ap[j];
        tp = ap, ap = bp, bp = tp;
    }
    int debug = 1;
}

int query(int idx) {
    return sortedArr[idx - 1] ^ MSB;
}