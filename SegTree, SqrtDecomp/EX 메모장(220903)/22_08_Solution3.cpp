#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX�޸���_user version 03
comkiwer's test
offline query(Journaling)
*/
#define rint register int

const int LM = 1 << 17;   // 131072
const int HLM = 1 << 21;  // 2097152

int srrLen;
char srr[LM][1024];       // 128MB

int curLine;              // insert�� ����� ���� ��ȣ
int hisLen;               // ��� ����
int cmd[HLM];             // ��� ��ȣ append:0, insert:1, erase:-1
int memoLine[HLM];        // �Լ��� �Ű������� �־��� ����,����,�߰��� ������ index
int srcLine[HLM];         // insert�� ����� ���� ��ȣ�� ���
int memoLen;              // ���� ����

void strcpy(char* dest, char* src) {
    for (rint i = 0; dest[i] = src[i]; ++i) {}
}

void append(char* str) {
    strcpy(srr[srrLen], str);
    cmd[++hisLen] = 0;           // append ��� ��ȣ
    memoLine[hisLen] = srrLen++; // ������ ����� index
    ++memoLen;                   // ���� ���� ����
}

void insert(int line, char* str) {
    cmd[++hisLen] = 1;           // insert ��� ��ȣ
    memoLine[hisLen] = line;     // ������� �־��� ���� ���� ��ġ ���
    srcLine[hisLen] = curLine;   // linestring(int line) index
    ++memoLen;                   // ���� ���� ����
}

void erase(int line) {
    cmd[++hisLen] = -1;          // erase ��� ��ȣ
    memoLine[hisLen] = line;     // ������� �־��� ���� ���� ��ġ ���
    --memoLen;                   // ���� ���� ����
}

char* linestring(int line) {
    if (memoLen < 100000)        // 10�� ��������
        return srr[curLine = line]; // line�� ���������� ���� ���� ����

    // �������� �ѹ��� ����
    for (rint i = hisLen; i > 1000; --i) {
        if (cmd[i] > 0) {        // insert�� ���
            if (memoLine[i] == line)
                line = srcLine[i]; // ���� ���� ��ȣ
            else if (memoLine[i] < line)
                line--;            // ������ ������ ����
        }
        else {
            if (memoLine[i] <= line)
                line -= cmd[i];    // ������ ��� 1����, �߰��� ��� ��ȭ ����
        }
    }
    return srr[line];
}