/*
12_Bit_image3_user_ver01

[���� ����]
�ҹ��ڷ� ������ �ܾ�(����1~7)��� �־��� ���� 65535�� ����(�������� ����)�� �־�����,
encode(����), decode(����) �ϴ� ����.
(1) ������ ũ�Ⱑ �������� ���� ����.
(2) ����ӵ��� �������� ���� ����.

[���� �м�]
(1) - �����ϴ� �ܾ��� ������ �ִ� 1024(��� 800 ~900)��,
    - �� ���忡 �����ϴ� �ܾ��� ������ ��� 13107�� ����(65535 / 5(�ܾ��� ��ձ���4 + ����1) = 13107)
    - �� Ư¡���� �̿��� �� ������ ?
(2) �ܾ��� �󵵼��� �̿��� �������ڵ� ???
(3) �ѹ��ڸ� 5bit�� �ٿ�ǥ���ϱ� : 65536 * 5 / 8 = 40960btye�� ����ϹǷ� 100�� TC�� ���� ������ 400���� ���̴�.
    �־��� �޸� �ȿ��� �ذᰡ���ϳ� ���� ������ �ޱ� �����.
    ��� 20000�� �̸����� �ذ��� �� �־�� �Ѵ�.

[�ع� ���� : ]
���� dicWords�ܾ �ִ� 1024��� ���� ����,
�����ϴ� �ܾ�� �ܾ����� ����� �����ϰ�
������ �ܾ�� �ܾ����� �ܾ��ȣ�� ǥ���ϸ� �ϳ��� �ܾ 10bit�� ǥ���� �� �ִ�.

(1) encode :
    �����ܾ�� : ����ܾ�� : ���� �ܾ� ��� : ���� �ܾ� ���
    10bit : 14bit : (3bit(�ܾ����) + 5bit(�ѹ���) * 4(�ܾ�������)) * 1000(�����ܾ��) : 10bit * ����ܾ��
    = (10) + (14) + (23 * 1000) + (10 * 13107) = 24 + 23000 + 131070 = 154094 bit
    * �ϳ��� TC�� ���� : 154094 / 8 = 19,261.75��
    (2) decode : endcode�� ������(1)�� ������ Ǯ�� str�ϼ�.
    (3) ���� ����ġ : 19,261.75 * 100 + 2000(����ð�) = �� 1,926,175 ����
    (4) ����
    : �ܾ ���̼����� �����Ͽ� �����Ѵٸ� �ܾ ���� 3bit�� ������ �� �ִ�.

    SEED:5, SCORE : 193**** (���� ������ �ܾ���� �� 13,300 �����̱� ������ ����ġ�� �Ѵ� ����� ���´�.)

(2) ������ ��Ʈ������ ������ �� �־�� �Ѵ�.
    ������ ���� �Լ��� ����� �� �ִ�.

    void write(char*str, int idx, int val) {
        *((UI*)(str + (idx / 8))) += val << (idx % 8);
    }
    int read(char*str, int idx, int bitLen) {
        UI tg = *((UI*)(str + (idx / 8))), mask = (1 << bitLen) - 1;
        return (tg >> (idx % 8)) & mask;
    }
*/
#define rint register int
using UI = unsigned int;
//using ULL = unsigned long long;
//void writeULL(char*str, int idx, ULL val) {
//  *((ULL*)(str + (idx >> 3))) |= val << (idx & 7);
//}
//ULL readULL(char*str, int idx, int bitLen) {
//  ULL tg = *((ULL*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
//  return (tg >> (idx & 7)) & mask;
//}

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx >> 3))) |= val << (idx & 7);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx & 7)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    // 1. dicWords �ܾ� ���� & ������ �ܾ ��ȣ�� ġȯ�ϱ�
    long long dicWords[1025]; // dicWords �ܾ�� : �ܾ�(�ִ�35bit)�� �ϳ��� ������ ����
    int dwLen[1025];          // �� �ܾ��� ����
    int dcnt = 0;             // dicWords �ܾ� ��(������ �ܾ��� ����)

    int sentenceWords[16384]; // ������ �ܾ dicWords�ܾ� ��ȣ�� ġȯ�Ͽ� ����
    int swCnt = 0;            // ������ �ܾ��

    // str[]�� parsing
    long long word = 0;
    rint i, j, wlen = 0;
    for (i = 0; str[i]; ++i) { // ������ ��ȸ�ϸ鼭
        if (str[i] == ' ') {   // �ܾ���
            for (j = 0; j < dcnt && dicWords[j] != word; ++j); // linear search
            if (j == dcnt) {   // ��ã�� ��� : word�� ���ο� �ܾ��̹Ƿ� ����ϱ�
                dicWords[dcnt] = word;
                dwLen[dcnt++] = wlen;
            }
            sentenceWords[swCnt++] = j;  // ������ swCnt��°�ܾ�� �ܾ����� j�� �ܾ�
            word = 0, wlen = 0;// ���ο� �ܾ �����ϱ� ���Ͽ� �ʱ�ȭ
        }
        else {                 // �ܾ ��ӵǴ� ���̶��
            //word = (word << 5) + str[i] - 96;  // Horner's method
            word = word * 32 + str[i] - 96;      // Horner's method : 32������ ����
            wlen++;
        }
    }

    // 2. enc_str�� dicWords�ܾ��, ������ �ܾ�� ����ϱ�
    rint idx = 0;
    write(enc_str, idx, dcnt), idx += 10;   // 1024    dicWords�ܾ�����
    write(enc_str, idx, swCnt), idx += 14;  // 16384   ������ �ܾ�� ���

    // 3. enc_str�� dicWords�ܾ� ����ϱ�
    for (i = 0; i < dcnt; ++i) {
        long long w = dicWords[i];
        write(enc_str, idx, dwLen[i]), idx += 3;      // �ܾ��� ���� ���
        for (j = 0; j < dwLen[i]; ++j) {              // �ܾ� ���
            write(enc_str, idx, w % 32), idx += 5;    // ���ڴ����� ��� : ������ ���ں��� �������� ��ϵ�
            w /= 32;                                  // �������ڸ� ���Ͽ�
        }
    }

    // 4. enc_str�� ������ �ܾ� ��ȣ ����ϱ�
    for (i = 0; i < swCnt; ++i) {
        write(enc_str, idx, sentenceWords[i]), idx += 10;
    }

    int sentenceLength = (idx + 7) / 8;           // �ø���
    return sentenceLength;                        // ����� ���� ��ȯ
}

