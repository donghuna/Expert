#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
22_EX�޸���_userTest_stl_analysis02
use stl
sqrt decomposition test
*/
#define rint register int

const int LM = 110000;
const int MOD = 100;
char strDB[LM][1024];    // ���ο� ���ڿ� ����
int scnt;                // strDB�� �� ����, 1_base
int mcnt;                // B[mcnt]���� ������ ������ȣ              
int target;              // linestring���� ������ strDB �� ��ȣ

struct Block {
    int arr[1000], an;
    void append(int strIndex) { // ���� ���� �� �ڿ� �߰�
        arr[an++] = strIndex;
    }
    void insert(int arrIndex) { // ���� ���� arrIndex�� target����
        for (rint i = an; i > arrIndex; --i)
            arr[i] = arr[i - 1];
        arr[arrIndex] = target;
        an++;
    }
    void erase(int arrIndex) {
        for (rint i = arrIndex; i < an; ++i)
            arr[i] = arr[i + 1];
        an--;
    }
    int getLine(int line) {
        return arr[line];
    }
}B[1100];

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

void append(char* str) {
    strcpy(strDB[++scnt], str);  // strDB�� 1_base
    if (B[mcnt].an < MOD) B[mcnt].append(scnt);
    else B[++mcnt].append(scnt);
}

void insert(int line, char* str) {  // line�� 0_base
    // str�� ������  block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    B[i].insert(line);
}

void erase(int line) {              // line�� 0_base
    // ������  block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    B[i].erase(line);
}

char* linestring(int line) {        // line�� 0_base
    // block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    target = B[i].getLine(line);
    return strDB[target];
}