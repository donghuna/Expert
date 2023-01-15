#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
22_EX�޸���_userTest_stl_analysis
*/

#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int LM = 110000;
const int MOD = 100;
char strDB[LM][1024];  // ���ο� ���ڿ� ����
int scnt;              // strDB�� �� ����, 1_base
vector<int> memo;      // strDB�� ���ȣ�� �����Ͽ� �޸����� ǥ��
int mcnt;              // memo���� ����               
int target;            // linestring���� ������ strDB �� ��ȣ

int inCnt[LM], delCnt[LM];
int mx;

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

void append(char* str) {
    inCnt[mcnt / MOD] ++;
    mx = max(mx, inCnt[mcnt / MOD] - delCnt[mcnt / MOD]);
    strcpy(strDB[++scnt], str);  // strDB�� 1_base
    memo.push_back(scnt);
    mcnt++;
}

void insert(int line, char* str) {
    inCnt[line / MOD]++;
    mx = max(mx, inCnt[mcnt / MOD] - delCnt[mcnt / MOD]);
    memo.insert(memo.begin() + line, target);
    mcnt++;
}

void erase(int line) {
    delCnt[line / MOD] ++;
    memo.erase(memo.begin() + line);
    mcnt--;
}

char* linestring(int line) {
    target = memo[line];
    return strDB[target];
}

void output() {
    printf("mx : %d\n", mx);
}