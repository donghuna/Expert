/*
11_보안시스템_user_ver03
bitwise + DP
*/
const int LM = 920;
int N, entry[LM + 5];
int popCnt[4096];  // popCnt[i]: i가 가진 1인 비트수

int ffs(int n) {
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) return i;
    return 0;
}

int encoding(int x, int y) {
    for (int i = 1; N < LM; ++i) { // DP를 이용하여 popcnt 구하기
        popCnt[i] = popCnt[i / 2] + (i & 1);
        if (popCnt[i] == 6)
            entry[++N] = i;
    }
    int k = ffs((entry[x] ^ entry[y]) & entry[x]);
    return k + 1;
}

char answer(int p, int k) {
    int ret = (entry[p] >> (k - 1)) & 1;
    return ret ? 'x' : 'y';
}