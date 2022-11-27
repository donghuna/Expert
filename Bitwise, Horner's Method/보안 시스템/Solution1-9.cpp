/*
11_보안시스템_user_ver01
Sperner's theorem
*/
const int LM = 920;
int N, A[LM + 5];

int bitcount(int n) {
    int cnt = 0;
    /*for (; n; n -= n & -n) cnt++;*/
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) cnt++;
    return cnt;
}

int ffs(int n) {
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) return i;
    return 0;
}

int encoding(int x, int y) {
    for (int i = 63; N < LM; ++i) {
        if (bitcount(i) == 6)
            A[++N] = i;
    }
    int k = ffs((A[x] ^ A[y]) & A[x]);
    return k + 1;
}

char answer(int p, int k) {
    int ret = (A[p] >> (k - 1)) & 1;
    //int ret = A[p] & (1 << (k - 1));
    return ret ? 'x' : 'y';
}