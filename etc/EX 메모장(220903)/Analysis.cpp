#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX메모장_userTest
naive version, use STL
*/
#include <bits/stdc++.h>
using namespace std;
#define rint register int

const int LM = 1 << 20;
const int MLM = 100001;
const int MOD = 100;
int scnt, mcnt, tg;
char srr[LM][1024];
char* ptr;
vector<int> memo;

int inCnt[MLM], outCnt[MLM], mx[MLM];
void init() {
    scnt = mcnt = 0;
    memo.clear();
}

void append(char* str) {
    mcnt++;
    inCnt[mcnt / MOD]++; // mcnt / MOD에 추가된 개수
    mx[mcnt / MOD] = max(mx[mcnt / MOD], inCnt[mcnt / MOD] - outCnt[mcnt / MOD]);
    strcpy(srr[++scnt], str);
    memo.push_back(scnt);
}

void insert(int line, char* str) {
    mcnt++;
    inCnt[line / MOD] ++; // mcnt / MOD에 추가된 개수
    mx[line / MOD] = max(mx[line / MOD], inCnt[line / MOD] - outCnt[line / MOD]);
    memo.insert(memo.begin() + line, tg);
}

void erase(int line) {
    outCnt[line / MOD] ++; // mcnt / MOD에 추가된 개수
    mx[line / MOD] = max(mx[line / MOD], inCnt[line / MOD] - outCnt[line / MOD]);
    memo.erase(memo.begin() + line);
    mcnt--;
}

char* linestring(int line) {
    tg = memo[line];
    return srr[tg];
}

void destroy() {
    puts("i번, 추가된수, 삭제된수, 남아있는수, 최대남은수");
    for (int i = 0; i < MLM / MOD; ++i)
        printf("%3d : %5d - %5d = %5d, %5d\n", i, inCnt[i], outCnt[i], inCnt[i] - outCnt[i], mx[i]);
}