*
ver02
seed:1117, score: 8575 : PASS
*/
#define rint register int

const int LM = 66;
int A[LM][LM], S[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, r, c;
    int ans = 0;
    for (i = 0; i < 64; ++i) {
        for (j = 0; j < 64; ++j) {
            S[i + 1][j + 1] = image[i][j];
        }
    }

    for (i = 1; i < LM; ++i) {
        for (j = 1; j < LM; ++j) {
            A[i][j] = S[i][j] - S[i - 1][j] - S[i][j - 1] + S[i - 1][j - 1];
        }
    }

    for (i = 1; i < 56; ++i) {
        for (j = 1; j < 56; ++j)if(A[i][j] > 0){
            for (r = i + 10; r < LM; ++r) {
                for (c = j + 10; c < LM; ++c) {
                    if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) { // 사각형이라면
                        A[i][j] --, A[r][c]--, A[i][c] ++, A[r][j]++;
                        if (r - i == c - j) // 정사각형이라면
                            ans++;
                    }
                }
            }
        }
    }

    return ans;
}
