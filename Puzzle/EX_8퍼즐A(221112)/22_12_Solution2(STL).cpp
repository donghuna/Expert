#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
38_EX8퍼즐A_user_BFS_ver00_STL
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
    hmap[123456780] = 0;           // face가 123456780인 데이터는 que[0]에 있다.
    while (fr < re) {
        Data t = que[fr];
        rint i = 0;
        do {
            rint newZeroPos = adj[t.zeroPos][i];
            rint val = t.face / deci[newZeroPos] % 10;  // 0이 이동할 위치에 있는 1~8의 숫자 추출하기
            rint newFace = t.face - val * deci[newZeroPos] + val * deci[t.zeroPos];  // 0을 이동시키기
            if (hmap.count(newFace) == 0) {             // newFace가 이전에 만들어진적이 있는지 확인
                hmap[newFace] = re;                     // 새롭게 만들어진 수라면
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