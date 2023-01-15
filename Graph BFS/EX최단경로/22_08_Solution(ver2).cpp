/*
20_EX�ִܰ��_ver02
[huristic, local search]
use array bfs, swiching queue
A*�˰��� ����
h(r, c): ������(39999,39999)�� ���� ������ �����Ÿ�
���� �������� �ִ� h(r, c)�� maxVal�̶�� �� ��,
h(nr, nc) + THRESHOLD < maxVal �� ���� ���ܽ��� �˻������� ��ҽ��� �˻��Ѵ�.

THRESHOLD == 15�� ������ �����ڰ� �հ���.
�׷��� seed�� �ٲٸ� ���� Ʋ���� ��� �ټ� �߻�
*/
#define rint register int
const int LM = 100008;
const int THRESHOLD = 36;           //*****

int dr[] = { 0, 1, 0, -1 }, dc[] = { 1, 0, -1, 0 };
int able[5][5] = { {1, 1},{1, 1, 1},{0, 1, 1, 1}, {0, 0, 1, 1} };

struct Data {
    int r, c, u;
}A[LM], B[LM];  // two queue

int max(int a, int b) { return a > b ? a : b; }
int test(char map[40000][40000]) {
    rint an = 0, bn = 0;  // an: A[]'s size, bn:B[]'s size
    int level = 1;
    A[an++] = { 0, 0, map[0][0] };
    map[0][0] = 4;

    for (;; ++level) {
        int maxVal = 0;
        bn = 0;
        for (rint i = 0; i < an; ++i) {
            int r = A[i].r, c = A[i].c;
            int u = A[i].u;      // ��ȿ ������ ����
            for (rint j = 0; j < 4; ++j) {
                int nr = r + dr[j], nc = c + dc[j];
                if (nr < 0 || nr > 39999 || nc < 0 || nc > 39999) continue;
                int v = map[nr][nc];

                if (able[u][v] == 0) continue;

                if (nr == 39999 && nc == 39999) return level + 1; // *****

                B[bn++] = { nr, nc, map[nr][nc] };
                maxVal = max(nr + nc, maxVal);
                map[nr][nc] = 4;      // �湮 üũ
            }
        }
        if (bn == 0) break;
        an = 0;
        for (rint i = 0; i < bn; ++i) {
            if (B[i].r + B[i].c + THRESHOLD >= maxVal) A[an++] = B[i];
        }
    }
    return 0;
}