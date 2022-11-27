#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
38_EX메모장_userTest01
naive version, use STL & cstring libray
[strategy]
1. 문자열은 별도 보관
2. 문자열 index를 배열로 관리
   관리 배열이 동적으로 증가 감소가 이루어지므로
   vector를 사용
3. 시간복잡도 O(N * N)
*/
#include <cstring>
#include <vector>
using namespace std;
#define rint register int

const int LM = 1 << 20;
const int MLM = 100001;
int scnt, mcnt, tg;
char srr[LM][1024];
char* ptr;
vector<int> memo;

void append(char* str) {
    strcpy(srr[scnt], str);
    memo.push_back(scnt++);
}

void insert(int line, char* str) {
    memo.insert(memo.begin() + line, tg);
}

void erase(int line) {
    memo.erase(memo.begin() + line);
}

char* linestring(int line) {
    tg = memo[line];
    return srr[tg];
}