/*
ver01
seed:1117, score:7822 : fail
*/
#define rint register int

const int LM = 66;
int A[LM][LM], S[LM][LM];

int recog(unsigned char image[64][64])
{
    rint i, j, k;
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
        for (j = 1; j < 56; ++j) if(A[i][j] > 0){
            for (k = 10; i + k < LM && j + k < LM; ++k) {
                int r = i + k, c = j + k;   // 정사각형만 찾을 예정이므로
                if (A[i][j] > 0 && A[r][c] > 0 && A[i][c] < 0 && A[r][j] < 0) {
                    A[i][j]--, A[r][c]--, A[i][c]++, A[r][j]++;
                    ans++;
                }
            }
        }
    }

    return ans;
}
