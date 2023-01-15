#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
06_square_user_ver04
seed : 1117, score: 8715
*/
#define rint register int
const int LM = 66;
int A[LM][LM], B[LM][LM], S[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, k, r, c, ansA = 0, ansB = 0;
    // (i, j)을 (i+1, j+1)로 평행이동시키기
    for (i = 0; i < 64; ++i) {
        for (j = 0; j < 64; ++j) S[i + 1][j + 1] = image[i][j];
    }

    // A[][]을 복원하기
    for (i = 1; i <= 65; ++i) {
        for (j = 1; j <= 65; ++j) {
            A[i][j] = B[i][j] = S[i][j] - S[i][j - 1] - S[i - 1][j] + S[i - 1][j - 1];
        }
    }

    // 순방향으로 정사각형 구하기
    for (i = 1; i <= 55; ++i) {                     // (55, 55)는 (sr, sc)의 최대범위
        for (j = 1; j <= 55; ++j)if (A[i][j] > 0) {
            for (r = i + 10; r < LM; ++r) {
                for (c = j + 10; c < LM; ++c) if (A[r][c] > 0) {
                    if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) {
                        // 직사각형이라면
                        --A[i][j], --A[r][c], ++A[i][c], ++A[r][j];
                        if (r - i == c - j)
                            ansA++;   // 정사각형이라면
                    }
                }
            }
        }
    }

    // 역방향 정사각형 구하기
    for (i = 55; i > 0; --i) {                     // (55, 55)는 (sr, sc)의 최대범위
        for (j = 55; j > 0; --j)if (B[i][j] > 0) {
            for (r = i + 10; r < LM; ++r) {
                for (c = j + 10; c < LM; ++c) if (B[r][c] > 0) {
                    if (B[i][j] > 0 && B[r][c] > 0 && B[i][c] < 0 && B[r][j] < 0) {
                        // 직사각형이라면
                        --B[i][j], --B[r][c], ++B[i][c], ++B[r][j];
                        if (r - i == c - j)
                            ansB++;   // 정사각형이라면
                    }
                }
            }
        }
    }

    rint zcntA = 0, zcntB = 0;

    for (i = 1; i < LM; ++i) {
        for (j = 1; j <= LM; ++j) {
            zcntA += A[i][j] == 0;
            zcntB += B[i][j] == 0;
        }
    }

    if (zcntA > zcntB)
        return ansA;

    return ansB;
}