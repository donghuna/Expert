#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
22_EX메모장_userTest_stl_analysis02
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
char strDB[LM][1024];    // 새로운 문자열 저장
int scnt;                // strDB의 행 갯수, 1_base
vector<int> memo[1100];  // strDB의 행번호를 block(100개 행을 하나의 구역으로)단위로 저장하여 메모장을 표시
int mcnt;                // memo[mcnt]장의 마지막 구역번호              
int target;              // linestring에서 구해진 strDB 행 번호
int mx = 100;

void strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

void append(char* str) {
    strcpy(strDB[++scnt], str);  // strDB는 1_base
    if (memo[mcnt].size() < MOD) memo[mcnt].push_back(scnt);
    else memo[++mcnt].push_back(scnt);
}

void insert(int line, char* str) {  // line은 0_base
    // str을 삽입할  block번호 구하기
    int i = 0;
    for (; i <= mcnt && memo[i].size() <= line; ++i)
        line -= memo[i].size();
    memo[i].insert(memo[i].begin() + line, target);
    mx = max(mx, (int)memo[i].size());
}

void erase(int line) {              // line은 0_base
    // 삭제할  block번호 구하기
    int i = 0;
    for (; i <= mcnt && memo[i].size() <= line; ++i)
        line -= memo[i].size();
    memo[i].erase(memo[i].begin() + line);
}

char* linestring(int line) {        // line은 0_base
    // block번호 구하기
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