/*
Bit_ImageMap3
[Solution Sketch]
1. 엔트리 단어고르기
   en : 엔트리 단어수(800~900), fn = 1023 - en
2. 문장의 등장한 빈도수를 기준으로 엔트리 단어를 정렬
   fn개의 단어는 9bit만으로 표시
   en - fn개의 단어는 10bit로 표시하는 전략을 사용할 수 있다.

SEED: 5, SCORE : 약189**** ~ 190****
*/
#define rint register int
using UI = unsigned int;

void write(char* str, int idx, int val) {
    *((UI*)(str + (idx >> 3))) |= val << (idx & 7);
}
int read(char* str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx & 7)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    long long entry[1025];    // 엔트리단어(단어|길이)
    int wnum[1 << 16];        // 문장의 단어가 참조하는 엔트리 단어 인덱스
    int en = 0, wn = 0;       // 엔트리 단어수, 문장의 단어수
    int freq[1025] = { 0 };   // 사용된 빈도수
    int rk[1025] = { 0 };     // 빈도수 내림차순 랭킹
    int sorted[1025] = { 0 }; // 빈도수 내림차순으로 정렬된 엔트리 인덱스

    long long word = 0;
    rint i, j, len = 0;
    for (i = 0; i < STRN && str[i]; ++i) {
        word = 0, len = 0;
        for (; i <= STRN && str[i] != ' '; ++i) {
            word = word * 32 + str[i] - 96;
            len++;
        }

        word = (word << 3) + len;
        for (j = 0; j < en && entry[j] != word; ++j); // linear search
        if (j == en) {          // 새로운 단어 등장
            entry[en++] = word;
        }
        wnum[wn++] = j;
        freq[j] ++;             // j번 단어의 사용빈도수 증가
    }

    for (i = 0; i < en; ++i) {  // 빈도수의 내림차순으로 랭킹부여
        for (j = 0; j < i; ++j) if (freq[j] >= freq[i])
            rk[i]++;
        for (j++; j < en; ++j) if (freq[j] > freq[i])
            rk[i]++;

        sorted[rk[i]] = i;       // 랭킹으로 정렬
    }

    rint idx = 0;
    write(enc_str, idx, en), idx += 10;   // 엔트리 단어수 기록
    write(enc_str, idx, wn), idx += 14;   // 문장의 단어수 기록

    for (i = 0; i < en; ++i) {
        word = entry[sorted[i]]; // 랭킹이 높은 단어부터 등록
        len = word & 7, word >>= 3;
        write(enc_str, idx, len), idx += 3;
        for (j = 0; j < len; ++j) {
            write(enc_str, idx, word & 31), idx += 5;
            word >>= 5;
        }
    }

    int fn = 1023 - en;          // 빈자리 수
    for (i = 0; i < wn; ++i) {
        j = rk[wnum[i]];
        if (j < fn) {            // 높은 랭킹부터 빈자리 수 만큼은 9bit할당
            write(enc_str, idx, j), idx += 9;
        }
        else {                   // en - fn개의 낮은 랭킹에는 10bit할당
            j += fn;             // fn개의 높은 랭킹과 구분되게 하기 위하여
            write(enc_str, idx, j >> 1), idx += 9;
            write(enc_str, idx, j & 1), idx++;
        }
    }
    return (idx + 7) / 8;
}

void decode(char* dec_str, char* enc_str, int encn) {
    rint idx = 0;
    int en = read(enc_str, idx, 10); idx += 10;
    int fn = 1023 - en;
    int wn = read(enc_str, idx, 14); idx += 14;

    char dict[1025][8] = { 0 };
    rint i, j, t = 0;
    for (i = 0; i < en; ++i) {
        int len = read(enc_str, idx, 3); idx += 3;
        for (j = len - 1; j >= 0; --j) {
            int k = read(enc_str, idx, 5); idx += 5;
            dict[i][j] = k + 96;
        }
    }

    for (i = 0; i < wn; ++i) {
        rint k = read(enc_str, idx, 9); idx += 9;
        if (k >= fn) {    // 낮은 랭킹의 경우 10bit이다.
            k = (k << 1) | read(enc_str, idx, 1), idx++;
            k -= fn;
        }
        for (j = 0; dict[k][j]; ++j)
            dec_str[t++] = dict[k][j];
        dec_str[t++] = ' ';
    }
}
