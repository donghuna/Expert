/*
23_����ִ�_user_ver01
binary bit + Divide & Conquer
*/
extern int countScore(int guess[]);
#define rint register int
const int LM = 256;
int* ret;
int entry[LM];
int remainIdx[LM];

void getEntry() {
    rint i, j = 0, k, p, cnt = 0;
    int guess[LM] = { 0 };
    for (i = 1; i < 256 && cnt < 200; i += 7) {
        p = 0;
        for (j = 0; j < 7; ++j) {
            int len = 1 << j;
            for (k = 0; k < len; ++k) {
                guess[p++] = i + j;
            }
        }
        rint res = countScore(guess) % 256;   /// ���� ������ �Ǵ��Ѵ�.
        for (j = 0; j < 7; ++j) if ((res >> j) & 1) {
            entry[cnt++] = i + j;
        }
    }
}

void DAC(int s, int e, int totalCnt) {
    // base condition
    if (totalCnt == 0) return;     // ������ ����ų� �ڱ� �ڸ� ã�� ��찡 ���ٸ� ����
    if (totalCnt == e - s + 1) {   // s���� e���̿� ���� �ִ� ������ �ڱ� �ڸ��� ã�� ���
        for (rint i = s; i <= e; ++i) {
            ret[remainIdx[i]] = entry[remainIdx[i]];
            entry[remainIdx[i]] = 0;
        }
        return;
    }

    // normal condition : �����Ͽ� Ž��
    int m = (s + e) / 2, left[LM] = { 0 };
    for (rint i = s; i <= m; ++i)
        left[remainIdx[i]] = entry[remainIdx[i]];
    int leftCnt = countScore(left) / 256; // ���� ������ �������� �ڱ� �ڸ� ã�� ���� ���� ���ϱ�
    int rightCnt = totalCnt - leftCnt;    // ������ ������ �������� �ڱ� �ڸ� ã�� ���� ����
    DAC(s, m, leftCnt);
    DAC(m + 1, e, rightCnt);
}

void consistOf(int userRet[])
{
    ret = userRet;
    rint i, tmp, remainCnt = 200;
    for (i = 0; i < 200; ++i) remainIdx[i] = i;
    // 1. get entry[]
    getEntry();

    // 2. find position
    while (true) {
        int cnt = countScore(entry) / 256;     /// �ڱ� �ڸ� ã�� ���� ����
        DAC(0, remainCnt - 1, cnt);

        remainCnt = 0;                         /// �����ִ� ���� ����
        for (i = 0; i < 200; ++i) {
            if (entry[i])
                remainIdx[remainCnt++] = i;    /// �����ִ� ���� �ε��� ���
        }
        if (remainCnt == 0) break;             /// �����ִ� ���� ���ٸ� ����

        /// ���� ������ �� �ڸ��� �̵���Ű��
        tmp = entry[remainIdx[0]];
        for (i = 0; i < remainCnt - 1; ++i)
            entry[remainIdx[i]] = entry[remainIdx[i + 1]];
        entry[remainIdx[i]] = tmp;
    }
}