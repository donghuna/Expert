#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
j5296_EX¸Þ¸ðÀå_user_ver01
comkiwer's test
use SegTree + SqrtDecomposition
*/
#define rint register int

const int LM = 1 << 17;
const int TLM = 1 << 10;
const int MLM = 100001;
int sn, mcnt, idx;
char srr[LM][1024];

void Strcpy(char* dest, char* src) {
    while (*dest++ = *src++);
}

struct Data {
    int A[1000], an;
    void insert(int k, int sidx) {
        for (rint i = an; i > k; --i) A[i] = A[i - 1];
        A[k] = sidx, an++;
    }
    void erase(int k) {
        for (rint i = k; i < an; ++i) A[i] = A[i + 1];
        an--;
    }
}leaf[TLM];
int tree[TLM * 2];

void push(int node, int s, int e, int tg, int sidx) {
    tree[node]++;
    if (s == e) {
        leaf[s].insert(tg, sidx);
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) push(lch, s, m, tg, sidx);
    else {
        int sz = (m - s + 1) * 100;
        if (tree[lch] + 1 <= sz && tree[lch] == tg)
            push(lch, s, m, tg, sidx);
        else
            push(rch, m + 1, e, tg - tree[lch], sidx);
    }
}

void pop(int node, int s, int e, int tg) {
    tree[node]--;
    if (s == e) {
        leaf[s].erase(tg);
        return;
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) pop(lch, s, m, tg);
    else pop(rch, m + 1, e, tg - tree[lch]);
}

int query(int node, int s, int e, int tg) {
    if (s == e) {
        return leaf[s].A[tg];
    }
    int lch = node * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > tg) return query(lch, s, m, tg);
    return query(rch, m + 1, e, tg - tree[lch]);
}

void append(char* str) {
    Strcpy(srr[++sn], str);
    push(1, 0, TLM - 1, mcnt++, sn);
}

void insert(int line, char* str) {
    push(1, 0, TLM - 1, line, idx);
    mcnt++;
}

void erase(int line) {
    pop(1, 0, TLM - 1, line);
    mcnt--;
}

char* linestring(int line) {
    idx = query(1, 0, TLM - 1, line);
    return srr[idx];
}