/*
22_EX�޸���_user_ver03_journaling
*/
#define rint register int

const int LM = 110000;
const int HLM = 1 << 21;  // 2097152

int scnt;
char strDB[LM][1024];     // 100MB

int target;              // insert�� ����� ���� ��ȣ
int hisLen;               // ��� ����
int cmd[HLM];             // ��� ��ȣ append:0, insert:1, erase:-1
int memoLine[HLM];        // �Լ��� �Ű������� �־��� ����,����,�߰��� ������ index
int srcLine[HLM];         // insert�� ����� ���� ��ȣ�� ���
int memoLen;              // ���� ����: 100000������ Ȯ���ϴ� �뵵

void strcpy(char* dest, char* src) {
    for (rint i = 0; dest[i] = src[i]; ++i) {}
}

void append(char* str) {
    strcpy(strDB[scnt], str);
    cmd[++hisLen] = 0;         // append ��� ��ȣ
    memoLine[hisLen] = scnt++; // ������ ����� index
    ++memoLen;                 // ���� ���� ����
}

void insert(int line, char* str) {
    cmd[++hisLen] = 1;           // insert ��� ��ȣ
    memoLine[hisLen] = line;     // ������� �־��� ���� ���� ��ġ ���
    srcLine[hisLen] = target;   // linestring(int line) index
    ++memoLen;                   // ���� ���� ����
}

void erase(int line) {
    cmd[++hisLen] = -1;          // erase ��� ��ȣ
    memoLine[hisLen] = line;     // ������� �־��� ���� ���� ��ġ ���
    --memoLen;                   // ���� ���� ����
}

char* linestring(int line) {
    if (memoLen < 100000)        // 10�� ��������
        return strDB[target = line]; // line�� ���������� ���� ���� ����

    // �������� �ѹ��� ����
    for (rint i = hisLen; i > 1000; --i) {
        if (cmd[i] > 0) {          // insert�� ���
            if (memoLine[i] == line)
                line = srcLine[i]; // ���� ���� ��ȣ
            else if (memoLine[i] < line)  // ������ġ�� �� �����̶��
                line--;            // ������ ������ ����
        }
        else {                     // append, erase
            if (memoLine[i] <= line)
                line -= cmd[i];    // ������ ��� 1����, �߰��� ��� ��ȭ ����
        }
    }
    return strDB[line];
}