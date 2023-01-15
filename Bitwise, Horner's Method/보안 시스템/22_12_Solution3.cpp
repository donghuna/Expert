/*
11_���Ƚý���_user_ver03
bitwise + DP
*/
const int LM = 920;
int N, entry[LM + 5];
int popCnt[4096];  // popCnt[i]: i�� ���� 1�� ��Ʈ��

int ffs(int n) {
    for (int i = 0; i < 12; ++i)
        if ((n >> i) & 1) return i;
    return 0;
}

int encoding(int x, int y) {
    for (int i = 1; N < LM; ++i) { // DP�� �̿��Ͽ� popcnt ���ϱ�
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