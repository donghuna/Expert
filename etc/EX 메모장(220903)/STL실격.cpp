#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX�޸���_userTest
naive version, use STL
*/
/// ***** user.cpp *****
#include <bits/stdc++.h>
using namespace std;
#define rint register int

const int LM = 1 << 20;
const int MLM = 100001;
int sn, mcnt, idx;     // mcnt �޸��忡 ��ϵ� �����
char srr[LM][1024];
char* ptr;
vector<int> memo[1025];
int tree[4096];         // �� ������ ���� ����
int mx;

void push(int node, int s, int e, int tg, int sidx) { // tg: nth, sidx: string index
    tree[node]++;                                     // ������ ���� ����
    if (s == e) {
        // s�� �޸��� tg��°�� sidx ����
        memo[s].insert(memo[s].begin() + tg, sidx);

        mx = max(mx, tree[node]);
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) push(lch, s, m, tg, sidx);    // tg�� ������ �պ��� ���� ���
    else {                                            // �׷��� �ʴ� ���
        int sz = (m - s + 1) * 100;                   // ���� ������ �� �Ѱ�
        if (tree[lch] + 1 <= sz && tree[lch] == tg)   // ���ʿ� ���ڸ��� �ִ� ���
            push(lch, s, m, tg, sidx);
        else
            push(rch, m + 1, e, tg - tree[lch], sidx);// ���� ������ ������ ����������
    }
}

void pop(int node, int s, int e, int tg) {
    tree[node]--;                                     // ������ ���� ����
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