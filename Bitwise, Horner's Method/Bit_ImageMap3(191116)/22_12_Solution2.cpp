/*
Bit_ImageMap3_ver02
�ܾ���� �������� ������ ����
�ܾ���� 3��Ʈ�� �������� �������� TC�� 3*850(���dicWords�ܾ��) / 8 = �� 300�� ������ �� �ִ�.

[���� ����]
�ҹ��ڷ� ������ �ܾ�(����1~7)��� �־��� ���� 65535�� ����(�������� ����)�� �־�����,
encode(����), decode(����) �ϴ� ����.
(1) ������ ũ�Ⱑ �������� ���� ����.
(2) ����ӵ��� �������� ���� ����.

[���� �м�]
(1) - �����ϴ� �ܾ��� ������ �ִ� 1024(��� 800 ~900)��,
    - �� ���忡 �����ϴ� �ܾ��� ������ ��� 13107�� ����(65535 / 5(�ܾ��� ��ձ���4 + ����1) = 13107)
    - �� Ư¡���� �̿��� �� ������ ?
(2) �ܾ��� �󵵼��� �̿��� �������ڵ� ? ? ?
(3) �ѹ��ڸ� 5bit�� �ٿ�ǥ���ϱ� : 65536 * 5 / 8 = 40960btye�� ����ϹǷ� 100�� TC�� ���� ������ 400���� ���̴�.
    �־��� �޸� �ȿ��� �ذᰡ���ϳ� ���� ������ �ޱ� �����.
    ��� 20000�� �̸����� �ذ��� �� �־�� �Ѵ�.

[�ع� ���� : ]
���� dicWords�ܾ �ִ� 1024��� ���� ����, �ܾ����� ����� �ϳ��� �ܾ 10bit�� ǥ���ϱ�
(1) encode :
    �����ܾ�� : ����ܾ�� : ���� �ܾ� ��� : ���� �ܾ� ���
    10bit : 14bit : (3bit(�ܾ����) + 5bit(�ѹ���) * 4(�ܾ�������)) * 1000(�����ܾ��) : 10bit * ����ܾ��
    = (10) + (14) + (23 * 1000) + (10 * 13107) = 24 + 23000 + 131070 = 154094 bit
    * �ϳ��� TC�� ���� : 154094 / 8 = 19, 261.75��
    (2) decode : endcode�� ������(1)�� ������ Ǯ�� str�ϼ�.
    (3) ���� ����ġ : 19,261.75 * 100 + 2000(����ð�) = �� 1,926,175 ����
    (4) ����
    : dicWords �ܾ��� �� dwcnt �� 800~900�� �̹Ƿ� rcnt = 1023 - dwcnt���� �������̴�.
      rcnt�� 9��Ʈ ���� �Ҵ��ϰ� dwcnt-rcnt������ 10��Ʈ�� �Ҵ��ϴ� ������ ����� �� �ִ�.
    : �󵵼��� �������� �������� �󵵼� ���� �ܾ��(rcnt)�� 9bit�� ���� ��ȣ��(dwcnt - rcnt)�� 10bit�� �Ҵ��ϴ� ������ ����� �� �ִ�.

    SEED:5, SCORE : ��189**** ~ 190****
*/
#define rint register int
using UI = unsigned int;

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx >> 3))) |= val << (idx & 7);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx & 7)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    long long dicWords[1025], sorted[1025]; // dicWords �ܾ�� : �ܾ�(�ִ�35bit)+����(3bit)�� �ϳ��� ������ ����
    int cnt[8] = { 0 }, rank[1025];
    int dwcnt = 0;          // dicWords �ܾ� ��

    int wnum[1 << 16];     // ������ �ܾ dicWords�ܾ� ��ȣ�� ġȯ�Ͽ� ����
    int wcnt = 0;          // ������ �ܾ��

    long long word = 0;
    rint i, j, len = 0;
    for (i = 0; i < STRN && str[i]; ++i) {
        if (str[i] == ' ') {
            word = (word << 3) + len;
            for (j = 0; j < dwcnt && dicWords[j] != word; ++j); // full search
            if (j == dwcnt) { // ��ã�� ��� �ܾ� ����ϱ� 
                dicWords[dwcnt++] = word;
                cnt[len]++;
            }
            wnum[wcnt++] = j;  // ������ wcnt��°�ܾ�� �ܾ����� j�� �ܾ�
            word = 0, len = 0; // ���ο� �ܾ �����ϱ� ���Ͽ� �ʱ�ȭ
        }
        else {
            word = (word << 5) + str[i] - 96;  // Horner's method
            len++;
        }
    }

    //enc_str�� dicWords�ܾ�� ���
    rint idx = 0;
    for (i = 1; i < 8; ++i)
        write(enc_str, idx, cnt[i]), idx += 9;

    // counting_sort, rank
    for (i = 1; i < 8; ++i) cnt[i] += cnt[i - 1];
    for (i = dwcnt - 1; i >= 0; --i) {
        len = dicWords[i] & 7;
        rank[i] = --cnt[len];
        sorted[rank[i]] = dicWords[i];
    }

    // 2. ������ �ܾ�� ����ϱ�
    write(enc_str, idx, wcnt), idx += 14;  // 16384

    // 3. enc_str�� dicWords�ܾ� ����ϱ�
    for (i = 0; i < dwcnt; ++i) {
        long long w = sorted[i];
        len = w & 7, w >>= 3;
        for (j = 0; j < len; ++j) {                // �ܾ� ���
            write(enc_str, idx, w & 31), idx += 5; // ���ڴ����� ���
            w >>= 5;                               // �������ڸ� ���Ͽ�
        }
    }

    // 4. enc_str�� ������ �ܾ� ��ȣ ����ϱ�
    for (i = 0; i < wcnt; ++i) {
        write(enc_str, idx, rank[wnum[i]]), idx += 10;
    }

    int sentenceLength = (idx + 7) / 8;           // �ø���
    return sentenceLength;                        // ����� ���� ��ȯ
}

void decode(char* dec_str, char* enc_str, int encn) {
    // 1. dicWords �ܾ�� ���ϱ�, ������ �ܾ�� ���ϱ�
    rint i, j, k, t;
    rint idx = 0;
    int dwcnt = 0, cnt[8] = { 0 };
    for (i = 1; i < 8; ++i)
        cnt[i] = read(enc_str, idx, 9), idx += 9;
    int wcnt = read(enc_str, idx, 14); idx += 14;

    // 2. dicWords �ܾ� �����Ͽ� ����ϱ�
    char dicWords[1025][8] = { 0 };
    for (i = 1; i < 8; ++i) {
        for (j = 0; j < cnt[i]; ++j) {
            for (k = i - 1; k >= 0; --k) {
                t = read(enc_str, idx, 5); idx += 5; // �ܾ� �����ϱ�
                dicWords[dwcnt][k] = t + 96;
            }
            dwcnt++;
        }
    }

    // 3. dec_str�� ���� �����ϱ�
    t = 0;
    for (i = 0; i < wcnt; ++i) {
        int k = read(enc_str, idx, 10); idx += 10;
        for (j = 0; dicWords[k][j]; ++j)
            dec_str[t++] = dicWords[k][j];
        dec_str[t++] = ' ';
    }
}