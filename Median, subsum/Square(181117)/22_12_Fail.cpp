#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
06_square_user_ver01_FAIL
seed : 1117, score: 7822
*/
#define rint register int
const int LM = 66;
int A[LM][LM], S[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, k, r, c, ans = 0;
    // (i, j)을 (i+1, j+1)로 평행이동시키기
    for (i = 0; i < 64; ++i) {
        for (j = 0; j < 64; ++j) S[i + 1][j + 1] = image[i][j];
    }

    // A[][]을 복원하기
    for (i = 1; i <= 65; ++i) {
        for (j = 1; j <= 65; ++j) {
            A[i][j] = S[i][j] - S[i][j - 1] - S[i - 1][j] + S[i - 1][j - 1];
        }
    }

    for (i = 1; i <= 55; ++i) {                     // (55, 55)는 (sr, sc)의 최대범위
        for (j = 1; j <= 55; ++j)if (A[i][j] > 0) {
            // 정사각형을 찾는것이 목적이므로 기울기가 -1인 대각선만 검사한다.
            for (k = 10; i + k < 66 && j + k < 66; ++k) {
                r = i + k, c = j + k;
                if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) {
                    ans++;
                    --A[i][j], --A[r][c], ++A[i][c], ++A[r][j];
                }
            }
        }
    }
    return ans;
}