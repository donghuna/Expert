/*
11_보안시스템_user_ver02
Sperner's theorem
*/
const int LM = 920;
int N, A[LM + 10];
// make(사용해야할 0의 갯수, 사용해야할 1의 갯수, 만든 수)
void make(int zero, int one, int num) {
    if (zero + one == 0) {
        A[++N] = num;
        return;
    }
    if (zero) make(zero - 1, one, (num << 1) | 0);
    if (one) make(zero, one - 1, (num << 1) | 1);
}

int ffs(int n) {
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) return i;
    return 0;
}

int encoding(int x, int y) {
    if (N == 0) make(6, 6, 0);
    int k = ffs((A[x] ^ A[y]) & A[x]);
    return k + 1;
}

char answer(int p, int k) {
    int ret = A[p] & (1 << (k - 1));
    //int ret = (A[p] >> (k - 1)) & 1;
    return ret ? 'x' : 'y';
}