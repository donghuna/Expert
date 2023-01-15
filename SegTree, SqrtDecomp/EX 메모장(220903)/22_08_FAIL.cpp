#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
38_EX�޸���_userTest01
naive version, use STL & cstring libray
[strategy]
1. ���ڿ��� ���� ����
2. ���ڿ� index�� �迭�� ����
   ���� �迭�� �������� ���� ���Ұ� �̷�����Ƿ�
   vector�� ���
3. �ð����⵵ O(N * N)
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