/*
14_데이터압축2_user_ver01
*/
#define rint register int
const int LM = 10000;
const int TH = 30;

void comp(char map[10000][10000], char data[150000]) {
    rint i, j, k;
    rint dataIndex = 4;       // data[]의 인덱스, data[0]: 가로 선분의 개수, data[1]: 전체 선분의 개수
    short* ap = (short*)data;  // data배열을 2바이트 단위로 사용하겠다는 의미.
    int* bp = (int*)data;

    // 가로로 세어 기록하기
    for (i = 0; i < LM; ++i) {
        for (j = 0; j < LM; ++j) if (map[i][j] == 1) {
            for (k = j + 1; k < LM && map[i][k] == 1; ++k);
            rint len = k - j + 1;  // 가로선의 길이
            if (len > TH) {
                ap[dataIndex++] = i;  // 행번호
                ap[dataIndex++] = j;  // 열시작
                ap[dataIndex++] = k;  // 열끝

                // 가로로 센것을 표시하기: 세로로 셀때 제외하고 생각하기 위하여
                for (; j < k; ++j) map[i][j] = 2;
            }
            j = k;
        }
    }
    bp[0] = dataIndex;

    // 세로로 세어 기록하기
    for (j = 0; j < LM; ++j) {
        for (i = 0; i < LM; ++i) if (map[i][j] == 1) {  // 시작위치
            for (k = i + 1; k < LM && map[k][j] > 0; ++k);
            ap[dataIndex++] = i; // 행시작
            ap[dataIndex++] = k; // 행끝
            ap[dataIndex++] = j; // 열번호
            i = k;
        }
    }
    bp[1] = dataIndex;
}

void decomp(char map[10000][10000], char data[150000]) {
    rint i, j, k;
    rint dataIndex = 4;       // data[]의 인덱스, data[0]: 가로 선분의 개수, data[1]: 전체 선분의 개수
    short* ap = (short*)data;  // data배열을 2바이트 단위로 사용하겠다는 의미.
    int* bp = (int*)data;
    rint an = bp[0], bn = bp[1];

    // 가로선 긋기
    for (; dataIndex < an;) {
        rint i = ap[dataIndex++]; // 행번호
        rint j = ap[dataIndex++]; // 열시작
        rint k = ap[dataIndex++]; // 열끝
        for (; j < k; ++j) map[i][j] = 1;
    }

    while (dataIndex < bn) {
        rint i = ap[dataIndex++]; // 행시작
        rint k = ap[dataIndex++]; // 행끝
        rint j = ap[dataIndex++]; // 열번호
        for (; i < k; ++i) map[i][j] = 1;
    }
}