/*
14_데이터압축2_user_ver02
[선분으로 자료를 표현 + 대각선 좌표값을 FLIP]
    가로정보개수, 세로정보개수, (가로정보들 : 시작점, 길이(sr, sc, n)), (세로정보들: 시작점, 길이(sr, sc, n))
    가로길이가 TH이상인 경우는 가로 정보로 표시하고, 나머지는 세로정보로 표시한다.

    14bit * 3(선분정보) * 4(한 사각형의 선분수) * 10000(사각형수) = 1,680,000bit이므로210,000여 byte로 나타낼 수 있다.
    조금 여유있게 16(short) * 3 * 40000 = 1,920,000 이고 240000 여 byte로 나타낼 수 있다.
    예측치가 주어진 15만개의 공간을 초과하지만 데이터가 random생성되며 여러개의 사각형이 겹치는 경우
    데이터수가 24만이 되지 않을 가능성이 매우높다.

[대각선 flip 참고 자료]
Why is iterating 2D array row major faster than column major ?
https://stackoverflow.com/questions/33722520/why-is-iterating-2d-array-row-major-faster-than-column-major
*/
#define rint register int
const int LM = 10000;
const int TH = 40;

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

    // 대각선 flip
    for (i = 0; i < LM; ++i) {
        for (j = i + 1; j < LM; ++j) {
            rint t = map[i][j];
            map[i][j] = map[j][i];
            map[j][i] = t;
        }
    }

    // 세로로 세어 기록하기
    for (i = 0; i < LM; ++i) {
        for (j = 0; j < LM; ++j) if (map[i][j] == 1) {  // 시작위치
            for (k = j + 1; k < LM && map[i][k] > 0; ++k);
            ap[dataIndex++] = j; // 행시작
            ap[dataIndex++] = k; // 행끝
            ap[dataIndex++] = i; // 열번호
            j = k;
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