*
Bit_ImageMap3_ver02
단어길이 기준으로 정렬한 버전
단어길이 3비트를 저장하지 않음으로 TC당 3*850(평균entry단어수) / 8 = 약 300점 절약할 수 있다.

[문제 개요]
소문자로 구성된 단어(길이1~7)들로 주어진 길이 65535의 문장(공백으로 구분)이 주어질때,
encode(압축), decode(복원) 하는 문제.
(1) 압축한 크기가 작을수록 좋은 점수.
(2) 실행속도가 빠를수록 좋은 점수.

[문제 분석]
(1) - 등장하는 단어의 종류는 최대 1024(평균 800 ~900)개,
    - 한 문장에 등장하는 단어의 개수는 평균 13107개 내외(65535 / 5(단어의 평균길이4 + 공백1) = 13107)
    - 이 특징들을 이용할 수 있을까 ?
(2) 단어의 빈도수를 이용한 허프만코드 ? ? ?
(3) 한문자를 5bit로 줄여표현하기 : 65536 * 5 / 8 = 40960btye를 사용하므로 100개 TC에 대한 점수는 400만여 점이다.
    주어진 메모리 안에서 해결가능하나 좋은 점수를 받기 힘들다.
    적어도 20000점 미만으로 해결할 수 있어야 한다.

[해법 연구 : ]
등장 entry단어가 최대 1024라는 점에 착안, 단어장을 만들고 하나의 단어를 10bit로 표현하기
(1) encode :
    사전단어수 : 문장단어수 : 사전 단어 기록 : 문장 단어 기록
    10bit : 14bit : (3bit(단어길이) + 5bit(한문자) * 4(단어길이평균)) * 1000(사전단어수) : 10bit * 문장단어수
    = (10) + (14) + (23 * 1000) + (10 * 13107) = 24 + 23000 + 131070 = 154094 bit
    * 하나의 TC당 점수 : 154094 / 8 = 19, 261.75점
    (2) decode : endcode의 내용을(1)의 역으로 풀어 str완성.
    (3) 점수 예상치 : 19,261.75 * 100 + 2000(실행시간) = 약 1,926,175 예상
    (4) 고찰
    : entry 단어의 수 ecnt 는 800~900개 이므로 rcnt = 1023 - ecnt개는 여유분이다.
      rcnt는 9비트 만을 할당하고 ecnt-rcnt개에는 10비트를 할당하는 전략을 사용할 수 있다.
    : 빈도수를 기준으로 정렬한후 빈도수 높은 단어들(rcnt)에 9bit를 낮은 번호들(ecnt - rcnt)에 10bit를 할당하는 전략을 사용할 수 있다.

    SEED:5, SCORE : 1901144
*/
#define rint register int
using UI = unsigned int;

void write(char*str, int idx, int val) {
    *((UI*)(str + (idx >> 3))) |= val << (idx & 7);
}
int read(char*str, int idx, int bitLen) {
    UI tg = *((UI*)(str + (idx >> 3))), mask = (1 << bitLen) - 1;
    return (tg >> (idx & 7)) & mask;
}

int encode(char* enc_str, char* str, int STRN) {
    long long entry[1025], sorted[1025]; // entry 단어들 : 단어(최대35bit)+길이(3bit)를 하나의 정수로 저장
    int cnt[8] = { 0 }, rank[1025];
    int ecnt = 0;          // entry 단어 수

    int wnum[1 << 16];     // 문장의 단어를 entry단어 번호로 치환하여 저장
    int wcnt = 0;          // 문장의 단어수

    long long word = 0;
    rint i, j, len = 0;
    for (i = 0; i < STRN && str[i]; ++i) {
        if (str[i] == ' ') {
            word = (word << 3) + len;
            for (j = 0; j < ecnt && entry[j] != word; ++j); // full search
            if (j == ecnt)  // 못찾은 경우 단어 등록하기
                entry[ecnt++] = word, cnt[len]++;
            wnum[wcnt++] = j;  // 문장의 wcnt번째단어는 단어장의 j번 단어
            word = 0, len = 0; // 새로운 단어를 저장하기 위하여 초기화
        }
        else {
            word = (word << 5) + str[i] - 96;  // Horner's method
            len++;
        }
    }

    //enc_str에 entry단어수 기록
    rint idx = 0;
    for (i = 1; i < 8; ++i)
        write(enc_str, idx, cnt[i]), idx += 9;

    // counting_sort, rank
    for (i = 1; i < 8; ++i) cnt[i] += cnt[i - 1];
    for (i = ecnt - 1; i >= 0; --i) {
        len = entry[i] & 7;
        rank[i] = --cnt[len];
        sorted[cnt[len]] = entry[i];
    }

    // 2. 문장의 단어수 기록하기
    write(enc_str, idx, wcnt), idx += 14;  // 16384

    // 3. enc_str에 entry단어 기록하기
    for (i = 0; i < ecnt; ++i) {
        long long w = sorted[i];
        len = w & 7, w >>= 3;
        for (j = 0; j < len; ++j) {                // 단어 기록
            write(enc_str, idx, w & 31), idx += 5; // 문자단위로 기록
            w >>= 5;                               // 다음문자를 위하여
        }
    }

    // 4. enc_str에 문장의 단어 번호 기록하기
    for (i = 0; i < wcnt; ++i) {
        write(enc_str, idx, rank[wnum[i]]), idx += 10;
    }

    int sentenceLength = (idx + 7) / 8;           // 올림식
    return sentenceLength;                        // 압축된 길이 반환
}

void decode(char* dec_str, char* enc_str, int encn) {
    // 1. entry 단어수 구하기, 문장의 단어수 구하기
    rint i, j, k, t;
    rint idx = 0;
    int ecnt = 0, cnt[8] = { 0 };
    for (i = 1; i < 8; ++i)
        cnt[i] = read(enc_str, idx, 9), idx += 9;
    int wcnt = read(enc_str, idx, 14); idx += 14;

    // 2. entry 단어 복원하여 기록하기
    char dict[1025][8] = { 0 };
    for (i = 1; i < 8; ++i) {
        for (j = 0; j < cnt[i]; ++j) {
            for (k = i - 1; k >= 0; --k) {
                t = read(enc_str, idx, 5); idx += 5; // 단어 복원하기
                dict[ecnt][k] = t + 96;
            }
            ecnt++;
        }
    }

    // 3. dec_str에 문장 복원하기
    t = 0;
    for (i = 0; i < wcnt; ++i) {
        int k = read(enc_str, idx, 10); idx += 10;
        for (j = 0; dict[k][j]; ++j)
            dec_str[t++] = dict[k][j];
        dec_str[t++] = ' ';
    }
}
