#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX메모장_userTest
naive version, use STL
*/
/// ***** user.cpp *****
#include <bits/stdc++.h>
using namespace std;
#define rint register int

const int LM = 1 << 20;
const int MLM = 100001;
int sn, mcnt, idx;     // mcnt 메모장에 기록된 문장수
char srr[LM][1024];
char* ptr;
vector<int> memo[1025];
int tree[4096];         // 각 구간의 합을 저장
int mx;

void push(int node, int s, int e, int tg, int sidx) { // tg: nth, sidx: string index
    tree[node]++;                                     // 구간의 개수 증가
    if (s == e) {
        // s번 메모의 tg번째에 sidx 삽입
        memo[s].insert(memo[s].begin() + tg, sidx);

        mx = max(mx, tree[node]);
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) push(lch, s, m, tg, sidx);    // tg이 구간의 합보다 작은 경우
    else {                                            // 그렇지 않는 경우
        int sz = (m - s + 1) * 100;                   // 왼쪽 구간의 합 한계
        if (tree[lch] + 1 <= sz && tree[lch] == tg)   // 왼쪽에 빈자리가 있는 경우
            push(lch, s, m, tg, sidx);
        else
            push(rch, m + 1, e, tg - tree[lch], sidx);// 남은 개수를 가지고 오른쪽으로
    }
}

void pop(int node, int s, int e, int tg) {
    tree[node]--;                                     // 구간의 개수 감소
    if (s == e) {
        memo[s].erase(memo[s].begin() + tg);
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) pop(lch, s, m, tg);
    else pop(rch, m + 1, e, tg - tree[lch]);
}

int query(int node, int s, int e, int tg) {
    if (s == e) {
        return memo[s][tg];
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) return query(lch, s, m, tg);
    return query(rch, m + 1, e, tg - tree[lch]);
}

void append(char* str) {
    strcpy(srr[++sn], str);
    push(1, 0, 1023, mcnt++, sn);
}

void insert(int line, char* str) {
    push(1, 0, 1023, line, idx);
    mcnt++;
}

void erase(int line) {
    pop(1, 0, 1023, line);
    mcnt--;
}

char* linestring(int line) {
    idx = query(1, 0, 1023, line);
    return srr[idx];
}