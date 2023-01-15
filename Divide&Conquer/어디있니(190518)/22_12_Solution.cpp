/*
28_����ִ�_user
D&C
*/
extern int countScore(int guess[]);

#define rint  register int
const int LM = 256;
int* ret;
int entry[LM]; // 200 entry
int index[LM]; // remain index array

void getEntry() {
    rint i, j, p, x, cnt = 0;  // N=255��, K=200���� ���� ���� bin = 7�� ����
    int guess[LM] = { 0 };
    for (i = 1; i <= 255; i += 7) {
        int p = 0, x;
        for (j = 0; j < 7; ++j) {
            int len = 1 << j;  // 1, 2, 4, 8, 16, .., 32768
            for (x = 0; x < len; ++x) {
                guess[p++] = i + j;
            }
        }
        int ret = countScore(guess) % 256;  // ���������� �Ǵ�
        for (j = 0; j < 7; ++j) {
            if ((ret >> j) & 1)  // i + j�� entry���
                entry[cnt++] = i + j;
        }
    }
}

void DAC(int s, int e, int totalCnt) {
    if (totalCnt == 0) return;   // bounding
    // base condition
    if (totalCnt == e - s + 1) {
        for (int i = s; i <= e; ++i) {
            ret[index[i]] = entry[index[i]];// �ڸ��� ã�� ��� ����迭�� �����ϰ�
            entry[index[i]] = 0;            // �����
        }
        return;
    }
    // normal condition
    rint i, m = (s + e) / 2;
    int leftEntry[LM] = { 0 };
    for (i = s; i <= m; ++i) {  // ���ݸ� �����͸� �����Ͽ� Ȯ���ϱ�
        leftEntry[index[i]] = entry[index[i]];
    }
    int leftCnt = countScore(leftEntry) / 256;
    DAC(s, m, leftCnt);
    DAC(m + 1, e, totalCnt - leftCnt);
}

void consistOf(int userRet[])
{
    ret = userRet;
    getEntry();
    int indexCnt = 200;
    rint i;
    for (i = 0; i < 200; ++i) index[i] = i;

    while (indexCnt) {
        int totalCnt = countScore(entry) / 256; // �ڸ��� ã�� ���� ���ϱ�

        // 1. �ڸ��� Ȯ���ϱ�
        DAC(0, indexCnt, totalCnt);

        // 2. ���� �ڸ��� ã�� ���� ��ġ ���ϱ�
        indexCnt = 0;
        for (i = 0; i < 200; ++i) {
            if (entry[i])
                index[indexCnt++] = i;
        }

        // 3. ��ġ�� ȸ����Ű��
        rint t = entry[index[0]];
        for (i = 0; i < indexCnt - 1; ++i) {
            entry[index[i]] = entry[index[i + 1]];
        }
        entry[index[i]] = t;
    }
}
