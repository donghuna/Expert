#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
38_EX8����A_user_BFS_ver00_STL
*/

extern void move(int mode);

#include <cstdio>
#include <algorithm>
#include <unordered_map>
using namespace std;

#define rint register int

const int LM = 181440; // 9!/2
struct Data {
    int face, zeroPos, pathIdx, pathDir;
}que[LM + 5];
int fr, re;

unordered_map<int, int> hmap; // <int:face, int: que[]'s index>
int deci[9] = { 100'000'000, 10'000'000, 1'000'000, 100'000, 10'000, 1'000, 100, 10, 1 };
int adj[9][5] = { {1, 3}, {0, 2, 4}, {1, 5}, {0, 4, 6}, {1, 3, 5, 7}, {2, 4, 8}, {3, 7}, {4, 6, 8}, {5, 7} };
int dir[9][5] = { {3, 1}, {2, 3, 1}, {2, 1}, {0, 3, 1}, {0, 2, 3, 1}, {0, 2, 1}, {0, 3}, {0, 2, 3}, {0, 2} };

void BFS() {
    que[re++] = { 123456780, 8 };  // {123456780, 8, 0, 0}
    hmap[123456780] = 0;           // face�� 123456780�� �����ʹ� que[0]�� �ִ�.
    while (fr < re) {
        Data t = que[fr];
        rint i = 0;
        do {
            rint newZeroPos = adj[t.zeroPos][i];
            rint val = t.face / deci[newZeroPos] % 10;  // 0�� �̵��� ��ġ�� �ִ� 1~8�� ���� �����ϱ�
            rint newFace = t.face - val * deci[newZeroPos] + val * deci[t.zeroPos];  // 0�� �̵���Ű��
            if (hmap.count(newFace) == 0) {             // newFace�� ������ ����������� �ִ��� Ȯ��
                hmap[newFace] = re;                     // ���Ӱ� ������� �����
                que[re++] = { newFace, newZeroPos, fr, dir[t.zeroPos][i] ^ 1 };
            }
            i++;
        } while (adj[t.zeroPos][i]);

        ++fr;
    }
}

void test(const int puzzle[3][3])
{
    // If you modify the puzzle const data by bypassing it, you will be disqualified.
    if (re == 0) BFS();
    rint i, j, face = 0;
    for (i = 0; i < 3; ++i) for (j = 0; j < 3; ++j) {
        face = face * 10 + puzzle[i][j];
    }

    i = hmap[face];
    while (i) {
        move(que[i].pathDir);
        i = que[i].pathIdx;
    }
}