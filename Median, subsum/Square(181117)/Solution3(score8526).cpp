/*
06_square
seed:   1, score: 8755점
seed:   2, score: 8736점
seed:   3, score: 8683점
seed:   4, score: 8724점
seed:   5, score: 8720점
seed:   6, score: 8792점
seed:   7, score: 8716점
seed:   8, score: 8707점
seed:   9, score: 8799점
seed:  10, score: 8746점
seed:1117, score: 8715점
*/
#define rint register int
const int LM = 66;
int S[LM][LM], A[LM][LM], B[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, r, c;
    int azCnt = 0, bzCnt = 0;  // zero_count
    int aAns = 0, bAns = 0;

    for (i = 0; i < 64; ++i)for (j = 0; j < 64; ++j)
        S[i + 1][j + 1] = image[i][j];               // 미분이 편하도록 대각선 이동하여 저장

    for (i = 1; i < LM; ++i)for (j = 1; j < LM; ++j) // 미분
        A[i][j] = B[i][j] = S[i][j] + S[i - 1][j - 1] - S[i][j - 1] - S[i - 1][j];

    // 순(↘)방향으로 정사각형 구하기
    for (i = 1; i < 56; ++i) for (j = 1; j < 56; ++j) if (A[i][j] > 0) {
        for (r = i + 10; r < LM; ++r) for (c = j + 10; c < LM; ++c) {
            if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) {  // 사각형으로 추정된다면
                A[i][j]--, A[r][c]--, A[i][c]++, A[r][j]++;  // 사각형은 제거
                if (r - i == c - j) aAns++;                   // 정사각형 개수만 구하기
            }
        }
    }

    // 역(↖)방향으로 정사각형 구하기
    for (i = 55; i > 0; --i) for (j = 55; j > 0; --j) if (B[i][j] > 0) {  // 사각형으로 추정된다면
        for (r = i + 10; r < LM; ++r) for (c = j + 10; c < LM; ++c) {
            if (B[i][j] > 0 && B[r][c] > 0 && B[i][c] < 0 && B[r][j] < 0) {
                B[i][j]--, B[r][c]--, B[i][c]++, B[r][j]++;  // 사각형은 제거
                if (r - i == c - j) bAns++;                   // 정사각형 개수만 구하기
            }
        }
    }

    // zero count
    for (i = 1; i < LM; ++i) {
        for (j = 1; j < LM; ++j) {
            azCnt += A[i][j] == 0;
            bzCnt += B[i][j] == 0;
        }
    }

    // 초기 상태가 0이었으므로 0이 많은 경우가 복원이 잘 된 것으로 판단
    if (azCnt > bzCnt)
        return aAns;
    return bAns;
}