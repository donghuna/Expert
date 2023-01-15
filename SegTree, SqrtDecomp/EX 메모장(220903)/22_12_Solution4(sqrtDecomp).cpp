#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
22_EX메모장_userTest_stl_analysis02
use stl
sqrt decomposition test
*/
#define rint register int

const int LM = 110000;
const int MOD = 100;
char strDB[LM][1024];    // 새로운 문자열 저장
int scnt;                // strDB의 행 갯수, 1_base
int mcnt;                // B[mcnt]장의 마지막 구역번호              
int target;              // linestring에서 구해진 strDB 행 번호

struct Block {
    int arr[1000], an;
    void append(int strIndex) { // 현재 블럭의 맨 뒤에 추가
        arr[an++] = strIndex;
    }
    void insert(int arrIndex) { // 현재 블럭의 arrIndex에 target삽입
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
    strcpy(strDB[++scnt], str);  // strDB는 1_base
    if (B[mcnt].an < MOD) B[mcnt].append(scnt);
    else B[++mcnt].append(scnt);
}

void insert(int line, char* str) {  // line은 0_base
    // str을 삽입할  block번호 구하기
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    B[i].insert(line);
}

void erase(int line) {              // line은 0_base
    // 삭제할  block번호 구하기
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    B[i].erase(line);
}

char* linestring(int line) {        // line은 0_base
    // block번호 구하기
    int i = 0;
    for (; i <= mcnt && B[i].an <= line; ++i)
        line -= B[i].an;
    target = B[i].getLine(line);
    return strDB[target];
}