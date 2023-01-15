/*
Bit_ImageMap3_ver03
[Solution Sketch]
1. ��Ʈ�� �ܾ����
   dwcnt : ��Ʈ�� �ܾ��(800~900), fn = 1023 - dwcnt
2. ������ ������ �󵵼��� �������� ��Ʈ�� �ܾ ����
   fn���� �ܾ�� 9bit������ ǥ��
   dwcnt - fn���� �ܾ�� 10bit�� ǥ���ϴ� ������ ����� �� �ִ�.
SEED: 5, SCORE: 185**** ~ 187****
*/
#define rint register int
using UI = unsigned int;

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx / 8))) |= val << (idx % 8);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx % 8)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    long long dicWords[1024];     // ��Ʈ�� �ܾ�
    int dwLen[1024];            // ��Ʈ�� �� �ܾ��� ����
    int dwcnt = 0;                // ��Ʈ�� �ܾ��

    int wnum[1 << 14];         // ������ �ܾ �����ϴ� ��Ʈ�� �ܾ� �ε���
    int wn = 0;                // ������ �ܾ��

    int freq[1025] = { 0 };    // ���� �󵵼�
    int mxF = 0;               // �ִ� �󵵼�
    int cnt[2048] = { 0 };     // �󵵼� ����Ƚ�� ���
    int ranking[1025] = { 0 }; // i�� ��Ʈ���� ��ũ
    int sorted[1025] = { 0 };  // �󵵼� ������������ ���ĵ� ��Ʈ�� �ε���

    long long word = 0;
    rint i, j, wlen = 0;
    for (i = 0; str[i]; ++i) {
        word = 0, wlen = 0;
        for (; str[i] != ' '; ++i) {
            word = (word << 5) + str[i] - 96;
            wlen++;
        }

        for (j = 0; j < dwcnt && dicWords[j] != word; ++j); // linear search
        if (j == dwcnt) {         // ���ο� �ܾ� ����
            dicWords[dwcnt] = word;
            dwLen[dwcnt++] = wlen;
        }
        wnum[wn++] = j;
        freq[j] ++;            // j�� �ܾ��� ���󵵼� ����
    }

    ////////// [counting sort : desc] //////////
    for (i = 0; i < dwcnt; ++i) {
        if (mxF < freq[i]) mxF = freq[i];
        cnt[freq[i]] ++;
    }
    for (i = mxF - 1; i > 0; --i) cnt[i] += cnt[i + 1];
    for (i = 0; i < dwcnt; ++i) {
        ranking[i] = --cnt[freq[i]];      // i�� ���� ranking[i]
        sorted[ranking[i]] = i;           // ranking[i]�� i��
    }
    ////////////////////////////////////////

    rint idx = 0;
    write(enc_str, idx, dwcnt), idx += 10;   // ��Ʈ�� �ܾ�� ���
    write(enc_str, idx, wn), idx += 14;   // ������ �ܾ�� ���

    for (i = 0; i < dwcnt; ++i) {
        word = dicWords[sorted[i]];          // ��ŷ�� ���� �ܾ���� ���
        wlen = dwLen[sorted[i]];
        write(enc_str, idx, wlen), idx += 3;
        for (j = 0; j < wlen; ++j) {
            write(enc_str, idx, word & 31), idx += 5;
            word >>= 5;
        }
    }

    int fn = 1024 - dwcnt;                   // ���ڸ� ��
    for (i = 0; i < wn; ++i) {
        j = ranking[wnum[i]];
        if (j < fn) {                     // ���� ��ŷ���� ���ڸ� �� ��ŭ�� 9bit�Ҵ�
            write(enc_str, idx, j), idx += 9;
        }
        else {                            // dwcnt - fn���� ���� ��ŷ���� 10bit�Ҵ�
            j += fn;                      // ���� 9��Ʈ�� ���� ��, fn���� ���� ��ŷ�� ���еǰ� �ϱ� ���Ͽ�
            write(enc_str, idx, j >> 1), idx += 9;
            write(enc_str, idx, j & 1), idx++;
        }
    }
    return (idx + 7) / 8;
}

void decode(char* dec_str, char* enc_str, int encn) {
    rint idx = 0;
    int dwcnt = read(enc_str, idx, 10); idx += 10;  // ��Ʈ�� �ܾ�� ���ϱ�
    int fn = 1024 - dwcnt;                          // ���ڸ��� ���ϱ�
    int wn = read(enc_str, idx, 14); idx += 14;  // ������ �ܾ�� ���ϱ�

    char dicWords[1025][8] = { 0 };                 // ��Ʈ�� �ܾ ������ �迭
    rint i, j, t = 0;
    for (i = 0; i < dwcnt; ++i) {                   // ��Ʈ�� �ܾ� �����Ͽ� ����
        int len = read(enc_str, idx, 3); idx += 3;
        for (j = len - 1; j >= 0; --j) {
            int k = read(enc_str, idx, 5); idx += 5;
            dicWords[i][j] = k + 96;
        }
    }

    for (i = 0; i < wn; ++i) {                   // ���� �����ϱ�
        // ��Ʈ�� ��ȣ ã��
        rint k = read(enc_str, idx, 9); idx += 9;
        if (k >= fn) {                           // ���� ��ŷ�� ��� 10bit�̴�.
            k = (k << 1) | read(enc_str, idx, 1), idx++;
            k -= fn;
        }

        for (j = 0; dicWords[k][j]; ++j)            // ���忡 �ܾ� ����ϱ�
            dec_str[t++] = dicWords[k][j];
        dec_str[t++] = ' ';
    }
}