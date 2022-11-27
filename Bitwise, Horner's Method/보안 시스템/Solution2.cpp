/*
3_보안시스템_user_ver01
*/
const int LM = 920;
int N, tab[LM + 5];

int bitcount(int n) {
    int cnt = 0;
    /*for (; n; n -= n & -n) cnt++;*/
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) cnt++;
    return cnt;
}

int ffs(int n) {
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) return i + 1;
    return 0;
}

int encoding(int x, int y) {
    for (int i = 63; N < LM; ++i) {
        if (bitcount(i) == 6) 
            tab[++N] = i;
    }
    int k = ffs((tab[x] ^ tab[y]) & tab[x]);
    return k;
}

char answer(int p, int k) {
    int ret = tab[p] & (1 << (k - 1));
    //int ret = (tab[p] >> (k - 1)) & 1;
    return ret ? 'x' : 'y';
}
