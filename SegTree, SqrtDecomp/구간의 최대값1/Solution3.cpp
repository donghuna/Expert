#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
33_�������ִ밪1_ver03
use sement tree
*/

#include <stdio.h>

const int LM = 50005;
const int TLM = 1 << 17; /// 131072

int N, Q, A[LM];
int tree[TLM];

inline int max(int a, int b) { return a > b ? a : b; }
void build(int now, int s, int e) {
    if (s >= e) {
        tree[now] = A[s];
        return;
    }
    int lch = now * 2, rch = lch + 1;
    int m = (s + e) / 2;
    build(lch, s, m);
    build(rch, m + 1, e);
    tree[now] = max(tree[lch], tree[rch]);
}

void update(int now, int s, int e, int tg, int val) {
    if (s == e) {
        tree[now] = val;
        return;
    }
    int lch = now * 2, rch = lch + 1;
    int m = (s + e) / 2;
    if (tg <= m) update(lch, s, m, tg, val);  // tg�� ã�ư���
    else update(rch, m + 1, e, tg, val);      // ���⼭ ��ü�� Ž���ϴ� ��� �ð��ʰ��� �ɸ���.
    tree[now] = max(tree[lch], tree[rch]);
}

int query(int now, int s, int e, int si, int ei) {
    if (e < si || ei < s) return 0;           // Ʈ������(s, e)�� ��������(si, ei)�� ��ġ�� ������ ���� ���
    if (si <= s && e <= ei) return tree[now]; // Ʈ������(s, e)�� ��������(si, ei)�� ���ԵǴ� ���
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;

    // Ʈ�������� ���������� �Ϻ� ��ġ�� ��� �Ǵ� ���� ������ Ʈ�������� ���ԵǴ� ���
    int left = query(lch, s, m, si, ei);
    int right = query(rch, m + 1, e, si, ei);
    return max(left, right);
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d %d", &N, &Q);
    int i, si, ei;
    for (i = 1; i <= N; ++i) scanf("%d", A + i);
    build(1, 1, N);
    //for (i = 1; i <= N; ++i) {
    //  update(1, 1, N, i, A[i]);
    //}
    for (i = 0; i < Q; ++i) {
        scanf("%d %d", &si, &ei);
        printf("%d\n", query(1, 1, N, si, ei));
    }
    return 0;
}