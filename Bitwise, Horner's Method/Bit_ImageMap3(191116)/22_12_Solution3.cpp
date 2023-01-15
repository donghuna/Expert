/*
Bit_ImageMap3_ver03
[Solution Sketch]
1. 엔트리 단어고르기
   dwcnt : 엔트리 단어수(800~900), fn = 1023 - dwcnt
2. 문장의 등장한 빈도수를 기준으로 엔트리 단어를 정렬
   fn개의 단어는 9bit만으로 표시
   dwcnt - fn개의 단어는 10bit로 표시하는 전략을 사용할 수 있다.
SEED: 5, SCORE: 185**** ~ 187****
*/
#define rint register int
using UI = unsigned int;

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx / 8))) |= val << (idx % 8);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx % 8)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    long long dicWords[1024];     // 엔트리 단어
    int dwLen[1024];            // 엔트리 각 단어의 길이
    int dwcnt = 0;                // 엔트리 단어수

    int wnum[1 << 14];         // 문장의 단어가 참조하는 엔트리 단어 인덱스
    int wn = 0;                // 문장의 단어수

    int freq[1025] = { 0 };    // 사용된 빈도수
    int mxF = 0;               // 최대 빈도수
    int cnt[2048] = { 0 };     // 빈도수 등장횟수 기록
    int ranking[1025] = { 0 }; // i번 엔트리의 랭크
    int sorted[1025] = { 0 };  // 빈도수 내림차순으로 정렬된 엔트리 인덱스

    long long word = 0;
    rint i, j, wlen = 0;
    for (i = 0; str[i]; ++i) {
        word = 0, wlen = 0;
        for (; str[i] != ' '; ++i) {
            word = (word << 5) + str[i] - 96;
            wlen++;
        }

        for (j = 0; j < dwcnt && dicWords[j] != word; ++j); // linear search
        if (j == dwcnt) {         // 새로운 단어 등장
            dicWords[dwcnt] = word;
            dwLen[dwcnt++] = wlen;
        }
        wnum[wn++] = j;
        freq[j] ++;            // j번 단어의 사용빈도수 증가
    }

    ////////// [counting sort : desc] //////////
    for (i = 0; i < dwcnt; ++i) {
        if (mxF < freq[i]) mxF = freq[i];
        cnt[freq[i]] ++;
    }
    for (i = mxF - 1; i > 0; --i) cnt[i] += cnt[i + 1];
    for (i = 0; i < dwcnt; ++i) {
        ranking[i] = --cnt[freq[i]];      // i등 수는 ranking[i]
        sorted[ranking[i]] = i;           // ranking[i]는 i등
    }
    ////////////////////////////////////////

    rint idx = 0;
    write(enc_str, idx, dwcnt), idx += 10;   // 엔트리 단어수 기록
    write(enc_str, idx, wn), idx += 14;   // 문장의 단어수 기록

    for (i = 0; i < dwcnt; ++i) {
        word = dicWords[sorted[i]];          // 랭킹이 높은 단어부터 등록
        wlen = dwLen[sorted[i]];
        write(enc_str, idx, wlen), idx += 3;
        for (j = 0; j < wlen; ++j) {
            write(enc_str, idx, word & 31), idx += 5;
            word >>= 5;
        }
    }

    int fn = 1024 - dwcnt;                   // 빈자리 수
    for (i = 0; i < wn; ++i) {
        j = ranking[wnum[i]];
        if (j < fn) {                     // 높은 랭킹부터 빈자리 수 만큼은 9bit할당
            write(enc_str, idx, j), idx += 9;
        }
        else {                            // dwcnt - fn개의 낮은 랭킹에는 10bit할당
            j += fn;                      // 상위 9비트를 비교할 때, fn개의 높은 랭킹과 구분되게 하기 위하여
            write(enc_str, idx, j >> 1), idx += 9;
            write(enc_str, idx, j & 1), idx++;
        }
    }
    return (idx + 7) / 8;
}

void decode(char* dec_str, char* enc_str, int encn) {
    rint idx = 0;
    int dwcnt = read(enc_str, idx, 10); idx += 10;  // 엔트리 단어수 구하기
    int fn = 1024 - dwcnt;                          // 빈자리수 구하기
    int wn = read(enc_str, idx, 14); idx += 14;  // 문장의 단어수 구하기

    char dicWords[1025][8] = { 0 };                 // 엔트리 단어를 저장할 배열
    rint i, j, t = 0;
    for (i = 0; i < dwcnt; ++i) {                   // 엔트리 단어 복원하여 저장
        int len = read(enc_str, idx, 3); idx += 3;
        for (j = len - 1; j >= 0; --j) {
            int k = read(enc_str, idx, 5); idx += 5;
            dicWords[i][j] = k + 96;
        }
    }

    for (i = 0; i < wn; ++i) {                   // 문장 복원하기
        // 엔트리 번호 찾기
        rint k = read(enc_str, idx, 9); idx += 9;
        if (k >= fn) {                           // 낮은 랭킹의 경우 10bit이다.
            k = (k << 1) | read(enc_str, idx, 1), idx++;
            k -= fn;
        }

        for (j = 0; dicWords[k][j]; ++j)            // 문장에 단어 기록하기
            dec_str[t++] = dicWords[k][j];
        dec_str[t++] = ' ';
    }
}