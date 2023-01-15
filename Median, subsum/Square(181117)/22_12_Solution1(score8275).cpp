#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
06_square_user_ver02
seed : 1117, score: 8275
*/
#define rint register int
const int LM = 66;
int A[LM][LM], S[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, k, r, c, ans = 0;
    // (i, j)�� (i+1, j+1)�� �����̵���Ű��
    for (i = 0; i < 64; ++i) {
        for (j = 0; j < 64; ++j) S[i + 1][j + 1] = image[i][j];
    }

    // A[][]�� �����ϱ�
    for (i = 1; i <= 65; ++i) {
        for (j = 1; j <= 65; ++j) {
            A[i][j] = S[i][j] - S[i][j - 1] - S[i - 1][j] + S[i - 1][j - 1];
        }
    }

    for (i = 1; i <= 55; ++i) {                     // (55, 55)�� (sr, sc)�� �ִ����
        for (j = 1; j <= 55; ++j)if (A[i][j] > 0) {
            for (r = i + 10; r < LM; ++r) {
                for (c = j + 10; c < LM; ++c) if (A[r][c] > 0) {
                    if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) {
                        // ���簢���̶��
                        --A[i][j], --A[r][c], ++A[i][c], ++A[r][j];
                        if (r - i == c - j)
                            ans++;   // ���簢���̶��
                    }
                }
            }
        }
    }
    return ans;
}