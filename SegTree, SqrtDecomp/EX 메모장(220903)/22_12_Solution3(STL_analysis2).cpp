#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
22_EX�޸���_userTest_stl_analysis02
use stl
sqrt decomposition test
*/

#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int LM = 110000;
const int MOD = 100;
char strDB[LM][1024];    // ���ο� ���ڿ� ����
int scnt;                // strDB�� �� ����, 1_base
vector<int> memo[1100];  // strDB�� ���ȣ�� block(100�� ���� �ϳ��� ��������)������ �����Ͽ� �޸����� ǥ��
int mcnt;                // memo[mcnt]���� ������ ������ȣ              
int target;              // linestring���� ������ strDB �� ��ȣ
int mx = 100;

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

void append(char* str) {
    strcpy(strDB[++scnt], str);  // strDB�� 1_base
    if (memo[mcnt].size() < MOD) memo[mcnt].push_back(scnt);
    else memo[++mcnt].push_back(scnt);
}

void insert(int line, char* str) {  // line�� 0_base
    // str�� ������  block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && memo[i].size() <= line; ++i)
        line -= memo[i].size();
    memo[i].insert(memo[i].begin() + line, target);
    mx = max(mx, (int)memo[i].size());
}

void erase(int line) {              // line�� 0_base
    // ������  block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && memo[i].size() <= line; ++i)
        line -= memo[i].size();
    memo[i].erase(memo[i].begin() + line);
}

char* linestring(int line) {        // line�� 0_base
    // block��ȣ ���ϱ�
    int i = 0;
    for (; i <= mcnt && memo[i].size() <= line; ++i)
        line -= memo[i].size();
    target = memo[i][line];
    return strDB[target];
}

void output() {
    printf("mx : %d\n", mx);
    for (int i = 0; i < 1100; ++i) {
        printf("%4d : %4d\n", i, memo[i].size());
    }
}