void decode(char* dec_str, char* enc_str, int encn) {
    // 1. dicWords �ܾ�� ���ϱ�, ������ �ܾ�� ���ϱ�
    rint idx = 0;
    int dcnt = read(enc_str, idx, 10); idx += 10;    // dicWords �ܾ��
    int swCnt = read(enc_str, idx, 14); idx += 14;   // ���� �ܾ��

    // 2. dicWords �ܾ� �����Ͽ� ����ϱ�
    char dicWords[1025][8] = { 0 };
    rint i, j, t = 0;
    for (i = 0; i < dcnt; ++i) {
        int len = read(enc_str, idx, 3); idx += 3;   // ���� ���ϱ�
        for (j = len - 1; j >= 0; --j) {             // ���� �ڸ����� �����Ͽ����Ƿ� �������� 
            int k = read(enc_str, idx, 5); idx += 5; // �ܾ� �����ϱ�
            dicWords[i][j] = k + 96;
        }
    }

    // 3. dec_str�� ���� �����ϱ�
    for (i = 0; i < swCnt; ++i) {
        int k = read(enc_str, idx, 10); idx += 10;
        for (j = 0; dicWords[k][j]; ++j)
            dec_str[t++] = dicWords[k][j];
        dec_str[t++] = ' ';
    }
}