/*
Bit_ImageMap3
[Solution Sketch]
1. ��Ʈ�� �ܾ����
   en : ��Ʈ�� �ܾ��(800~900), fn = 1023 - en
2. ������ ������ �󵵼��� �������� ��Ʈ�� �ܾ ����
   fn���� �ܾ�� 9bit������ ǥ��
   en - fn���� �ܾ�� 10bit�� ǥ���ϴ� ������ ����� �� �ִ�.

SEED: 5, SCORE : ��189**** ~ 190****
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
    long long entry[1025];    // ��Ʈ���ܾ�(�ܾ�|����)
    int wnum[1 << 16];        // ������ �ܾ �����ϴ� ��Ʈ�� �ܾ� �ε���
    int en = 0, wn = 0;       // ��Ʈ�� �ܾ��, ������ �ܾ��
    int freq[1025] = { 0 };   // ���� �󵵼�
    int rk[1025] = { 0 };     // �󵵼� �������� ��ŷ
    int sorted[1025] = { 0 }; // �󵵼� ������������ ���ĵ� ��Ʈ�� �ε���

    long long word = 0;
    rint i, j, len = 0;
    for (i = 0; i < STRN && str[i]; ++i) {
        word = 0, len = 0;
        for (; i <= STRN && str[i] != ' '; ++i) {
            word = word * 32 + str[i] - 96;
            len++;
        }

        word = (word << 3) + len;
        for (j = 0; j < en && entry[j] != word; ++j); // linear search
        if (j == en) {          // ���ο� �ܾ� ����
            entry[en++] = word;
        }
        wnum[wn++] = j;
        freq[j] ++;             // j�� �ܾ��� ���󵵼� ����
    }

    for (i = 0; i < en; ++i) {  // �󵵼��� ������������ ��ŷ�ο�
        for (j = 0; j < i; ++j) if (freq[j] >= freq[i])
            rk[i]++;
        for (j++; j < en; ++j) if (freq[j] > freq[i])
            rk[i]++;

        sorted[rk[i]] = i;       // ��ŷ���� ����
    }

    rint idx = 0;
    write(enc_str, idx, en), idx += 10;   // ��Ʈ�� �ܾ�� ���
    write(enc_str, idx, wn), idx += 14;   // ������ �ܾ�� ���

    for (i = 0; i < en; ++i) {
        word = entry[sorted[i]]; // ��ŷ�� ���� �ܾ���� ���
        len = word & 7, word >>= 3;
        write(enc_str, idx, len), idx += 3;
        for (j = 0; j < len; ++j) {
            write(enc_str, idx, word & 31), idx += 5;
            word >>= 5;
        }
    }

    int fn = 1023 - en;          // ���ڸ� ��
    for (i = 0; i < wn; ++i) {
        j = rk[wnum[i]];
        if (j < fn) {            // ���� ��ŷ���� ���ڸ� �� ��ŭ�� 9bit�Ҵ�
            write(enc_str, idx, j), idx += 9;
        }
        else {                   // en - fn���� ���� ��ŷ���� 10bit�Ҵ�
            j += fn;             // fn���� ���� ��ŷ�� ���еǰ� �ϱ� ���Ͽ�
            write(enc_str, idx, j >> 1), idx += 9;
            write(enc_str, idx, j & 1), idx++;
        }
    }
    return (idx + 7) / 8;
}

void decode(char* dec_str, char* enc_str, int encn) {
    rint idx = 0;
    int en = read(enc_str, idx, 10); idx += 10;
    int fn = 1023 - en;
    int wn = read(enc_str, idx, 14); idx += 14;

    char dict[1025][8] = { 0 };
    rint i, j, t = 0;
    for (i = 0; i < en; ++i) {
        int len = read(enc_str, idx, 3); idx += 3;
        for (j = len - 1; j >= 0; --j) {
            int k = read(enc_str, idx, 5); idx += 5;
            dict[i][j] = k + 96;
        }
    }

    for (i = 0; i < wn; ++i) {
        rint k = read(enc_str, idx, 9); idx += 9;
        if (k >= fn) {    // ���� ��ŷ�� ��� 10bit�̴�.
            k = (k << 1) | read(enc_str, idx, 1), idx++;
            k -= fn;
        }
        for (j = 0; dict[k][j]; ++j)
            dec_str[t++] = dict[k][j];
        dec_str[t++] = ' ';
    }
}
